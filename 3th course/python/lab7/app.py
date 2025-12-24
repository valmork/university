import threading
import webbrowser
from flask import Flask, render_template, request, redirect, url_for, flash
import sqlite3
from models import init_db, get_db_connection, student_exists, email_exists, phone_exists
from datetime import datetime
import os

app = Flask(__name__)
app.secret_key = 'your_secret_key_here'

# Добавим отладочную информацию
print("=" * 60)
print(f"Запуск приложения управления студентами")
print(f"Текущая директория: {os.getcwd()}")
print(f"Файл базы будет создан в: {os.path.join(os.getcwd(), 'students.db')}")
print("=" * 60)

# Инициализация базы данных
print("Инициализация базы данных...")
try:
    init_db()
    print("База данных готова к работе")
except Exception as e:
    print(f"Ошибка при инициализации базы: {e}")

@app.route('/')
def index():
    """Главная страница - отображение списка студентов"""
    conn = get_db_connection()
    
    try:
        students = conn.execute('''
            SELECT 
                id, 
                full_name, 
                birth_date,
                phone,
                email,
                enrollment_year,
                group_name
            FROM students
            ORDER BY full_name
        ''').fetchall()
        
        print(f"Загружено {len(students)} студентов из базы")
        return render_template('index.html', students=students)
    except Exception as e:
        print(f"Ошибка при загрузке студентов: {e}")
        flash('Ошибка при загрузке данных из базы', 'error')
        return render_template('index.html', students=[])
    finally:
        conn.close()

@app.route('/add', methods=['GET', 'POST'])
def add_student():
    """Добавление нового студента"""
    if request.method == 'POST':
        full_name = request.form['full_name'].strip()
        birth_date = request.form['birth_date']
        group_name = request.form['group_name'].strip()
        phone = request.form['phone'].strip()
        email = request.form['email'].strip()
        enrollment_year = request.form['enrollment_year']
        
        print(f"Попытка добавления студента: {full_name}, группа: {group_name}")
        
        # Валидация данных
        if not full_name or not birth_date or not group_name or not enrollment_year:
            flash('Пожалуйста, заполните все обязательные поля!', 'error')
            return redirect(url_for('add_student'))
        
        # Проверка на дубликат
        if student_exists(full_name, birth_date, group_name):
            flash('Студент с такими ФИО, датой рождения и группой уже существует!', 'error')
            return redirect(url_for('add_student'))
        
        # Дополнительные проверки
        if email and email_exists(email):
            flash('Студент с таким email уже существует!', 'error')
            return redirect(url_for('add_student'))
            
        if phone and phone_exists(phone):
            flash('Студент с таким телефоном уже существует!', 'error')
            return redirect(url_for('add_student'))
        
        conn = get_db_connection()
        try:
            conn.execute('''
                INSERT INTO students (full_name, birth_date, group_name, phone, email, enrollment_year)
                VALUES (?, ?, ?, ?, ?, ?)
            ''', (full_name, birth_date, group_name, phone, email, enrollment_year))
            conn.commit()
            flash('Студент успешно добавлен!', 'success')
            print(f"Студент {full_name} добавлен в базу")
        except sqlite3.IntegrityError as e:
            flash('Ошибка: студент с такими данными уже существует!', 'error')
            print(f"Ошибка IntegrityError: {e}")
        except sqlite3.Error as e:
            flash(f'Ошибка при добавлении студента: {str(e)}', 'error')
            print(f"Ошибка SQLite: {e}")
        finally:
            conn.close()
        
        return redirect(url_for('index'))
    
    return render_template('add_student.html', current_year=datetime.now().year)

@app.route('/delete/<int:student_id>', methods=['POST'])
def delete_student(student_id):
    """Удаление студента"""
    conn = get_db_connection()
    
    try:
        student = conn.execute('SELECT full_name FROM students WHERE id = ?', (student_id,)).fetchone()
        if student:
            conn.execute('DELETE FROM students WHERE id = ?', (student_id,))
            conn.commit()
            flash(f'Студент {student["full_name"]} успешно удален!', 'success')
            print(f"Студент {student['full_name']} удален из базы")
        else:
            flash('Студент не найден!', 'error')
    except sqlite3.Error as e:
        flash(f'Ошибка при удалении студента: {str(e)}', 'error')
        print(f"Ошибка при удалении: {e}")
    finally:
        conn.close()
    
    return redirect(url_for('index'))

@app.route('/delete_form')
def delete_form():
    """Страница с формой удаления студентов"""
    conn = get_db_connection()
    
    try:
        students = conn.execute('''
            SELECT 
                id, 
                full_name,
                group_name
            FROM students
            ORDER BY full_name
        ''').fetchall()
        return render_template('delete_student.html', students=students)
    finally:
        conn.close()

@app.route('/db_info')
def db_info():
    """Информация о базе данных"""
    conn = get_db_connection()
    try:
        count = conn.execute('SELECT COUNT(*) FROM students').fetchone()[0]
        return f'''
        <h2>Информация о базе данных</h2>
        <p>Путь к файлу: {os.path.join(os.getcwd(), 'students.db')}</p>
        <p>Всего студентов: {count}</p>
        <a href="/">На главную</a>
        '''
    finally:
        conn.close()

def open_browser():
    """Открыть браузер после запуска сервера"""
    webbrowser.open_new("http://127.0.0.1:5001")

if __name__ == '__main__':
    print("\n🌐 Запуск веб-сервера на порту 5001...")
    print("📱 Открытие браузера через 1 секунду...")
    
    # Запускаем браузер через 1 секунду
    threading.Timer(1.0, open_browser).start()
    
    app.run(debug=True, port=5001, use_reloader=False)