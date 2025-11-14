import tkinter as tk
from tkinter import ttk, messagebox, filedialog
import json
import os


# ======= Класс студента =======
class Student:
    def __init__(self, zachetka, surname, name, patronymic,
                 gender=None, birth_date=None, phone=None, address=None, group=None):
        if not all([zachetka, surname, name, patronymic]):
            raise ValueError("Обязательные поля (зачётка, фамилия, имя, отчество) должны быть заполнены.")

        self.zachetka = zachetka.strip()
        self.surname = surname.strip()
        self.name = name.strip()
        self.patronymic = patronymic.strip()
        self.gender = gender.strip() if gender else None
        self.birth_date = birth_date.strip() if birth_date else None
        self.phone = phone.strip() if phone else None
        self.address = address.strip() if address else None
        self.group = group.strip() if group else None

    def __str__(self):
        return (f"Зачётка: {self.zachetka}\n"
                f"ФИО: {self.surname} {self.name} {self.patronymic}\n"
                f"Пол: {self.gender if self.gender else '-'}\n"
                f"Дата рождения: {self.birth_date if self.birth_date else '-'}\n"
                f"Телефон: {self.phone if self.phone else '-'}\n"
                f"Адрес: {self.address if self.address else '-'}\n"
                f"Группа: {self.group if self.group else '-'}\n")

    def to_dict(self):
        """Преобразование объекта в словарь для сохранения"""
        return {
            "zachetka": self.zachetka,
            "surname": self.surname,
            "name": self.name,
            "patronymic": self.patronymic,
            "gender": self.gender,
            "birth_date": self.birth_date,
            "phone": self.phone,
            "address": self.address,
            "group": self.group
        }

    @staticmethod
    def from_dict(data):
        """Создание объекта из словаря"""
        return Student(**data)


students = []
current_file = None  # путь к открытому файлу


# ======= Функции обработки событий =======
def add_student():
    zachetka = entry_zachetka.get().strip()
    surname = entry_surname.get().strip()
    name = entry_name.get().strip()
    patronymic = entry_patronymic.get().strip()
    gender = gender_var.get().strip()
    birth_date = entry_birth.get().strip()
    phone = entry_phone.get().strip()
    address = entry_address.get().strip()
    group = combo_group.get().strip()

    if not all([zachetka, surname, name, patronymic]):
        messagebox.showwarning("Ошибка", "Заполните обязательные поля: зачётка, фамилия, имя, отчество.")
        return

    student = Student(zachetka, surname, name, patronymic, gender, birth_date, phone, address, group)
    students.append(student)
    messagebox.showinfo("Успех", "Студент успешно добавлен!")
    clear_fields()
    show_all_students()


def delete_student():
    zachetka = entry_zachetka.get().strip()
    for s in students:
        if s.zachetka == zachetka:
            students.remove(s)
            messagebox.showinfo("Удаление", "Студент успешно удалён.")
            show_all_students()
            return
    messagebox.showwarning("Ошибка", "Студент с таким номером зачётки не найден.")


def show_all_students():
    text_display.delete(1.0, tk.END)
    if not students:
        text_display.insert(tk.END, "Список студентов пуст.\n")
    else:
        for i, s in enumerate(students, 1):
            text_display.insert(tk.END, f"--- Студент #{i} ---\n{s}\n")


def search_by_group():
    group = combo_group.get().strip()
    text_display.delete(1.0, tk.END)
    found = [s for s in students if s.group == group]
    if not found:
        text_display.insert(tk.END, "Студенты не найдены.\n")
    else:
        for s in found:
            text_display.insert(tk.END, str(s) + "\n")


def clear_fields():
    entry_zachetka.delete(0, tk.END)
    entry_surname.delete(0, tk.END)
    entry_name.delete(0, tk.END)
    entry_patronymic.delete(0, tk.END)
    entry_birth.delete(0, tk.END)
    entry_phone.delete(0, tk.END)
    entry_address.delete(0, tk.END)
    combo_group.set('')
    gender_var.set('')


# ======= Работа с файлами =======
def new_file():
    global students, current_file
    if messagebox.askyesno("Новый файл", "Очистить текущие данные?"):
        students = []
        current_file = None
        clear_fields()
        show_all_students()


def open_file():
    global students, current_file
    path = filedialog.askopenfilename(filetypes=[("JSON файлы", "*.json")])
    if not path:
        return
    try:
        with open(path, "r", encoding="utf-8") as f:
            data = json.load(f)  # <- здесь важно, что JSON корректный
            students = [Student.from_dict(s) for s in data]
        current_file = path
        show_all_students()
        messagebox.showinfo("Открытие", f"Файл успешно открыт: {os.path.basename(path)}")
    except Exception as e:
        messagebox.showerror("Ошибка", f"Не удалось открыть файл:\n{e}")



