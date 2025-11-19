// Получение доступа к элементам
const searchInput = document.getElementById('search');
const userList = document.getElementById('user-list');

let allUsers = []; // Сохраняем всех пользователей для фильтрации

// Реализация AJAX-запроса для загрузки данных
function loadUsers() {
    const xhr = new XMLHttpRequest();
    
    xhr.open('GET', 'users.json', true);
    
    xhr.onload = function() {
        if (xhr.status === 200) {
            // Преобразуем JSON-строку в массив объектов
            allUsers = JSON.parse(xhr.responseText);
            // Отображаем всех пользователей
            displayUsers(allUsers);
        } else {
            console.error('Ошибка загрузки данных: ' + xhr.status);
        }
    };
    
    xhr.onerror = function() {
        console.error('Ошибка сети при выполнении запроса');
    };
    
    xhr.send();
}

// Реализация отображения списка пользователей
function displayUsers(users) {
    // Очищаем список
    userList.innerHTML = '';
    
    // Для каждого пользователя создаем элемент списка
    users.forEach(user => {
        const listItem = document.createElement('li');
        listItem.textContent = `Имя: ${user.name}, Email: ${user.email}`;
        userList.appendChild(listItem);
    });
}

// Реализация фильтрации пользователей
function filterUsers() {
    const searchText = searchInput.value.toLowerCase();
    
    // Фильтруем пользователей по имени
    const filteredUsers = allUsers.filter(user => 
        user.name.toLowerCase().includes(searchText)
    );
    
    // Отображаем отфильтрованных пользователей
    displayUsers(filteredUsers);
}

// Загружаем пользователей после загрузки страницы
window.onload = function() {
    loadUsers();
    
    // Добавляем обработчик события input для поиска
    searchInput.addEventListener('input', filterUsers);
};