import math
from functools import reduce, partial

# --- Комбинаторы высшего порядка ---

def compose(*funcs):
    """Композиция функций справа налево."""
    return lambda x: reduce(lambda acc, f: f(acc), reversed(funcs), x)

def selector(pred, f_true, f_false):
    """Возвращает функцию, выбирающую между двумя функциями без if."""
    return lambda x: (f_true, f_false)[not pred(x)](x)

# --- Базовые проверки ---

def len_is(n):
    return lambda args: len(args) == n

def all_positive(args):
    return all(map(lambda a: a > 0, args))

# --- Ошибочные сообщения ---

def err_len(expected):
    return lambda args: f"Неправильный формат ввода: ожидалось {expected} аргументов, получено {len(args)}!"

def err_positive(args):
    return "Ошибка: все аргументы должны быть положительными числами!"

# --- Вычисления площадей (чистые функции) ---

def triangle_calc(args): base, h = args; return 0.5 * base * h
def circle_calc(args): r, = args; return math.pi * r**2
def parallelogram_calc(args): base, h = args; return base * h
def exit_action(args): return "Выход из программы."

# --- Конвейеры без if/try/except ---

triangle_area = compose(
    selector(len_is(2), 
        selector(all_positive, triangle_calc, err_positive),
        err_len(2)
    )
)

circle_area = compose(
    selector(len_is(1),
        selector(all_positive, circle_calc, err_positive),
        err_len(1)
    )
)

parallelogram_area = compose(
    selector(len_is(2),
        selector(all_positive, parallelogram_calc, err_positive),
        err_len(2)
    )
)

exit_wrapper = selector(len_is(0), exit_action,
    lambda args: f"Неправильный формат ввода: ожидалось 0 аргументов, получено {len(args)}!"
)

# --- Таблица функций ---

area_rules = {
    "T": triangle_area,
    "C": circle_area,
    "P": parallelogram_area,
    "E": exit_wrapper
}

# --- Тестовые данные ---

L = [
    ['T', 'C', 'P', 'E'],
    [1, 3],
    [2.5],
    [2.5, 2],
    []
]

# --- Выполнение ---

print(*map(lambda x: area_rules[x[0]](x[1]), zip(L[0], L[1:])), sep='\n')
