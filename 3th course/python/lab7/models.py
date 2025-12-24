import sqlite3
import os

# Определяем абсолютный путь к базе данных
def get_db_path():
    """Возвращает абсолютный путь к файлу базы данных"""
    base_dir = os.path.dirname(os.path.abspath(__file__))
    db_path = os.path.join(base_dir, 'students.db')
    print(f"DB Path: {db_path}")  # Для отладки
    return db_path

def init_db():
    """Инициализация базы данных - создает таблицы если их нет"""
    db_path = get_db_path()
    
    conn = sqlite3.connect(db_path)
    cursor = conn.cursor()
    
    # Создаем таблицу если ее нет
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS students (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            full_name TEXT NOT NULL,
            birth_date TEXT NOT NULL,
            group_name TEXT NOT NULL,
            phone TEXT,
            email TEXT,
            enrollment_year INTEGER,
            UNIQUE(full_name, birth_date, group_name)
        )
    ''')
    
    # Проверяем, есть ли тестовые данные
    cursor.execute("SELECT COUNT(*) FROM students")
    student_count = cursor.fetchone()[0]
    
    # Добавляем тестовые данные ТОЛЬКО если таблица пустая
    if student_count == 0:
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
            print("✅ Тестовые данные успешно добавлены!")
        except sqlite3.IntegrityError as e:
            print(f"⚠️ Некоторые тестовые данные уже существуют: {e}")
    else:
        print(f"📊 В базе уже есть {student_count} студентов, тестовые данные не добавляем")
    
    conn.commit()
    conn.close()
    print("✅ База данных успешно инициализирована!")

def get_db_connection():
    """Создание соединения с базой данных"""
    db_path = get_db_path()
    conn = sqlite3.connect(db_path)
    conn.row_factory = sqlite3.Row
    return conn

def check_db_exists():
    """Проверка существования файла базы данных"""
    db_path = get_db_path()
    return os.path.exists(db_path)

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