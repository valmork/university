import pandas as pd
import numpy as np
import scipy as ss
import seaborn as sns
import matplotlib.pyplot as plt
import pylab as py
import statsmodels.stats.api as sms

df = pd.read_excel('Модуль_МС_2025.xlsx')  #чтение датафрейма df (таблицы данных)

print(df.p_9.describe())  #основные числовые характеристики
df.p_9.mode()   # мода
print("Мода: ", ss.stats.mode(df.p_9, keepdims=True)[0][0])   # (только первая)

print("Медиана: ", df.p_9.median())   #медиана
np.median(df.p_9)
print("Ср. знач. выборки: ", df.p_9.mean())   #среднее значение выборки
np.mean(df.p_9)

print("Размах: ", np.percentile(df.p_9, [0, 100])[1] - np.percentile(df.p_9, [0, 100])[0])   #размах

print("Дисперсия выборки: ", df.p_9.var())   # дисперсия выборки
print("Дисперсия ген. совокупности: ", np.var(df.p_9))    # дисперсия генеральной совокупности

print("Стандартное отклонение: ", df.p_9.std())     #стандартное отклонение СО
print("СКО: ", np.std(df.p_9))       #среднеквадратическое отклонение СКО
print("СО: ", np.std(df.p_9, ddof=1))      #стандартное отклонение СО

print("SE: ", df.p_9.sem())      #стандартная ошибка среднего  (se)
ss.stats.sem(df.p_9)      #стандартная ошибка среднего  (se)

print("3я квантиль, 75%-ый процентиль: ", df.p_9.quantile(q=0.75))     #3я квантиль, 75%-ый процентиль
print("50%-ный и 70%-ный процентили: ", df.p_9.quantile(q=[0.5, 0.7]))     #50%-ный и 70%-ный процентили

plt.figure(figsize=(16,6))   #размеры рисунка
sns.boxplot(df.p_9, orient='horizantal')    #ящик с усами

plt.figure(figsize=(16,6))                                   #размеры рисунка
df.p_9.plot(kind="hist", fontsize=8, bins=9)     #гистограмма
#  df.p_9.plot(kind="hist", bins=10, fontsize=8)  можно указать число интервалов группировки
AxesSubplot:'Frequency'         #подпись вертикальной оси
py.show()

ss.stats.probplot(df.p_9, dist="norm", plot=py)    #QQ-plot
py.show()

mu = df.p_9.mean()
std = df.p_9.std()
R = df.p_9.max() - df.p_9.min()
h = R / 9

df.p_9.plot(kind="hist", bins=9, fontsize=8)

xmin, xmax = plt.xlim()
x = np.arange (-2, 11, 0.5)
p = ss.stats.norm.pdf(x, mu, std)*df.p_9.count()*h

plt.plot(x, p, 'b')
plt.title("График плотности нормального распределения")

plt.show()

alpha = 0.03 # Уровень значимости
intervals = [
-10000,
0.8888, 2.3333, 3.7777, 5.2222, 6.6666, 8.1111,
10000
]

xvalues = [x for x in intervals[1:]]

right_theor_freq = ss.stats.norm.cdf(x=xvalues, loc=mu, scale=std)

xvalues = [x for x in intervals[:-1]]

left_theor_freq = ss.stats.norm.cdf(x=xvalues, loc=mu, scale=std)

npi = (right_theor_freq - left_theor_freq) * df.x_1.count()
ni = [7, 11, 6, 30, 8, 16, 7]

pirson = []
for i in range(len(ni)):
    pirson.append((ni[i] - npi[i]) ** 2 / ni[i])

degrees_of_freedom = len(intervals) - 1 - 2 - 1

chi2 = np.sum(pirson)
chi2_crit = ss.stats.chi2.ppf(1-alpha, df=degrees_of_freedom)
p_value = ss.stats.chi2.sf(chi2, degrees_of_freedom)

print(f"chi2: {chi2}")
print(f"chi2_crit: {chi2_crit}")
print(f"p-value: {p_value}")

if chi2 < chi2_crit and p_value > alpha:
    print("Принимаем гипотезу H0")
else:
    print("Отвергаем гипотезу H0")

# --- ВАРИАЦИОННЫЙ РЯД ---
clean_data = df.p_9.dropna().values
var_row = pd.Series(clean_data).value_counts().sort_index()

# Формируем таблицу вариационного ряда
var_df = pd.DataFrame({
    'Варианта, xi': var_row.index,
    'Частота, ni': var_row.values
})

print("\nВариационный ряд:")
print(var_df.to_string(index=False))

# --- ГРУППИРОВАННЫЙ РЯД ---
intervals = [-2, -0.5555, 0.8888, 2.3333, 3.7777, 5.2222, 6.6666, 8.1111, 9.5555, 11]
grouped_freq, bin_edges = np.histogram(clean_data, bins=intervals)

mu = clean_data.mean()
std = clean_data.std()
n = len(clean_data)

# Формируем таблицу группированного ряда
grouped_df = pd.DataFrame({
    'Начало интервала': bin_edges[:-1],
    'Конец интервала': bin_edges[1:],
    'Группированная частота': grouped_freq,
})

print("\nГруппированный статистический ряд:")
print(grouped_df.to_string(index=False))
