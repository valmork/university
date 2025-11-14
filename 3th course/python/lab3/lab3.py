class Student:
    def __init__(self, zachetka, surname, name, patronymic, gender=None, birth_date=None,
                 phone=None, address=None, group=None):
        # Проверка обязательных параметров
        if not zachetka or not zachetka.strip():
            raise ValueError("Номер зачётки не может быть пустым")
        if not surname or not surname.strip():
            raise ValueError("Фамилия не может быть пустой")
        if not name or not name.strip():
            raise ValueError("Имя не может быть пустым")
        if not patronymic or not patronymic.strip():
            raise ValueError("Отчество не может быть пустым")
        
        self.zachetka = zachetka.strip()
        self.surname = surname.strip()
        self.name = name.strip()
        self.patronymic = patronymic.strip()
        self.gender = gender.strip() if gender and gender.strip() else None
        self.birth_date = birth_date.strip() if birth_date and birth_date.strip() else None
        self.phone = phone.strip() if phone and phone.strip() else None
        self.address = address.strip() if address and address.strip() else None
        self.group = group.strip() if group and group.strip() else None

    def __str__(self):
        return (f"Зачётка: {self.zachetka}\n"
                f"ФИО: {self.surname} {self.name} {self.patronymic}\n"
                f"Пол: {self.gender}\n"
                f"Дата рождения: {self.birth_date}\n"
                f"Телефон: {self.phone}\n"
                f"Адрес: {self.address}\n"
                f"Группа: {self.group}\n")

# список для хранения студентов
students = []


def add_student():
    print("\n=== Добавление студента ===")
    try:
        zachetka = input("Номер зачётки: ")
        surname = input("Фамилия: ")
        name = input("Имя: ")
        patronymic = input("Отчество: ")
        gender = input("Пол: ")
        birth_date = input("Дата рождения (дд.мм.гггг): ")
        phone = input("Телефон: ")
        address = input("Адрес: ")
        group = input("Группа: ")

        # Создаем объект студента (проверки выполнятся в конструкторе)
        student = Student(zachetka, surname, name, patronymic, gender,
                         birth_date, phone, address, group)
        students.append(student)
        print("Студент успешно добавлен!\n")
    
    except ValueError as e:
        print(f"Ошибка: {e}\n")
    except Exception as e:
        print(f"Произошла ошибка при добавлении студента: {e}\n")


def delete_student():
    print("\n=== Удаление студента ===")
    zachetka = input("Введите номер зачётки студента для удаления: ").strip()
    if not zachetka:
        print("Номер зачётки не может быть пустым.\n")
        return
        
    for student in students:
        if student.zachetka == zachetka:
            students.remove(student)
            print("Студент успешно удалён!\n")
            return
    print("Студент с таким номером зачётки не найден.\n")


def show_all_students():
    print("\n=== Список студентов ===")
    if not students:
        print("Список пуст.\n")
        return
    for i, student in enumerate(students, 1):
        print(f"--- Студент #{i} ---")
        print(student)


def search_by_group():
    print("\n=== Поиск студентов по группе ===")
    group = input("Введите название группы: ").strip()
    if not group:
        print("Название группы не может быть пустым.\n")
        return
        
    found = [s for s in students if s.group and s.group.lower() == group.lower()]
    if not found:
        print("Студенты не найдены.\n")
    else:
        for s in found:
            print(s)


def main_menu():
    while True:
        print("=== МЕНЮ ===")
        print("1. Добавить студента")
        print("2. Удалить студента")
        print("3. Показать всех студентов")
        print("4. Найти студентов по группе")
        print("0. Выход")

        choice = input("Выберите пункт меню: ").strip()

        if choice == "1":
            add_student()
        elif choice == "2":
            delete_student()
        elif choice == "3":
            show_all_students()
        elif choice == "4":
            search_by_group()
        elif choice == "0":
            print("Программа завершена.")
            break
        else:
            print("Неверный пункт меню. Попробуйте снова.\n")


if __name__ == "__main__":
    main_menu()