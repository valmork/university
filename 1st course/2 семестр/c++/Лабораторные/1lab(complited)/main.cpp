#include "funcs.h"
#include <iostream>
#include <string>
#include <fstream>
#include<iomanip>
#include<cstdio>
#include <Windows.h>

using namespace std;

int main()
{
    system("chcp 1251");
    setlocale(LC_ALL, "Rus");
    int menu, n = 0, a = 0, num = 0, i = 0, setyear, numb, delet;
    seller* S = new seller[n];
    seller** s = &S;
    bool stop = 0, stop1 = 1;
    string fam, nam;

    do{
        do{
            cout << endl << "----Меню----" << endl;
            cout << "1. Добавление информации о новом продавце." << endl;
            cout << "2. Удаление информации о продавце." << endl;
            cout << "3. Отображении продавцов в виде таблицы." << endl;
            cout << "4. Поиск продавца по году рождения." << endl;
            cout << "5. Поиск продавцов женского пола с дипломом." << endl;
            cout << "6. Сохранение информации в файл." << endl;
            cout << "7. Загрузка данных из файла." << endl;
            cout << "8. Выход из программы" << endl << endl;
            cout << "Выберите пункт меню: ";
            cin >> a; cout << endl;
            cin.clear();
            cin.ignore(9999, '\n');
            if ((a > 0) && (a <= 8)){
                stop1 = 1;
            }
        }while (stop1 == 0);

        menu = a;
        switch (menu){

        case  addinfo://Добавление нового продавца
            {
                *s = add(S, n);
            }
            break;

        case deleteinfo://Удаление инфы
            {
                m4:
                    cout << "Выберите способ удаления:" << endl;
                    cout << "1. По номеру" << endl;
                    cout << "2. По фамилии и имени" << endl;
                    cout << "3. По номеру и фамилии" << endl;
                    cin >> a;
                    cin.clear();
                    cin.ignore(9999, '\n');
                    if ((a > 0) && (a < 4)){
                        delet = a;
                        switch(delet){
                        case number:
                            m5:
                            cout << "Введите номер продавца: ";
                            cin >> numb; cout << endl;
                            cin.clear();
                            cin.ignore(9999, '\n');
                            if (numb > 0){
                                *s = del(S, n, numb);
                            }
                            else{
                                goto m5;
                            }
                            break;

                        case famnam:
                            cout << "Введите фамилию: ";
                            getline(cin, fam); cout << endl;
                            cout << "Введите имя: ";
                            getline(cin, nam); cout << endl;
                            *s = del(S, n, fam, nam);
                            break;

                        case numfam:
                            m6:
                            cout << "Введите номер продавца: ";
                            cin >> numb; cout << endl;
                            cin.clear();
                            cin.ignore(9999, '\n');
                            if (numb < 0){
                                goto m6;
                            }
                            cout << "Введите фамилию: ";
                            getline(cin, fam); cout << endl;
                            *s = del(S, n, numb, fam);
                            break;
                        }
                    }
            }
            break;

        case showinfo://Показать всех в таблице
            {
                show(S, n);
            }
            break;

        case showyear://Поиск по годам
            {
                i = 0; setyear = 0;
                cout << "Введите год рождения продавца: "; cin >> setyear;
                cin.clear(); cin.ignore(9999, '\n'); cout << endl;
                foundyear(S, n, setyear, i);
            }
            break;

        case foundsmartwoman:
            {
                womanhigh(S, n, i);
            }
            break;

        case saveinfo:
            {
                saveinf(S, n);
            }
            break;

        case loadinfo:
            {
                S = loadinf(S, n);
            }
            break;

        }


    }while(stop == 0);







    return 0;
}

