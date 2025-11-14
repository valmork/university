import math

def main():
    print("Программа для вычисления площади фигур")
    
    while True:
        print("\nМеню:")
        print("«Т» - площадь равнобедренного треугольника")
        print("«С» - площадь круга") 
        print("«Р» - площадь параллелограмма")
        print("«Е» - выход из программы")
        
        choice = input("Выберите пункт меню: ").upper()
        
        if choice == 'Т':
            calculate_triangle_area()
        elif choice == 'С':
            calculate_circle_area()
        elif choice == 'Р':
            calculate_parallelogram_area()
        elif choice == 'Е':
            print("Выход из программы. До свидания!")
            break
        else:
            print("Ошибка: неверный пункт меню! Пожалуйста, выберите Т, С, Р или Е.")

def calculate_triangle_area():
    #Площадь равнобедренного треугольника
    try:
        base = float(input("Введите основание треугольника: "))
        height = float(input("Введите высоту треугольника: "))
        
        if base <= 0 or height <= 0:
            print("Ошибка: основание и высота должны быть положительными числами!")
            return
            
        area = 0.5 * base * height
        print(f"Площадь равнобедренного треугольника: {area:.2f}")
        
    except ValueError:
        print("Ошибка: введите числовые значения для основания и высоты!")

def calculate_circle_area():
    #Площадь круга
    try:
        radius = float(input("Введите радиус круга: "))
        
        if radius <= 0:
            print("Ошибка: радиус должен быть положительным числом!")
            return
            
        area = math.pi * radius ** 2
        print(f"Площадь круга: {area:.2f}")
        
    except ValueError:
        print("Ошибка: введите числовое значение для радиуса!")

def calculate_parallelogram_area():
    #Площадь параллелограмма
    try:
        base = float(input("Введите основание параллелограмма: "))
        height = float(input("Введите высоту параллелограмма: "))
        
        if base <= 0 or height <= 0:
            print("Ошибка: основание и высота должны быть положительными числами!")
            return
            
        area = base * height
        print(f"Площадь параллелограмма: {area:.2f}")
        
    except ValueError:
        print("Ошибка: введите числовые значения для основания и высоты!")


if __name__ == "__main__":
    main()