import tkinter as tk
from tkinter import ttk, messagebox


# ======= Класс студента =======
class Student:
    def __init__(self, zachetka, surname, name, patronymic,
                 gender=None, birth_date=None, phone=None, address=None, group=None):
        # Проверка обязательных параметров
        if not all([zachetka, surname, name, patronymic]):
            raise ValueError("Обязательные поля (зачётка, фамилия, имя, отчество) должны быть заполнены.")

        # Приведение опциональных параметров к None, если они пустые
        self.gender = gender if gender and gender.strip() else None
        self.birth_date = birth_date if birth_date and birth_date.strip() else None
        self.phone = phone if phone and phone.strip() else None
        self.address = address if address and address.strip() else None
        self.group = group if group and group.strip() else None

        # Обязательные поля
        self.zachetka = zachetka.strip()
        self.surname = surname.strip()
        self.name = name.strip()
        self.patronymic = patronymic.strip()

    def __str__(self):
        return (f"Зачётка: {self.zachetka}\n"
                f"ФИО: {self.surname} {self.name} {self.patronymic}\n"
                f"Пол: {self.gender if self.gender else '-'}\n"
                f"Дата рождения: {self.birth_date if self.birth_date else '-'}\n"
                f"Телефон: {self.phone if self.phone else '-'}\n"
                f"Адрес: {self.address if self.address else '-'}\n"
                f"Группа: {self.group if self.group else '-'}\n")


students = []


# ======= Функции для обработки событий =======
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

    # Проверяем только обязательные поля
    if not all([zachetka, surname, name, patronymic]):
        messagebox.showwarning("Ошибка", "Заполните все обязательные поля (зачётка, фамилия, имя, отчество)!")
        return

    # Приводим пустые опциональные поля к None
    gender = gender if gender else None
    birth_date = birth_date if birth_date else None
    phone = phone if phone else None
    address = address if address else None
    group = group if group else None

    try:
        student = Student(zachetka, surname, name, patronymic, gender,
                          birth_date, phone, address, group)
    except ValueError as e:
        messagebox.showerror("Ошибка", str(e))
        return

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
    gender_var.set('')  # сбрасываем пол


# ======= Интерфейс =======
root = tk.Tk()
root.title("Учёт студентов")
root.geometry("700x600")

# Поля ввода
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

# Радиокнопки для выбора пола
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

# Поле для вывода результатов
text_display = tk.Text(root, width=80, height=15)
text_display.grid(row=11, column=0, columnspan=3, pady=10)

root.mainloop()
