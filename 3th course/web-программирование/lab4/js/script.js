// Основной массив с книгами (главное хранилище данных приложения)
let books = [];

// Текущий фильтр отображения: all | read | unread
let currentFilter = 'all'; 

// Ключ для хранения данных в LocalStorage
const STORAGE_KEY = 'my_book_list_v1';


// Сохранение текущего массива книг в LocalStorage
function saveToStorage() {
  try {
    // Преобразуем массив в JSON-строку и сохраняем
    localStorage.setItem(STORAGE_KEY, JSON.stringify(books));
  } catch (e) {
    console.error('Не удалось сохранить данные в LocalStorage', e);
  }
}

// Загрузка данных из LocalStorage при старте страницы
function loadFromStorage() {
  try {
    const raw = localStorage.getItem(STORAGE_KEY);
    // Если данные есть — парсим JSON, иначе создаём пустой массив
    books = raw ? JSON.parse(raw) : [];
  } catch (e) {
    console.error('Не удалось загрузить данные из LocalStorage', e);
    books = [];
  }
}


// Генерация уникального идентификатора для книги
function genId() {
  return `${Date.now()}_${Math.random().toString(36).slice(2, 8)}`;
}

// Нормализация строки: убираем лишние пробелы
function norm(str) {
  return String(str || '').trim().replace(/\s+/g, ' ');
}


// Пересчёт и отображение статистики книг
function renderStats() {
  const total = books.length;
  const read = books.filter(b => b.read).length;
  const unread = total - read;

  $('#totalBooks').text(total);
  $('#readBooks').text(read);
  $('#unreadBooks').text(unread);
}


// Преобразование объекта книги в HTML-разметку
function bookToHTML(b) {
  return `
    <li class="book-item ${b.read ? 'read' : ''}" data-id="${b.id}">
      <div class="book-info">
        <div class="book-title" title="Двойной клик — редактировать">
          ${$('<div>').text(b.title).html()}
        </div>
        <div class="book-author">
          ${$('<div>').text(b.author || 'Неизвестный автор').html()}
        </div>
      </div>
      <div class="book-actions">
        <button class="toggle-read-btn" title="Изменить статус">
          ${b.read ? 'Сделать непрочитанной' : 'Отметить как прочитано'}
        </button>
        <button class="delete-btn" title="Удалить">Удалить</button>
      </div>
    </li>
  `;
}

// Применение фильтра к массиву книг
function applyFilter(arr) {
  switch (currentFilter) {
    case 'read':   return arr.filter(b => b.read);
    case 'unread': return arr.filter(b => !b.read);
    default:       return arr;
  }
}

// Полная перерисовка списка книг
function renderList(withAnimation = false) {
  const list = $('#bookList');
  list.empty();

  const toShow = applyFilter(books);

  if (toShow.length === 0) {
    list.append('<li class="search-result-item" style="cursor:default">Список пуст</li>');
  } else {
    toShow.forEach(b => {
      const $item = $(bookToHTML(b));

      // Анимация при добавлении
      if (withAnimation) {
        $item.hide();
        list.append($item);
        $item.slideDown(180);
      } else {
        list.append($item);
      }
    });
  }

  // После отрисовки обновляем статистику
  renderStats();
}


// Добавление новой книги
function addBook(title, author) {
  const t = norm(title);
  const a = norm(author);

  // Проверка на пустое название
  if (!t) {
    $('#bookTitle').addClass('input-error');
    setTimeout(() => $('#bookTitle').removeClass('input-error'), 600);
    return;
  }

  const book = {
    id: genId(),
    title: t,
    author: a,
    read: false
  };

  // Добавляем книгу в начало массива
  books.unshift(book);
  saveToStorage();
  renderList(true);
}

// Удаление книги
function deleteBook(id) {
  const idx = books.findIndex(b => b.id === id);
  if (idx >= 0) {
    books.splice(idx, 1);
    saveToStorage();
    renderList();
  }
}

