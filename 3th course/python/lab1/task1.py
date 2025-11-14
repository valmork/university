import math

def main():
    try:
        # Ввод данных
        x = float(input("Введите значение x: "))

        if x == 0:
            print("Ошибка: x не может быть равен 0")
            exit()

        n = float(input("Введите значение n: "))
        
        if n <= 0:
            print("Ошибка: n должно быть положительным числом")
            exit()
                
        # Проверка для корня n-й степени из синуса
        sin_value = math.sin(x**n)
        if sin_value < 0 and n % 2 == 0:
            print("Ошибка: нельзя извлечь корень четной степени из отрицательного числа")
            exit()
        
        # Вычисление по частям
        # 1. tg(x)/x
        part1 = math.tan(x) / x
        
        # 2. корень n-й степени из sin(x^n)
        if sin_value >= 0:
            part2 = sin_value ** (1/n)
        else:
            part2 = -((-sin_value) ** (1/n))
        
        # 3. e^((n+1)(x+2))
        part3 = math.exp((n + 1) *(x + 2))
        
        # Итоговый результат
        result = part1 + part2 + part3
        
        # Вывод результатов
        print(f"\nРезультаты вычислений:")
        print(f"tg({x})/{x} = {part1}")
        print(f"корень {n}-й степени из sin({x}^{n}) = {part2}")
        print(f"e^(({n}+1)*({x}+2)) = {part3}")
        print(f"Итоговый результат: {result}")
        
    except ValueError:
        print("Ошибка: введено нечисловое значение")
    except OverflowError:
        print("Ошибка: слишком большое значение для вычисления")
    except Exception as e:
        print(f"Произошла ошибка: {e}")

if __name__ == "__main__":
    main()