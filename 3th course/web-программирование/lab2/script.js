const searchInput = document.getElementById('search');
const userList = document.getElementById('user-list');

let allUsers = [];

function loadUsers() {
    const xhr = new XMLHttpRequest();
    xhr.open('GET', 'users.json', true);
    
    xhr.onload = function() {
        if (xhr.status === 200) {
            allUsers = JSON.parse(xhr.responseText);
            displayUsers(allUsers);
        } else {
            console.error('Ошибка загрузки данных: ' + xhr.status);
        }
    };
    
    xhr.onerror = function() {
        console.error('Ошибка сети');
    };
    
    xhr.send();
}

function displayUsers(users) {
    userList.innerHTML = '';
    
    users.forEach(user => {
        const listItem = document.createElement('li');
        listItem.textContent = `Имя: ${user.name}, Email: ${user.email}`;
        userList.appendChild(listItem);
    });
}

function filterUsers() {
    const searchText = searchInput.value.toLowerCase();
    const filteredUsers = allUsers.filter(user => 
        user.name.toLowerCase().includes(searchText)
    );
    displayUsers(filteredUsers);
}

searchInput.addEventListener('input', filterUsers);

window.onload = function() {
    loadUsers();
};