def save_file():
    global current_file
    if not current_file:
        save_file_as()
        return
    try:
        with open(current_file, "w", encoding="utf-8") as f:
            json.dump([s.to_dict() for s in students], f, ensure_ascii=False, indent=4)
        messagebox.showinfo("Сохранение", f"Изменения сохранены в {os.path.basename(current_file)}")
    except Exception as e:
        messagebox.showerror("Ошибка", f"Не удалось сохранить файл:\n{e}")


def save_file_as():
    global current_file
    path = filedialog.asksaveasfilename(defaultextension=".json",
                                        filetypes=[("JSON файлы", "*.json")])
    if not path:
        return
    try:
        with open(path, "w", encoding="utf-8") as f:
            json.dump([s.to_dict() for s in students], f, ensure_ascii=False, indent=4)
        current_file = path
        messagebox.showinfo("Сохранение", f"Файл успешно сохранён: {os.path.basename(path)}")
    except Exception as e:
        messagebox.showerror("Ошибка", f"Не удалось сохранить файл:\n{e}")


def exit_program():
    if messagebox.askokcancel("Выход", "Вы действительно хотите выйти?"):
        root.destroy()


def show_about():
    messagebox.showinfo("О разработчике", 
                        "Программа учёта студентов\n"
                        "Разработчик: Королев А. С.\n"
                        "Версия: 1.0\n"
                        "© 2025")


# ======= Интерфейс =======
root = tk.Tk()
root.title("Учёт студентов")
root.geometry("700x600")

# Главное меню
menu_bar = tk.Menu(root)

# Меню "Файл"
file_menu = tk.Menu(menu_bar, tearoff=0)
file_menu.add_command(label="Создать", command=new_file)
file_menu.add_command(label="Открыть", command=open_file)
file_menu.add_separator()
file_menu.add_command(label="Сохранить", command=save_file)
file_menu.add_command(label="Сохранить как...", command=save_file_as)
file_menu.add_separator()
file_menu.add_command(label="Выход", command=exit_program)
menu_bar.add_cascade(label="Файл", menu=file_menu)

# Меню "Справка"
help_menu = tk.Menu(menu_bar, tearoff=0)
help_menu.add_command(label="О разработчике", command=show_about)
menu_bar.add_cascade(label="Справка", menu=help_menu)

root.config(menu=menu_bar)

# ======= Форма ввода =======
tk.Label(root, text="Номер зачётки:").grid(row=0, column=0, sticky="w")
entry_zachetka = tk.Entry(root)
entry_zachetka.grid(row=0, column=1)

tk.Label(root, text="Фамилия:").grid(row=1, column=0, sticky="w")
entry_surname = tk.Entry(root)
entry_surname.grid(row=1, column=1)

tk.Label(root, text="Имя:").grid(row=2, column=0, sticky="w")
entry_name = tk.Entry(root)
entry_name.grid(row=2, column=1)

tk.Label(root, text="Отчество:").grid(row=3, column=0, sticky="w")
entry_patronymic = tk.Entry(root)
entry_patronymic.grid(row=3, column=1)

# Пол
tk.Label(root, text="Пол:").grid(row=4, column=0, sticky="w")
gender_var = tk.StringVar(value='')
tk.Radiobutton(root, text="Мужской", variable=gender_var, value="Мужской").grid(row=4, column=1, sticky="w")
tk.Radiobutton(root, text="Женский", variable=gender_var, value="Женский").grid(row=4, column=2, sticky="w")

# Остальные поля
tk.Label(root, text="Дата рождения:").grid(row=5, column=0, sticky="w")
entry_birth = tk.Entry(root)
entry_birth.grid(row=5, column=1)

tk.Label(root, text="Телефон:").grid(row=6, column=0, sticky="w")
entry_phone = tk.Entry(root)
entry_phone.grid(row=6, column=1)

tk.Label(root, text="Адрес:").grid(row=7, column=0, sticky="w")
entry_address = tk.Entry(root)
entry_address.grid(row=7, column=1)

tk.Label(root, text="Группа:").grid(row=8, column=0, sticky="w")
combo_group = ttk.Combobox(root, values=["31ПИ", "31ПГ", "31ИВТ"])
combo_group.grid(row=8, column=1)

# Кнопки управления
tk.Button(root, text="Добавить", command=add_student).grid(row=9, column=0, pady=5)
tk.Button(root, text="Удалить", command=delete_student).grid(row=9, column=1, pady=5)
tk.Button(root, text="Показать всех", command=show_all_students).grid(row=9, column=2, pady=5)
tk.Button(root, text="Поиск по группе", command=search_by_group).grid(row=10, column=1, pady=5)
tk.Button(root, text="Очистить поля", command=clear_fields).grid(row=10, column=2, pady=5)

# Поле вывода
text_display = tk.Text(root, width=80, height=15)
text_display.grid(row=11, column=0, columnspan=3, pady=10)

root.mainloop()
