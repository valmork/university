
let books = [];
let currentFilter = 'all'; 

const STORAGE_KEY = 'my_book_list_v1';


function saveToStorage() {
  try {
    localStorage.setItem(STORAGE_KEY, JSON.stringify(books));
  } catch (e) {
    console.error('Не удалось сохранить данные в LocalStorage', e);
  }
}


function loadFromStorage() {
  try {
    const raw = localStorage.getItem(STORAGE_KEY);
    books = raw ? JSON.parse(raw) : [];
  } catch (e) {
    console.error('Не удалось загрузить данные из LocalStorage', e);
    books = [];
  }
}


function genId() {
  return `${Date.now()}_${Math.random().toString(36).slice(2, 8)}`;
}


function norm(str) {
  return String(str || '').trim().replace(/\s+/g, ' ');
}



function renderStats() {
  const total = books.length;
  const read = books.filter(b => b.read).length;
  const unread = total - read;

  $('#totalBooks').text(total);
  $('#readBooks').text(read);
  $('#unreadBooks').text(unread);
}

function bookToHTML(b) {
  return `
    <li class="book-item ${b.read ? 'read' : ''}" data-id="${b.id}">
      <div class="book-info">
        <div class="book-title" title="Двойной клик — редактировать">${$('<div>').text(b.title).html()}</div>
        <div class="book-author">${$('<div>').text(b.author || 'Неизвестный автор').html()}</div>
      </div>
      <div class="book-actions">
        <button class="toggle-read-btn" title="Отметить как ${b.read ? 'не прочитано' : 'прочитано'}">
          ${b.read ? 'Сделать непрочитанной' : 'Отметить как прочитано'}
        </button>
        <button class="delete-btn" title="Удалить">Удалить</button>
      </div>
    </li>
  `;
}

function applyFilter(arr) {
  switch (currentFilter) {
    case 'read':   return arr.filter(b => b.read);
    case 'unread': return arr.filter(b => !b.read);
    default:       return arr;
  }
}

function renderList(withAnimation = false) {
  const list = $('#bookList');
  list.empty();

  const toShow = applyFilter(books);

  if (toShow.length === 0) {
    list.append(`<li class="search-result-item" style="cursor:default">Список пуст</li>`);
  } else {
    toShow.forEach(b => {
      const $item = $(bookToHTML(b));
      if (withAnimation) {
        $item.hide();
        list.append($item);
        $item.slideDown(180);
      } else {
        list.append($item);
      }
    });
  }

  renderStats();
}



function addBook(title, author) {
  const t = norm(title);
  const a = norm(author);

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
  books.unshift(book);
  saveToStorage();
  renderList(true);
}

function deleteBook(id) {
  const idx = books.findIndex(b => b.id === id);
  if (idx >= 0) {
    books.splice(idx, 1);
    saveToStorage();
    renderList();
  }
}

function toggleRead(id) {
  const b = books.find(x => x.id === id);
  if (b) {
    b.read = !b.read;
    saveToStorage();
    renderList();
  }
}

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

async function searchOpenLibrary(query) {
  const q = norm(query);
  if (!q) {
    $('#searchResults').html('<div class="search-result-item" style="cursor:default">Введите запрос для поиска</div>');
    return;
  }

  if (searchInFlight) return;
  searchInFlight = true;

  $('#searchResults').html('<div class="search-result-item" style="cursor:default">Идет поиск…</div>');

  try {
    
    const url = `https://openlibrary.org/search.json?q=${encodeURIComponent(q)}&limit=10`;
    const res = await fetch(url);
    if (!res.ok) throw new Error('Ошибка сети');

    const data = await res.json();

    const docs = Array.isArray(data.docs) ? data.docs : [];
    if (docs.length === 0) {
      $('#searchResults').html('<div class="search-result-item" style="cursor:default">Ничего не найдено</div>');
      return;
    }

    const html = docs.map(d => {
      const title = d.title || 'Без названия';
      const authors = (d.author_name && d.author_name.length) ? d.author_name.join(', ') : 'Неизвестный автор';
      return `
        <div class="search-result-item js-add-from-search"
             data-title="${$('<div>').text(title).html()}"
             data-author="${$('<div>').text(authors).html()}"
             title="Нажмите, чтобы добавить">
          <strong>${$('<div>').text(title).html()}</strong><br>
          <em>${$('<div>').text(authors).html()}</em>
        </div>
      `;
    }).join('');

    $('#searchResults').html(html);
  } catch (e) {
    console.error(e);
    $('#searchResults').html('<div class="search-result-item" style="cursor:default">Ошибка при поиске. Попробуйте позже.</div>');
  } finally {
    searchInFlight = false;
  }
}



$(function () {

  loadFromStorage();
  renderList();


  $('#addBookBtn').on('click', () => {
    const title = $('#bookTitle').val();
    const author = $('#bookAuthor').val();
    addBook(title, author);
    if (norm(title)) {
  
      $('#bookTitle').val('');
      $('#bookAuthor').val('');
    }
  });


  $('#bookTitle, #bookAuthor').on('keydown', function (e) {
    if (e.key === 'Enter') {
      $('#addBookBtn').click();
    }
  });


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


  $('.filter-btn').on('click', function () {
    $('.filter-btn').removeClass('active');
    $(this).addClass('active');
    currentFilter = $(this).data('filter');
    renderList();
  });

  $('#searchBtn').on('click', () => {
    const q = $('#searchInput').val();
    searchOpenLibrary(q);
  });


  $('#searchInput').on('keydown', function (e) {
    if (e.key === 'Enter') {
      $('#searchBtn').click();
    }
  });


  $('#searchResults').on('click', '.js-add-from-search', function () {
    const title = $(this).data('title');
    const author = $(this).data('author');
    addBook(title, author);

    $(this).fadeOut(120).fadeIn(120);
  });
});
