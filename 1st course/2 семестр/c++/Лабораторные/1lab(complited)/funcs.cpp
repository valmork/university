#include "funcs.h"
#include <iostream>
#include <string>
#include <fstream>
#include<iomanip>
#include<cstdio>
#include <Windows.h>

using namespace std;

//--Добавляем функции--

seller* add(seller* S, int& n){
    n++;
    seller* Sn = new seller[n];
    for(int i = 0; i < n - 1; i++){
        Sn[i] = S[i];
    }
    delete[]S;
    S = new seller[n];
    S = Sn;
    cin.clear();

    //Добавляем новый элемент--
    m1://Метка для повторного введения номера
    int a = 0;
    cout << "Введите код продавца: "; cin >> a;
    cin.clear();
    cin.ignore(9999, '\n');
    for (int i = 0; i < n - 1; i++){
        if (S[i].num == a){
            cout << endl;
            goto m1;
        }
    }
    S[n-1].num = a;
    cout << endl;
    cout << "Введите фамилию: "; getline(cin, S[n-1].familiya); cout << endl;
    cin.clear();
    cout << "Введите имя: "; getline(cin, S[n-1].name); cout << endl;
    cin.clear();
    cout << "Введите отчество: "; getline(cin, S[n-1].surname); cout << endl;
    cin.clear();
    cout << "Введите адрес: "; getline(cin, S[n-1].address); cout << endl;
    cin.clear();
    cout << "Введите телефон: "; getline(cin, S[n-1].phone); cout << endl;
    cin.clear();

    m2://Метка для повторного выбора пола
    cout << "Выберите пол: " << endl;
    cout << "1 - Мужчина \n2 - Женщина" << endl;
    cin >> a;
    cin.clear();
    cin.ignore(9999, '\n');
    if ((a < 1) || (a > 2)){
        cout << endl;
        goto m2;
    }
    else{
        S[n-1].gender = static_cast<selectgender>(a);
        cout << endl;
    }

    cout << "Введите день рождения: "; cin >> S[n-1].date.day; cout << endl;
    cin.clear();
    cin.ignore(9999, '\n');
    cout << "Введите месяц рождения: "; cin >> S[n-1].date.month; cout << endl;
    cin.clear();
    cin.ignore(9999, '\n');
    cout << "Введите год рождения: "; cin >>S[n-1].date.year; cout << endl;
    cin.clear();
    cin.ignore(9999, '\n');
    cout << "Введите оклад: "; cin >> S[n-1].salary; cout << endl;
    cin.clear();
    m3://Метка для повторного выбора наличия диплома
    cout << "Есть высшее образование?: ";
    cout << "\n0 - есть \n1 - нет" << endl;
    cin >> a;
    cin.clear();
    cin.ignore(9999, '\n');
    if ((a != 0) && (a != 1)){
        cout << endl;
        goto m3;
    }
    else{
        S[n-1].highed = a;
    }
    cout << endl;
    return S;
}

seller* del(seller* S, int& n, int numb){//1 перегруженная функция
    for (int i = 0; i < n; i++){
        if (S[i].num == numb){
            n--;
            seller* Sn = new seller[n];
            int j, k;
            for (j = 0; j < i; j++){
                Sn[j] = S[i];//Запись до удаленных элементов
            }
            for (k = j, j = i + 1; j < n+1; j++, k++){
                Sn[k] = S[j];//Запись после удаленного элемента
            }
            delete[]S;
            S = new seller[n];
            S = Sn;
            break;
        }
        else{
            cout << "Такого продавца не найдено." << endl;
        }
    }
    return S;
}

seller* del(seller* S, int& n, string fam, string nam){//2 перегруженная функция
    for (int i = 0; i < n; i++){
        if ((S[i].familiya == fam) && (S[i].name) == nam){
            n--;
            seller* Sn = new seller[n];
            int j, k;
            for (j = 0; j < i; j++){
                Sn[j] = S[i];//Запись до удаленных элементов
            }
            for (k = j, j = i + 1; j < n+1; j++, k++){
                Sn[k] = S[j];//Запись после удаленного элемента
            }
            delete[]S;
            S = Sn;
            break;
        }
        else{
            cout << "Такого продавца не найдено." << endl;
        }
    }
    return S;
}

seller* del(seller* S, int& n, int numb, string fam){//3 перегруженная функция
    for (int i = 0; i < n; i++){
        if ((S[i].num == numb) && (S[i].familiya == fam)){
            n--;
            seller* Sn = new seller[n];
            int j, k;
            for (i = 0; j < n; j++){
                Sn[j] = S[i];
            }
            for (k = j, j = i + 1; j < n+1; j++, k++){
                Sn[k] = S[j];
            }
            delete[]S;
            S = new seller[n];
            S = Sn;
            break;
        }
        else{
            cout << "Такого продавца не найдено." << endl;
        }
    }
    return S;
}

