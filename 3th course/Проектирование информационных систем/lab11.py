import pymysql
import tkinter as tk
from tkinter import ttk, messagebox


# ░░░ ПОДКЛЮЧЕНИЕ К MySQL ░░░
DB_HOST = "localhost"
DB_PORT = 3306
DB_USER = "root"
DB_PASS = ""
DB_NAME = "sert_center"

conn = pymysql.connect(
    host=DB_HOST,
    port=DB_PORT,
    user=DB_USER,
    password=DB_PASS,
    database=DB_NAME,
    charset="utf8mb4"
)

cursor = conn.cursor()

# ░░░ ЧТЕНИЕ ВСЕХ ТАБЛИЦ ░░░
def get_tables():
    cursor.execute("SHOW TABLES")
    return [row[0] for row in cursor.fetchall()]


# ░░░ ЧТЕНИЕ ПОЛЕЙ ТАБЛИЦЫ ░░░
def get_fields(table):
    cursor.execute(f"DESCRIBE `{table}`")
    return [row[0] for row in cursor.fetchall()]


# ░░░ GUI ░░░
root = tk.Tk()
root.title("Конструктор SQL-запросов (MySQL)")
root.geometry("900x600")


# --- выбор таблицы ---
tk.Label(root, text="Таблица:").grid(row=0, column=0, padx=5, pady=5)
table_combo = ttk.Combobox(root, state="readonly", width=40)
table_combo.grid(row=0, column=1, padx=5, pady=5)
table_combo["values"] = get_tables()


# --- список полей ---
tk.Label(root, text="Поля:").grid(row=1, column=0, padx=5, pady=5)
fields_list = tk.Listbox(root, selectmode=tk.MULTIPLE, width=40, height=10)
fields_list.grid(row=1, column=1, padx=5, pady=5)


# обновление полей при выборе таблицы
def on_table_select(event):
    fields_list.delete(0, tk.END)
    table = table_combo.get()
    if table:
        for field in get_fields(table):
            fields_list.insert(tk.END, field)


table_combo.bind("<<ComboboxSelected>>", on_table_select)


# --- условие ---
tk.Label(root, text="Условие WHERE (пример: статус='Одобрено'):").grid(row=2, column=0)
cond_entry = tk.Entry(root, width=50)
cond_entry.grid(row=2, column=1, padx=5, pady=5)


# --- SQL-окно ---
tk.Label(root, text="SQL-запрос:").grid(row=3, column=0)
sql_text = tk.Text(root, width=80, height=5)
sql_text.grid(row=3, column=1, padx=5, pady=5)


# --- таблица результатов ---
result_table = ttk.Treeview(root)
result_table.grid(row=5, column=0, columnspan=3, padx=5, pady=5)


# ░░░ КНОПКИ ░░░

def build_query():
    table = table_combo.get()
    if not table:
        messagebox.showwarning("Ошибка", "Выберите таблицу!")
        return

    selected_fields = [fields_list.get(i) for i in fields_list.curselection()]
    field_str = ", ".join(f"`{f}`" for f in selected_fields) if selected_fields else "*"

    cond = cond_entry.get().strip()

    query = f"SELECT {field_str} FROM `{table}`"
    if cond:
        query += f" WHERE {cond}"

    sql_text.delete(1.0, tk.END)
    sql_text.insert(tk.END, query)


def run_query():
    query = sql_text.get(1.0, tk.END).strip()

    try:
        cursor.execute(query)
        rows = cursor.fetchall()

        # Очистка таблицы
        result_table.delete(*result_table.get_children())

        # Настройка заголовков
        columns = [desc[0] for desc in cursor.description]
        result_table["columns"] = columns
        result_table["show"] = "headings"

        for col in columns:
            result_table.heading(col, text=col)

        for row in rows:
            result_table.insert("", tk.END, values=row)

    except Exception as e:
        messagebox.showerror("Ошибка SQL", str(e))


build_btn = tk.Button(root, text="Сформировать SQL", command=build_query)
build_btn.grid(row=4, column=0, padx=5, pady=5)

run_btn = tk.Button(root, text="Выполнить", command=run_query)
run_btn.grid(row=4, column=1, padx=5, pady=5)


root.mainloop()