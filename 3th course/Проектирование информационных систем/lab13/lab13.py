import sqlite3
from datetime import datetime
import os

DB_FILE = "center.db"

# --- Инициализация тестовой базы ---
def init_test_db():
    conn = sqlite3.connect(DB_FILE)
    cur = conn.cursor()
    # Создаём таблицы (сотрудники, клиенты, сертификаты)
    cur.execute("""CREATE TABLE IF NOT EXISTS employees (
        id INTEGER PRIMARY KEY,
        name TEXT,
        role TEXT
    )""")
    cur.execute("""CREATE TABLE IF NOT EXISTS clients (
        id INTEGER PRIMARY KEY,
        name TEXT,
        contact TEXT
    )""")
    cur.execute("""CREATE TABLE IF NOT EXISTS certificates (
        id INTEGER PRIMARY KEY,
        client_id INTEGER,
        status TEXT
    )""")
    conn.commit()
    conn.close()

# --- Тестовые сценарии ---
def run_tests():
    conn = sqlite3.connect(DB_FILE)
    cur = conn.cursor()
    test_results = []

    # 1. Добавление сотрудника
    try:
        cur.execute("INSERT INTO employees (name, role) VALUES (?, ?)", ("Иванов И.И.", "Сотрудник"))
        conn.commit()
        test_results.append("Добавление сотрудника: PASS")
    except Exception as e:
        test_results.append(f"Добавление сотрудника: FAIL ({e})")

    # 2. Назначение администратора
    try:
        cur.execute("INSERT INTO employees (name, role) VALUES (?, ?)", ("Петров П.П.", "Администратор"))
        conn.commit()
        test_results.append("Назначение администратора: PASS")
    except Exception as e:
        test_results.append(f"Назначение администратора: FAIL ({e})")

    # 3. Добавление клиента
    try:
        cur.execute("INSERT INTO clients (name, contact) VALUES (?, ?)", ("ООО Ромашка", "info@romashka.ru"))
        conn.commit()
        test_results.append("Добавление клиента: PASS")
    except Exception as e:
        test_results.append(f"Добавление клиента: FAIL ({e})")

    # 4. Добавление сертификата
    try:
        cur.execute("INSERT INTO certificates (client_id, status) VALUES (?, ?)", (1, "Выдан"))
        conn.commit()
        test_results.append("Добавление сертификата: PASS")
    except Exception as e:
        test_results.append(f"Добавление сертификата: FAIL ({e})")

    # 5. Изменение статуса сертификата
    try:
        cur.execute("UPDATE certificates SET status=? WHERE id=?", ("Отозван", 1))
        conn.commit()
        test_results.append("Изменение статуса сертификата: PASS")
    except Exception as e:
        test_results.append(f"Изменение статуса сертификата: FAIL ({e})")

    # 6. Проверка прав доступа администратора
    try:
        cur.execute("SELECT * FROM employees WHERE role='Администратор'")
        admin_count = len(cur.fetchall())
        assert admin_count >= 1
        test_results.append("Проверка прав администратора: PASS")
    except Exception as e:
        test_results.append(f"Проверка прав администратора: FAIL ({e})")

    conn.close()
    return test_results

# --- Сохранение протокола тестирования ---
def save_protocol(results, filename="test_protocol.txt"):
    print("Протокол сохранён в:", os.path.abspath(filename))
    with open(filename, "w", encoding="utf-8") as f:
        f.write(f"Протокол тестирования ИС центра стандартизации и метрологии\n")
        f.write(f"Дата: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n\n")
        for r in results:
            f.write(r + "\n")

# --- Основной запуск ---
if __name__ == "__main__":
    init_test_db()
    results = run_tests()
    save_protocol(results)
    for r in results:
        print(r)
