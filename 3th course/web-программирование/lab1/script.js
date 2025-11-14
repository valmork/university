const newTaskInput = document.getElementById('new-task');
const addButton = document.getElementById('add-button');
const taskList = document.getElementById('task-list');

addButton.addEventListener('click', function() {
    const taskText = newTaskInput.value.trim();
    
    if (taskText === '') {
        alert('Пожалуйста, введите текст дела!');
        return;
    }
    
    const listItem = document.createElement('li');
    const taskSpan = document.createElement('span');
    const deleteButton = document.createElement('button');
    
    taskSpan.textContent = taskText;
    deleteButton.textContent = 'Удалить';
    
    listItem.appendChild(taskSpan);
    listItem.appendChild(deleteButton);
    taskList.appendChild(listItem);
    
    newTaskInput.value = '';
});

taskList.addEventListener('click', function(event) {
    const target = event.target;
    
    if (target.tagName === 'BUTTON') {
        const listItem = target.parentElement;
        taskList.removeChild(listItem);
    }
    
    if (target.tagName === 'SPAN') {
        target.classList.toggle('completed');
    }
});