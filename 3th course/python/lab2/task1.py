from math import tan, sin, e
from operator import truediv

def check(condition, error_message):
    return lambda x: (condition(x), x, error_message)

def get_value(prompt, check_fn):
    value = float(input(prompt))
    condition_result, checked_value, error_msg = check_fn(value)
    
    def success_handler(v):
        return v
    
    def error_handler(v, msg):
        print(f"Ошибка: {msg}")
        return get_value(prompt, check_fn)  # рекурсивный повторный ввод
    
    # Комбинатор для обработки условий
    return (condition_result and success_handler(checked_value)) or error_handler(checked_value, error_msg)

def safe_divide(a, b):
    def division_attempt():
        return truediv(a, b)
    
    def handle_zero_division():
        print("Ошибка: Деление на ноль")
        return float('inf')
    
    # Проверяем, знаменатель
    is_zero = lambda x: x == 0
    return (not is_zero(b) and division_attempt()) or handle_zero_division()

def compute(x, n):
    #Вычисление
    term1 = safe_divide(tan(x), x)
    term2 = (sin(x) ** safe_divide(n, n)) ** safe_divide(1, n)
    term3 = e ** ((n + 1) * (x + 2))
    
    return term1 + term2 + term3

check_nonzero = check(lambda x: x != 0, "x не может быть равен 0 (деление на ноль).")
check_positive = check(lambda n: n > 0, "n должно быть натуральным числом (>0).")

# Получаем значения
x = get_value("x: ", check_nonzero)
n = get_value("n: ", check_positive)

print("Результат:", compute(x, n))