void show(seller* S, int n){//Выводим в таблице
    cout << "+--------------------------------------------------+" << endl;
    cout << "|" << setw(50) << "Сведения о продавцах"<< "|" << endl;
    cout << "+--------------------------------------------------+" << endl;
    for (int i = 0; i < n; i++){
        cout << endl << "Продавец номер " << i+1 << endl;
        //Первая строчка дефолта-------------------------------------------
        cout << "+--------------------------------------------------+" << endl;
        cout << "|" << setw(16) << "Номер" << "|" << setw (16) << "Фамилия";
        cout << "|" << setw(16) << "Имя" << "|" << endl;
        cout << "+--------------------------------------------------+" << endl;
        //Первая строчка вывода++++++++++++++++++++++++++++++++++++++++++++
        cout << "|" << setw(16) << S[i].num << "|" << setw(16) << S[i].familiya << "|";
        cout << setw(16) << S[i].name << "|" << endl;
        //Вторая строчка дефолта-------------------------------------------
        cout << "+--------------------------------------------------+" << endl;
        cout << "|" << setw(16) << "Отчество" << "|" << setw (16) << "Адрес";
        cout << "|" << setw(16) << "Телефон" << "|" << endl;
        cout << "+--------------------------------------------------+" << endl;
        //Вторая строчка вывода++++++++++++++++++++++++++++++++++++++++++++
        cout << "|" << setw(16) << S[i].surname << "|" << setw(16) << S[i].address << "|";
        cout << setw(16) << S[i].phone << "|" << endl;
        //Третья строчка дефолта-------------------------------------------
        cout << "+--------------------------------------------------+" << endl;
        cout << "|" << setw(16) << "Пол" << "|" << setw (16) << "Дата";
        cout << "|" << setw(16) << "Оклад" << "|" << endl;
        cout << "+--------------------------------------------------+" << endl;
        //Третья строчка вывода++++++++++++++++++++++++++++++++++++++++++++
        switch (S[i].gender){
        case man:
            cout << "|" << setw(16) << "Мужчина" << "|";
            break;
        case woman:
            cout << "|" << setw(16) << "Женщина" << "|";
            break;
        }
        cout << setw(8) << S[i].date.day << "." << S[i].date.month << ".";
        cout << S[i].date.year << "|";
        cout << setw(16) << S[i].salary << "|" << endl;
        //Четвертая строчка дефолта----------------------------------------
        cout << "+--------------------------------------------------+" << endl;
        cout << "|" << setw(50) << "Наличие высшего образования?" << "|" << endl;
        cout << "+--------------------------------------------------+" << endl;
        //Четвертая строчка вывода+++++++++++++++++++++++++++++++++++++++++
        if (S[i].highed == 0){
            cout << "|" << setw(50) << "Диплом есть" << "|" << endl;
            cout << "+--------------------------------------------------+" << endl;
        }
        else{
            cout << "|" << setw(50) << "Диплома нет" << "|" << endl;
            cout << "+--------------------------------------------------+" << endl;
        }
    }
}

void showone(seller* S, int i){
    cout << endl << endl << "Номер: " << S[i].num << endl;
    cout << "Фамилия: " << S[i].familiya << endl;
    cout << "Имя: " << S[i].name << endl;
    cout << "Отчество: " << S[i].surname << endl;
    cout << "Номер: " << S[i].num << endl;
    cout << "Адрес: " << S[i].address << endl;
    cout << "Телефон: " << S[i].phone << endl;
    cout << "Пол: ";
    switch (S[i].gender){
    case man:
        cout << "Мужчина" << endl;
        break;
    case woman:
        cout << "Женщина" << endl;
        break;
    }
    cout << "Дата рождения: " << S[i].date.day << "." << S[i].date.month << ".";
    cout << S[i].date.year << endl;
    cout << "Оклад: " << S[i].salary << endl;
    cout << "Наличие высшего образования: ";
    if (S[i].highed == 0){
        cout << "Диплом есть" << endl;
    }
    else{
        cout << "Диплома нет" << endl;
    }
}
//Поиск по указанному году рождению----------------------

void foundyear(seller* S, int n, int setyear, int& i){
    int x = 0;
    for (int j = 0; j < n; j++){
        if (S[j].date.year == setyear){
            i = j;
            showone(S, i);
            x++;
        }
    }
    if (x == 0){
            cout << "Такого продавца не существует. Возможно, вы ошиблись с годом <3\n";
        }
}
//Поиск продавцов женского пола с дипломом---------------
void womanhigh(seller* S, int n, int& i){
    int x = 0;
    for (int j = 0; j < n; j++){
        if ((S[j].gender == 2) && (S[j].highed == 0)){
            i = j;
            showone(S, i);
            x++;
        }
    }
    if (x == 0){
        cout << "Нет ни одной женщины с высшим образование в вашем магазине, задумайтесь.\n";

    }
}
//Сохранение в файл-------------------------------------

void saveinf(seller* S, int& n)
{

ofstream out("struct.txt", ios::binary | ios::out);
out.write((char*)S, sizeof (seller)*n);
out.close();

ofstream fin("n.txt");
fin << n;

fin.close();
}

//Загрузка из файла-------------------------------------

seller* loadinf(seller* S, int& n)
{
ifstream fin("n.txt");
fin >> n;
cout << n;
fin.close();
int i;
S = new seller[n];
ifstream ins("struct.txt", ios::binary | ios::in);
ins.read((char*)S, sizeof (seller)*n);
ins.close();
return S;
}



//--Закончили добавлять функции--
