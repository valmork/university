const WebSocket = require('ws');
const { v4: uuidv4 } = require('uuid');

// Создаем WebSocket сервер на порту 8080
const wss = new WebSocket.Server({ port: 8080 });

// Хранилище для подключенных клиентов
const clients = new Map();
let onlineUsers = [];

console.log('WebSocket сервер запущен на порту 8080');

// Функция для отправки обновленного списка пользователей всем клиентам
function broadcastOnlineUsers() {
    const usersList = Array.from(clients.values()).map(client => ({
        id: client.id,
        username: client.username
    }));
    
    const message = {
        type: 'users_update',
        users: usersList
    };
    
    broadcastMessage(message);
}

// Функция для рассылки сообщения всем подключенным клиентам
function broadcastMessage(message) {
    const messageString = JSON.stringify(message);
    
    wss.clients.forEach(client => {
        if (client.readyState === WebSocket.OPEN) {
            client.send(messageString);
        }
    });
}

// Функция для отправки сообщения конкретному клиенту
function sendToClient(client, message) {
    if (client.readyState === WebSocket.OPEN) {
        client.send(JSON.stringify(message));
    }
}

// Обработка подключения нового клиента
wss.on('connection', function connection(ws) {
    // Генерируем уникальный ID для клиента
    const clientId = uuidv4();
    console.log(`Новое подключение: ${clientId}`);
    
    // Инициализируем клиента без имени пользователя
    clients.set(ws, {
        id: clientId,
        username: null
    });
    
    // Отправляем приветственное сообщение
    sendToClient(ws, {
        type: 'system',
        id: uuidv4(),
        text: 'Добро пожаловать в чат! Пожалуйста, введите ваше имя.',
        timestamp: new Date().toISOString()
    });
    
    // Обработка сообщений от клиента
    ws.on('message', function incoming(data) {
        try {
            const message = JSON.parse(data);
            const clientData = clients.get(ws);
            
            // Если пользователь еще не установил имя
            if (!clientData.username && message.type === 'set_username') {
                clientData.username = message.username;
                clients.set(ws, clientData);
                
                // Уведомляем всех о новом пользователе
                broadcastMessage({
                    type: 'system',
                    id: uuidv4(),
                    text: `Пользователь ${message.username} присоединился к чату`,
                    timestamp: new Date().toISOString()
                });
                
                // Обновляем список пользователей
                broadcastOnlineUsers();
                
                return;
            }
            
            // Обработка обычных сообщений
            if (message.type === 'chat_message' && clientData.username) {
                const chatMessage = {
                    type: 'chat_message',
                    id: uuidv4(),
                    text: message.text,
                    username: clientData.username,
                    userId: clientData.id,
                    timestamp: new Date().toISOString()
                };
                
                console.log(`Сообщение от ${clientData.username}: ${message.text}`);
                broadcastMessage(chatMessage);
            }
            
        } catch (error) {
            console.error('Ошибка обработки сообщения:', error);
        }
    });
    
    // Обработка отключения клиента
    ws.on('close', function close() {
        const clientData = clients.get(ws);
        if (clientData && clientData.username) {
            console.log(`Отключение: ${clientData.username}`);
            
            // Уведомляем всех об отключении пользователя
            broadcastMessage({
                type: 'system',
                id: uuidv4(),
                text: `Пользователь ${clientData.username} покинул чат`,
                timestamp: new Date().toISOString()
            });
        } else {
            console.log(`Отключение: ${clientId}`);
        }
        
        clients.delete(ws);
        broadcastOnlineUsers();
    });
    
    // Обработка ошибок
    ws.on('error', function error(err) {
        console.error('Ошибка WebSocket:', err);
    });
});