// Переключение статуса "прочитано"
function toggleRead(id) {
  const b = books.find(x => x.id === id);
  if (b) {
    b.read = !b.read;
    saveToStorage();
    renderList();
  }
}

// Редактирование книги (через prompt)
function editBook(id) {
  const b = books.find(x => x.id === id);
  if (!b) return;

  const newTitle = prompt('Изменить название книги:', b.title);
  if (newTitle === null) return;

  const newAuthor = prompt('Изменить автора:', b.author || '');
  if (newAuthor === null) return;

  const t = norm(newTitle);
  const a = norm(newAuthor);

  if (!t) return;

  b.title = t;
  b.author = a;
  saveToStorage();
  renderList();
}


let searchInFlight = false;

// Асинхронный поиск книг через внешний API
async function searchOpenLibrary(query) {
  const q = norm(query);

  if (!q) {
    $('#searchResults').html('<div class="search-result-item">Введите запрос для поиска</div>');
    return;
  }

  // Защита от повторных запросов
  if (searchInFlight) return;
  searchInFlight = true;

  $('#searchResults').html('<div class="search-result-item">Идет поиск…</div>');

  try {
    const url = `https://openlibrary.org/search.json?q=${encodeURIComponent(q)}&limit=10`;
    const res = await fetch(url);
    if (!res.ok) throw new Error('Ошибка сети');

    const data = await res.json();
    const docs = Array.isArray(data.docs) ? data.docs : [];

    if (docs.length === 0) {
      $('#searchResults').html('<div class="search-result-item">Ничего не найдено</div>');
      return;
    }

    // Формирование HTML результатов поиска
    const html = docs.map(d => {
      const title = d.title || 'Без названия';
      const authors = d.author_name?.join(', ') || 'Неизвестный автор';

      return `
        <div class="search-result-item js-add-from-search"
             data-title="${$('<div>').text(title).html()}"
             data-author="${$('<div>').text(authors).html()}">
          <strong>${$('<div>').text(title).html()}</strong><br>
          <em>${$('<div>').text(authors).html()}</em>
        </div>
      `;
    }).join('');

    $('#searchResults').html(html);
  } catch (e) {
    console.error(e);
    $('#searchResults').html('<div class="search-result-item">Ошибка поиска</div>');
  } finally {
    searchInFlight = false;
  }
}


$(function () {

  // Загружаем данные и отрисовываем список
  loadFromStorage();
  renderList();

  // Добавление книги
  $('#addBookBtn').on('click', () => {
    const title = $('#bookTitle').val();
    const author = $('#bookAuthor').val();
    addBook(title, author);

    if (norm(title)) {
      $('#bookTitle').val('');
      $('#bookAuthor').val('');
    }
  });

  // Добавление по Enter
  $('#bookTitle, #bookAuthor').on('keydown', function (e) {
    if (e.key === 'Enter') {
      $('#addBookBtn').click();
    }
  });

  // Делегирование событий списка книг
  $('#bookList')
    .on('click', '.delete-btn', function () {
      const id = $(this).closest('.book-item').data('id');
      deleteBook(String(id));
    })
    .on('click', '.toggle-read-btn', function () {
      const id = $(this).closest('.book-item').data('id');
      toggleRead(String(id));
    })
    .on('dblclick', '.book-title, .book-author', function () {
      const id = $(this).closest('.book-item').data('id');
      editBook(String(id));
    });

  // Фильтрация
  $('.filter-btn').on('click', function () {
    $('.filter-btn').removeClass('active');
    $(this).addClass('active');
    currentFilter = $(this).data('filter');
    renderList();
  });

  // Поиск
  $('#searchBtn').on('click', () => {
    searchOpenLibrary($('#searchInput').val());
  });

  $('#searchInput').on('keydown', function (e) {
    if (e.key === 'Enter') {
      $('#searchBtn').click();
    }
  });

  // Добавление книги из результатов поиска
  $('#searchResults').on('click', '.js-add-from-search', function () {
    addBook($(this).data('title'), $(this).data('author'));
    $(this).fadeOut(120).fadeIn(120);
  });
});
