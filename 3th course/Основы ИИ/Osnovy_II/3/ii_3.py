import pandas as pd
import numpy as np

from sklearn.model_selection import train_test_split
from sklearn.model_selection import cross_val_score

from sklearn.preprocessing import LabelEncoder
from sklearn.impute import SimpleImputer

from sklearn.ensemble import RandomForestClassifier
from sklearn.ensemble import GradientBoostingClassifier

from sklearn.metrics import accuracy_score
from sklearn.metrics import confusion_matrix
from sklearn.metrics import classification_report

from sklearn.metrics import roc_curve
from sklearn.metrics import roc_auc_score

import matplotlib.pyplot as plt

df = pd.read_csv('train.csv')

print("Первые строки датасета:")
print(df.head())

print("\nИнформация о датасете:")
print(df.info())

print("\nКоличество пропусков:")
print(df.isnull().sum())

# Удаляем ненужные столбцы при наличии
columns_to_drop = ['Name', 'Ticket', 'Cabin']

for col in columns_to_drop:
    if col in df.columns:
        df.drop(col, axis=1, inplace=True)


# Числовые признаки
numeric_columns = df.select_dtypes(include=['int64', 'float64']).columns

# Категориальные признаки
categorical_columns = df.select_dtypes(include=['object']).columns

# Заполнение числовых признаков средним
num_imputer = SimpleImputer(strategy='mean')

if len(numeric_columns) > 0:
    df[numeric_columns] = num_imputer.fit_transform(df[numeric_columns])

# Заполнение категориальных признаков самым частым значением
cat_imputer = SimpleImputer(strategy='most_frequent')

if len(categorical_columns) > 0:
    df[categorical_columns] = cat_imputer.fit_transform(df[categorical_columns])

encoder = LabelEncoder()

for column in categorical_columns:
    df[column] = encoder.fit_transform(df[column])

print("\nДанные после обработки:")
print(df.head())

# ============================================
# 5. Выделение признаков и целевой переменной
# ============================================

# Для Titanic целевая переменная — Survived

X = df.drop('Survived', axis=1)
y = df['Survived']

# ============================================
# 6. Разделение выборки
# ============================================

X_train, X_test, y_train, y_test = train_test_split(
    X,
    y,
    test_size=0.2,
    random_state=42,
    stratify=y
)

# ============================================
# 7. Исследование Random Forest
# ============================================

print("\n====================================")
print("RANDOM FOREST")
print("====================================")

n_trees_values = [5, 10, 20, 50, 100, 150, 200]

scores = []

for n in n_trees_values:

    rf_model = RandomForestClassifier(
        n_estimators=n,
        random_state=42
    )

    cv_score = cross_val_score(
        rf_model,
        X_train,
        y_train,
        cv=5,
        scoring='accuracy'
    ).mean()

    scores.append(cv_score)

    print(f"Количество деревьев: {n}")
    print(f"Средняя точность CV: {cv_score:.4f}")
    print()

# ============================================
# 8. Лучшее количество деревьев
# ============================================

best_score = max(scores)
best_n = n_trees_values[scores.index(best_score)]

print("Лучшее качество:")
print(best_score)

print("Лучшее количество деревьев:")
print(best_n)

# ============================================
# 9. Минимальное число деревьев > 60%
# ============================================

for n, score in zip(n_trees_values, scores):

    if score > 0.60:
        print("\nМинимальное число деревьев")
        print("при качестве выше 60%:")
        print(n)
        break

# ============================================
# 10. Обучение лучшей модели Random Forest
# ============================================

rf_model = RandomForestClassifier(
    n_estimators=best_n,
    random_state=42
)

rf_model.fit(X_train, y_train)

# ============================================
# 11. Оценка Random Forest
# ============================================

rf_predictions = rf_model.predict(X_test)

print("\n====================================")
print("РЕЗУЛЬТАТЫ RANDOM FOREST")
print("====================================")

print("Accuracy:")
print(accuracy_score(y_test, rf_predictions))

print("\nМатрица ошибок:")
print(confusion_matrix(y_test, rf_predictions))

print("\nОтчет классификации:")
print(classification_report(y_test, rf_predictions))

# ============================================
# 12. Градиентный бустинг
# ============================================

print("\n====================================")
print("GRADIENT BOOSTING")
print("====================================")

gb_model = GradientBoostingClassifier(
    n_estimators=100,
    learning_rate=0.1,
    random_state=42
)

gb_model.fit(X_train, y_train)

# ============================================
# 13. Оценка Gradient Boosting
# ============================================

gb_predictions = gb_model.predict(X_test)

print("\n====================================")
print("РЕЗУЛЬТАТЫ GRADIENT BOOSTING")
print("====================================")

print("Accuracy:")
print(accuracy_score(y_test, gb_predictions))

print("\nМатрица ошибок:")
print(confusion_matrix(y_test, gb_predictions))

print("\nОтчет классификации:")
print(classification_report(y_test, gb_predictions))

# ============================================
# 14. ROC-кривая Random Forest
# ============================================

rf_probs = rf_model.predict_proba(X_test)[:, 1]

rf_fpr, rf_tpr, _ = roc_curve(y_test, rf_probs)

rf_auc = roc_auc_score(y_test, rf_probs)

# ============================================
# 15. ROC-кривая Gradient Boosting
# ============================================

gb_probs = gb_model.predict_proba(X_test)[:, 1]

gb_fpr, gb_tpr, _ = roc_curve(y_test, gb_probs)

gb_auc = roc_auc_score(y_test, gb_probs)

# ============================================
# 16. Построение ROC-кривых
# ============================================

plt.figure(figsize=(8, 6))

plt.plot(
    rf_fpr,
    rf_tpr,
    label=f'Random Forest AUC = {rf_auc:.3f}'
)

plt.plot(
    gb_fpr,
    gb_tpr,
    label=f'Gradient Boosting AUC = {gb_auc:.3f}'
)

plt.plot([0, 1], [0, 1], linestyle='--')

plt.xlabel('False Positive Rate')
plt.ylabel('True Positive Rate')

plt.title('ROC-кривые моделей')

plt.legend()

plt.grid()

plt.show()

# ============================================
# 17. График зависимости качества
# от количества деревьев
# ============================================

plt.figure(figsize=(8, 6))

plt.plot(n_trees_values, scores, marker='o')

plt.xlabel('Количество деревьев')
plt.ylabel('Accuracy CV')

plt.title('Качество Random Forest')

plt.grid()

plt.show()

# ============================================
# 18. Итоговое сравнение
# ============================================

print("\n====================================")
print("СРАВНЕНИЕ МОДЕЛЕЙ")
print("====================================")

print(f"Random Forest AUC: {rf_auc:.4f}")
print(f"Gradient Boosting AUC: {gb_auc:.4f}")

if gb_auc > rf_auc:
    print("\nЛучше работает Gradient Boosting")
else:
    print("\nЛучше работает Random Forest")