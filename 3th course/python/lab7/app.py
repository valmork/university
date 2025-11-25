import threading
import webbrowser
from flask import Flask, render_template, request, redirect, url_for, flash
import sqlite3
from models import init_db, get_db_connection, student_exists, email_exists, phone_exists
from datetime import datetime
import os

app = Flask(__name__)
app.secret_key = 'your_secret_key_here'

# Инициализация базы данных
print("Инициализация базы данных...")
init_db()

@app.route('/')
def index():
    """Главная страница - отображение списка студентов"""
    conn = get_db_connection()
    
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
    
    conn.close()
    return render_template('index.html', students=students)

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
        
        # Валидация данных
        if not full_name or not birth_date or not group_name or not enrollment_year:
            flash('Пожалуйста, заполните все обязательные поля!', 'error')
            return redirect(url_for('add_student'))
        
        # Проверка на дубликат
        if student_exists(full_name, birth_date, group_name):
            flash('Студент с такими ФИО, датой рождения и группой уже существует!', 'error')
            return redirect(url_for('add_student'))
        
        # Дополнительные проверки (опционально)
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
        except sqlite3.IntegrityError:
            flash('Ошибка: студент с такими данными уже существует!', 'error')
        except sqlite3.Error as e:
            flash(f'Ошибка при добавлении студента: {str(e)}', 'error')
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
        conn.execute('DELETE FROM students WHERE id = ?', (student_id,))
        conn.commit()
        flash(f'Студент {student["full_name"]} успешно удален!', 'success')
    except sqlite3.Error as e:
        flash(f'Ошибка при удалении студента: {str(e)}', 'error')
    finally:
        conn.close()
    
    return redirect(url_for('index'))

@app.route('/delete_form')
def delete_form():
    """Страница с формой удаления студентов"""
    conn = get_db_connection()
    
    students = conn.execute('''
        SELECT 
            id, 
            full_name,
            group_name
        FROM students
        ORDER BY full_name
    ''').fetchall()
    
    conn.close()
    return render_template('delete_student.html', students=students)



def open_browser():
    webbrowser.open_new("http://127.0.0.1:5001")

if __name__ == '__main__':
# Запускаем браузер через 1 секунду после старта сервера
    threading.Timer(0.5, open_browser).start()
    app.run(debug=True, port=5001)