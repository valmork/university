import sqlite3
import os

def init_db():
    """Инициализация базы данных и создание таблиц"""
    # Удаляем старый файл базы если он существует
    if os.path.exists('students.db'):
        os.remove('students.db')
        print("Старая база данных удалена")
    
    conn = sqlite3.connect('students.db')
    cursor = conn.cursor()
    
    # Создаем таблицу студентов с уникальным ограничением
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS students (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            full_name TEXT NOT NULL,
            birth_date TEXT NOT NULL,
            group_name TEXT NOT NULL,
            phone TEXT,
            email TEXT,
            enrollment_year INTEGER,
            UNIQUE(full_name, birth_date, group_name)  -- Уникальная комбинация
        )
    ''')
    
    # Добавление тестовых данных
    cursor.execute("SELECT COUNT(*) FROM students")
    if cursor.fetchone()[0] == 0:
        print("Добавляем тестовые данные в базу...")
        
        students = [
            ('Петров Иван Сергеевич', '2000-05-15', '31ПИ', '+79161234567', 'petrov@edu.ru', 2023),
            ('Сидорова Мария Владимировна', '2001-03-20', '31ПГ', '+79162345678', 'sidorova@edu.ru', 2023),
            ('Козлов Алексей Дмитриевич', '2000-11-08', '31ИВТ', '+79163456789', 'kozlov@edu.ru', 2023),
            ('Никитина Елена Петровна', '2001-07-12', '31ПИ', '+79164567890', 'nikitina@edu.ru', 2023),
            ('Васильев Дмитрий Игоревич', '2000-09-25', '31ПИ', '+79165678901', 'vasilev@edu.ru', 2023)
        ]
        try:
            cursor.executemany('''
                INSERT INTO students (full_name, birth_date, group_name, phone, email, enrollment_year) 
                VALUES (?, ?, ?, ?, ?, ?)
            ''', students)
            print("Тестовые данные успешно добавлены!")
        except sqlite3.IntegrityError:
            print("Некоторые тестовые данные уже существуют")
    
    conn.commit()
    conn.close()
    print("База данных успешно инициализирована!")

def get_db_connection():
    """Создание соединения с базой данных"""
    conn = sqlite3.connect('students.db')
    conn.row_factory = sqlite3.Row
    return conn

def check_db_exists():
    """Проверка существования файла базы данных"""
    return os.path.exists('students.db')

def student_exists(full_name, birth_date, group_name):
    """Проверяет, существует ли студент с такими данными"""
    conn = get_db_connection()
    try:
        student = conn.execute('''
            SELECT id FROM students 
            WHERE full_name = ? AND birth_date = ? AND group_name = ?
        ''', (full_name, birth_date, group_name)).fetchone()
        return student is not None
    finally:
        conn.close()

def email_exists(email):
    """Проверяет, существует ли email (если email указан)"""
    if not email:
        return False
    conn = get_db_connection()
    try:
        student = conn.execute('SELECT id FROM students WHERE email = ?', (email,)).fetchone()
        return student is not None
    finally:
        conn.close()

def phone_exists(phone):
    """Проверяет, существует ли телефон (если телефон указан)"""
    if not phone:
        return False
    conn = get_db_connection()
    try:
        student = conn.execute('SELECT id FROM students WHERE phone = ?', (phone,)).fetchone()
        return student is not None
    finally:
        conn.close()