import pandas as pd
import numpy as np
import scipy.stats as st
import statsmodels.api as sm
import statsmodels.formula.api as smf
import seaborn as sns
import matplotlib.pyplot as plt
from statsmodels.stats.outliers_influence import variance_inflation_factor

df = pd.read_excel("№2.xlsx")
alpha = 0.03

# Функция для скорректированного R²
def adjusted_r_squared(r_squared, n, k):
    return 1 - ((1 - r_squared) * (n - 1)) / (n - k - 1)

# ------------------------------------------
# 1. Исходный анализ данных и корреляции
# ------------------------------------------
print("="*50)
print("Исходный анализ данных".center(50))
print("="*50)

# Корреляционные матрицы
print("\nМатрица корреляций Пирсона:")
print(df.corr().round(3))

print("\nМатрица корреляций Спирмена:")
print(df.corr(method='spearman').round(3))

print("\nМатрица корреляций Кендалла:")
print(df.corr(method='kendall').round(3))

# Графики распределений
sns.pairplot(data=df, kind='reg', diag_kind='kde')
plt.suptitle("Парные распределения и регрессии", y=1.02)
plt.show()

# ------------------------------------------
# 2. Углубленный корреляционный анализ
# ------------------------------------------
print("\n" + "="*50)
print("Углубленный анализ связи y и x4".center(50))
print("="*50)

# Расчет корреляции Пирсона
r, p_value = st.pearsonr(df['y'], df['x4'])
print(f"\nКоэффициент корреляции Пирсона: r = {r:.3f}")

# Интерпретация силы связи
if abs(r) >= 0.7:
    strength = "сильная"
elif abs(r) >= 0.3:
    strength = "умеренная"
else:
    strength = "слабая"
direction = "прямая" if r > 0 else "обратная"
print(f"Тип связи: {direction}, теснота: {strength}")

# Проверка значимости
t_corr = r * np.sqrt((len(df)-2)/(1-r**2))
p_corr = 2 * (1 - st.t.cdf(abs(t_corr), len(df)-2))
print(f"\nt-критерий: {t_corr:.3f}, p-value: {p_corr:.5f}")
print("Корреляция значима" if p_corr < alpha else "Корреляция не значима")


# ------------------------------------------
# 3. Регрессионный анализ
# ------------------------------------------
print("\n" + "="*50)
print("Регрессионный анализ".center(50))
print("="*50)

# Парная регрессия y ~ x4
model_pair = smf.ols('y ~ x4', data=df).fit()
print("\nПарная регрессия y ~ x4:")
print(f"Уравнение: y = {model_pair.params['Intercept']:.2f} + {model_pair.params['x4']:.4f}·x4")
print(f"R² = {model_pair.rsquared:.3f}, Adj R² = {model_pair.rsquared_adj:.3f}")
print(f"F-статистика: {model_pair.fvalue:.1f}, p-value: {model_pair.f_pvalue:.5f}")

# График парной регрессии
plt.figure(figsize=(10, 6))
sns.regplot(x='x4', y='y', data=df, line_kws={'color': 'red'})
plt.title(f'Парная регрессия: y = {model_pair.params["Intercept"]:.1f} + {model_pair.params["x4"]:.3f}·x4')
plt.xlabel('x4')
plt.ylabel('y')
plt.grid(True)
plt.show()

# Множественная регрессия
print("\n" + "="*30)
print("Множественная регрессия".center(30))
print("="*30)

# Проверка мультиколлинеарности
vif_data = pd.DataFrame()
vif_data["Фактор"] = ['x1', 'x2', 'x3', 'x4']
vif_data["VIF"] = [variance_inflation_factor(df[['x1','x2','x3','x4']].values, i) for i in range(4)]
print("\nФакторы инфляции дисперсии (VIF):")
print(vif_data.round(2))

# Построение моделей
models = {
    "x1 + x2 + x3 + x4": smf.ols('y ~ x1 + x2 + x3 + x4', data=df).fit(),
    "x2 + x3 + x4": smf.ols('y ~ x2 + x3 + x4', data=df).fit(),
    "x1 + x3 + x4": smf.ols('y ~ x1 + x3 + x4', data=df).fit(),
    "x1 + x2 + x4": smf.ols('y ~ x1 + x2 + x4', data=df).fit(),
    "x1 + x2 + x3": smf.ols('y ~ x1 + x2 + x3', data=df).fit(),
    "x3 + x4": smf.ols('y ~ x3 + x4', data=df).fit(),
    "x1 + x4": smf.ols('y ~ x1 + x4', data=df).fit(),
    "x1 + x3": smf.ols('y ~ x1 + x3', data=df).fit(),
}

# Сравнение моделей
model_comp = []
for name, model in models.items():
    r2_adj = adjusted_r_squared(model.rsquared, len(df), len(model.params)-1)
    model_comp.append((name, model.rsquared, r2_adj, model.aic, model.f_pvalue))

model_comp_df = pd.DataFrame(model_comp, columns=["Модель", "R²", "R²_испр", "AIC", "F_p-value"])
print("\nСравнение моделей:")
print(model_comp_df.sort_values("R²_испр", ascending=False).round(3))

# Выбор лучшей модели
best_model = models["x1 + x3 + x4"]
print(f"\nВыбрана модель: {best_model.model.formula} (скорректированный R² = {best_model.rsquared_adj:.3f})")

# Диагностика модели
print("\nДиагностика лучшей модели:")
print(best_model.summary())

# Стандартизированные коэффициенты
data_std = (df - df.mean()) / df.std()
std_model = smf.ols('y ~ x4', data=data_std).fit()
print("\nСтандартизированный коэффициент при x4:")
print(std_model.params.round(3))

