import sqlite3
import os

def check_database():
    """Проверка структуры базы данных"""
    if not os.path.exists('students.db'):
        print("Файл базы данных 'students.db' не существует!")
        return False
    
    try:
        conn = sqlite3.connect('students.db')
        cursor = conn.cursor()
        
        # Проверяем существование таблиц
        tables = ['students', 'groups', 'faculties']
        for table in tables:
            cursor.execute(f"SELECT name FROM sqlite_master WHERE type='table' AND name=?", (table,))
            if not cursor.fetchone():
                print(f"Таблица '{table}' не существует!")
                return False
        
        # Проверяем количество записей
        cursor.execute("SELECT COUNT(*) FROM students")
        students_count = cursor.fetchone()[0]
        
        cursor.execute("SELECT COUNT(*) FROM groups")
        groups_count = cursor.fetchone()[0]
        
        cursor.execute("SELECT COUNT(*) FROM faculties")
        faculties_count = cursor.fetchone()[0]
        
        print("База данных корректна!")
        print(f"Статистика:")
        print(f"   Студентов: {students_count}")
        print(f"   Групп: {groups_count}")
        print(f"   Факультетов: {faculties_count}")
        
        # Показываем структуру таблиц
        print("Структура таблиц:")
        for table in tables:
            print(f"\nТаблица: {table}")
            cursor.execute(f"PRAGMA table_info({table})")
            columns = cursor.fetchall()
            for col in columns:
                print(f"  - {col[1]} ({col[2]})")
        
        conn.close()
        return True
        
    except sqlite3.Error as e:
        print(f"Ошибка при проверке базы данных: {e}")
        return False

if __name__ == '__main__':
    check_database()