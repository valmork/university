from math import tan, sin, e

def check(condition, error_message):
    return lambda x: (condition(x) and True) or (_ for _ in ()).throw(AssertionError(error_message)) or x

check_nonzero = check(lambda x: x != 0, "x не может быть равен 0 (деление на ноль).")
check_positive = check(lambda n: n > 0, "n должно быть положительным числом.")

get_value = lambda prompt, check_fn: check_fn(float(input(prompt)))

x = get_value("x: ", check_nonzero)
n = get_value("n: ", check_positive)

compute = lambda x, n: (tan(x) / x) + (sin(x) ** (n / n)) ** (1 / n) + e ** ((n + 1) * (x + 2))

print("Результат:", compute(x, n))