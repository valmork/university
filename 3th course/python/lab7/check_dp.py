import sqlite3
import os

def check_database():
    """Проверка структуры базы данных"""
    db_file = 'students.db'
    
    if not os.path.exists(db_file):
        print(f"❌ Файл базы данных '{db_file}' не существует!")
        print(f"   Полный путь: {os.path.abspath(db_file)}")
        return False
    
    print(f"✅ Файл базы найден: {os.path.abspath(db_file)}")
    
    try:
        conn = sqlite3.connect(db_file)
        cursor = conn.cursor()
        
        # Проверяем существование таблиц
        cursor.execute("SELECT name FROM sqlite_master WHERE type='table'")
        tables = cursor.fetchall()
        
        print(f"\n📋 Таблицы в базе данных:")
        for table in tables:
            print(f"   - {table[0]}")
        
        # Проверяем таблицу students
        if ('students',) in tables:
            print("\n🔍 Проверяем таблицу 'students':")
            
            # Структура таблицы
            cursor.execute("PRAGMA table_info(students)")
            columns = cursor.fetchall()
            print("   Столбцы:")
            for col in columns:
                print(f"     - {col[1]} ({col[2]})")
            
            # Количество записей
            cursor.execute("SELECT COUNT(*) FROM students")
            students_count = cursor.fetchone()[0]
            print(f"   Количество записей: {students_count}")
            
            # Показать первые 10 записей
            if students_count > 0:
                print(f"\n   Первые {min(10, students_count)} записей:")
                cursor.execute("SELECT * FROM students LIMIT 10")
                students = cursor.fetchall()
                for student in students:
                    print(f"     ID: {student[0]}, ФИО: {student[1]}, Группа: {student[3]}")
        else:
            print("Таблица 'students' не существует!")
            return False
        
        # Размер файла
        file_size = os.path.getsize(db_file)
        print(f"\n💾 Размер файла базы данных: {file_size} байт ({file_size/1024:.2f} KB)")
        
        conn.close()
        return True
        
    except sqlite3.Error as e:
        print(f"Ошибка при проверке базы данных: {e}")
        return False

if __name__ == '__main__':
    check_database()