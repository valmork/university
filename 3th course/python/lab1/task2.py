def main():
    # Инициализация списка с элементами разных типов
    my_list = [10, -5, 3.14, "hello", 150.5, -20, "123", 75.8, True, 200.7]
    
    while True:
        print("\n" + "="*50)
        print("МЕНЮ ПРОГРАММЫ:")
        print("1 - Показать значения списка")
        print("2 - Добавить элемент в начало списка")
        print("3 - Удалить первый элемент списка")
        print("4 - Сформировать кортеж из вещественных элементов > 100")
        print("5 - Найти сумму целочисленных отрицательных элементов")
        print("6 - Сформировать строку и посчитать количество цифр")
        print("7 - Разница множеств М2 и М1")
        print("8 - Словарь с четными ключами")
        print("0 - Выход")
        print("="*50)
        
        choice = input("Выберите пункт меню: ")
        print(f"Вы ввели {choice}")        
        if choice == '1':
            show_list(my_list)
        elif choice == '2':
            add_to_beginning(my_list)
        elif choice == '3':
            remove_first_element(my_list)
        elif choice == '4':
            create_float_tuple(my_list)
        elif choice == '5':
            sum_negative_integers(my_list)
        elif choice == '6':
            count_digits_in_string(my_list)
        elif choice == '7':
            set_difference(my_list)
        elif choice == '8':
            create_dict_with_even_keys(my_list)
        elif choice == '0':
            print("Выход из программы...")
            break
        else:
            print("Неверный выбор! Попробуйте снова.")

def show_list(lst):
    #Показать значения списка на экране
    print("\nТекущий список:")
    for i, item in enumerate(lst):
        print(f"{i}: {item} ({type(item).__name__})")

def add_to_beginning(lst):
    #Добавление нового элемента в начало списка
    print("\nДобавление элемента в начало списка")
    print("Доступные типы элементов:")
    print("1 - Целое число")
    print("2 - Вещественное число")
    print("3 - Строка")
    print("4 - Логическое значение")
    
    type_choice = input("Выберите тип элемента: ")
    
    if type_choice == '1':
        try:
            value = int(input("Введите целое число: "))
            lst.insert(0, value)
            print(f"Добавлено число: {value}")
        except ValueError:
            print("Ошибка: введите корректное целое число!")
    
    elif type_choice == '2':
        try:
            value = float(input("Введите вещественное число: "))
            lst.insert(0, value)
            print(f"Добавлено вещественное число: {value}")
        except ValueError:
            print("Ошибка: введите корректное число!")
    
    elif type_choice == '3':
        value = input("Введите строку: ")
        lst.insert(0, value)
        print(f"Добавлена строка: '{value}'")
    
    elif type_choice == '4':
        value = input("Введите логическое значение (True/False): ").lower()
        if value == 'true':
            lst.insert(0, True)
            print("Добавлено значение: True")
        elif value == 'false':
            lst.insert(0, False)
            print("Добавлено значение: False")
        else:
            print("Ошибка: введите 'True' или 'False'!")
    
    else:
        print("Неверный выбор типа!")

def remove_first_element(lst):
    #Удаление первого элемента списка
    if len(lst) > 0:
        removed = lst.pop(0)
        print(f"Удален первый элемент: {removed}")
    else:
        print("Список пуст! Нечего удалять.")

def create_float_tuple(lst):
    #Сформировать кортеж из вещественных элементов > 100
    float_elements = []
    for item in lst:
        if isinstance(item, float) and item > 100:
            float_elements.append(item)
    
    result_tuple = tuple(float_elements)
    print(f"\nВещественные элементы списка большие 100: {result_tuple}")
    
    if not result_tuple:
        print("Подходящих элементов не найдено.")

def sum_negative_integers(lst):
    #Найти сумму всех целочисленных отрицательных элементов
    total = 0
    negative_integers = []
    
    for item in lst:
        if isinstance(item, int) and item < 0:
            total += item
            negative_integers.append(item)
    
    print(f"\nЦелочисленные отрицательные элементы: {negative_integers}")
    print(f"Их сумма: {total}")

def count_digits_in_string(lst):
    #Сформировать строку и посчитать количество цифр
    # Преобразуем все элементы в строки и объединяем
    combined_string = ''.join(str(item) for item in lst)
    
    # Считаем количество цифр
    digit_count = sum(1 for char in combined_string if char.isdigit())
    
    print(f"\nОбъединенная строка: {combined_string}")
    print(f"Количество цифр в строке: {digit_count}")

def set_difference(lst):
    #Разница множеств М2 и М1
    try:
        # Получение множества М1
        m1_input = input("Введите элементы множества М1 через пробел: ")
        m1_elements = m1_input.split()
        
        # Преобразуем в множество, конвертируя типы если возможно
        M1 = set()
        for elem in m1_elements:
            try:
                # Пробуем преобразовать в число
                if '.' in elem:
                    M1.add(float(elem))
                else:
                    M1.add(int(elem))
            except ValueError:
                # Если не число, оставляем как строку
                M1.add(elem)
        
        # Формируем множество М2 из списка
        M2 = set(lst)
        
        print(f"\nМножество М1: {M1}")
        print(f"Множество М2: {M2}")
        print(f"Разница М2 - М1: {M2 - M1}")
        
    except Exception as e:
        print(f"Ошибка при обработке множеств: {e}")

def create_dict_with_even_keys(lst):
    #Словарь с четными ключами и отображение элементов с четными ключами
    # Создаем словарь, где ключ - позиция элемента
    dictionary = {i: item for i, item in enumerate(lst)}
    
    print("\nПолный словарь:")
    for key, value in dictionary.items():
        print(f"Ключ {key}: {value}")
    
    print("\nЭлементы с четными ключами:")
    for key, value in dictionary.items():
        if key % 2 == 0:  # Четные ключи
            print(f"Ключ {key}: {value}")

if __name__ == "__main__":
    main()