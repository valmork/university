#include <iostream>
#include <string>
#include <fstream>
#include<iomanip>
#include<cstdio>
#include <Windows.h>

using namespace std;

struct setdate{
    int day = {01};
    int month = {01};
    int year = {2003};
};

enum selectgender{
    man = 1,
    woman,
};

enum menu{
    add = 1,
    del,
    show,
    search_year,
    found_smart_woman,
    change_shop_name,
    exit_prog,
};

enum how_del{
    numnum = 1,
    famnam,
    famnum,
};

class prod{//Объявление класса
private:
    int num;
    string familiya;
    string name;
    string surname;
    string address;
    string phone;
    selectgender gender;
    setdate date;
    float salary;
    bool highed;
    static string shop_name;

public:
    prod(){
        num = 0;
        familiya = "Ефанов";
        name = "Никита";
        surname = "Павлович";
        address = "ОГУшная общага";
        phone = "+79004873849";
        gender = static_cast<selectgender>(1);
        date.day = 10;
        date.month = 03;
        date.year = 2004;
        salary = 11000;
        highed = 1;
    }

    prod(int num_n, string fam_n, string nam_n, string sur_n, string addr_n,
         string phon_n, int gender_n, int day, int month, int year,
         float salary_n, bool highed_n){
        num = num_n;
        familiya = fam_n;
        name = nam_n;
        surname = sur_n;
        address = addr_n;
        phone = phon_n;
        gender = static_cast<selectgender>(gender_n);
        date.day = day;
        date.month = month;
        date.year = year;
        salary = salary_n;
        highed = highed_n;
    }

    return_num(){//Метод для возвращения номера
        return num;
    }

    return_year(){//Метод для возвращения года
        return date.year;
    }

    delet(int num_n){//Перегруженный метод для удаления по номеру
        if(num == num_n){
            return 1;
        }
    }

    delet(string fam_n, string nam_n){//Перегруженный метод для удаления по фамилии и имени
        if ((fam_n == familiya) && (nam_n == name)){
            return 1;
        }
    }

    delet(int num_n, string fam_n){//Перегруженный метод для удаления по фамилии и номеру
        if ((fam_n == familiya) && (num_n == num)){
            return 1;
        }
    }

    void show_prod(){
        if (num != 0){
            cout << "+--------------------------------------------------+" << endl;
        cout << "|" << setw(30) << "Сведения о продавцах магазина "<< shop_name << setw(17) << "|" << endl;
        //Первая строчка дефолта-------------------------------------------
        cout << "+--------------------------------------------------+" << endl;
        cout << "|" << setw(16) << "Номер" << "|" << setw (16) << "Фамилия";
        cout << "|" << setw(16) << "Имя" << "|" << endl;
        cout << "+--------------------------------------------------+" << endl;
        //Первая строчка вывода++++++++++++++++++++++++++++++++++++++++++++
        cout << "|" << setw(16) << num << "|" << setw(16) << familiya << "|";
        cout << setw(16) << name << "|" << endl;
        //Вторая строчка дефолта-------------------------------------------
        cout << "+--------------------------------------------------+" << endl;
        cout << "|" << setw(16) << "Отчество" << "|" << setw (16) << "Адрес";
        cout << "|" << setw(16) << "Телефон" << "|" << endl;
        cout << "+--------------------------------------------------+" << endl;
        //Вторая строчка вывода++++++++++++++++++++++++++++++++++++++++++++
        cout << "|" << setw(16) << surname << "|" << setw(16) << address << "|";
        cout << setw(16) << phone << "|" << endl;
        //Третья строчка дефолта-------------------------------------------
        cout << "+--------------------------------------------------+" << endl;
        cout << "|" << setw(16) << "Пол" << "|" << setw (16) << "Дата";
        cout << "|" << setw(16) << "Оклад" << "|" << endl;
        cout << "+--------------------------------------------------+" << endl;
        //Третья строчка вывода++++++++++++++++++++++++++++++++++++++++++++
        switch (gender){
        case man:
            cout << "|" << setw(16) << "Мужчина" << "|";
            break;
        case woman:
            cout << "|" << setw(16) << "Женщина" << "|";
            break;
        }
        cout << setw(8) << date.day << "." << date.month << ".";
        cout << date.year << "|";
        cout << setw(16) << salary << "|" << endl;
        //Четвертая строчка дефолта----------------------------------------
        cout << "+--------------------------------------------------+" << endl;
        cout << "|" << setw(50) << "Наличие высшего образования?" << "|" << endl;
        cout << "+--------------------------------------------------+" << endl;
        //Четвертая строчка вывода+++++++++++++++++++++++++++++++++++++++++
        if (highed == 0){
            cout << "|" << setw(50) << "Диплом есть" << "|" << endl;
            cout << "+--------------------------------------------------+" << endl;
        }
        else{
            cout << "|" << setw(50) << "Диплома нет" << "|" << endl;
            cout << "+--------------------------------------------------+" << endl;
        }
        }

    }

    void found_year(int year_n){//Поиск по году рождения-------------------
        if(date.year == year_n && num != 0){
            cout << num << endl << familiya << " , " << name << " , " << surname << endl;
            switch(gender){
            case man:
                cout << "муж." << endl;
                break;
            case woman:
                cout << "жен." << endl;
            }
            if (highed == 0){
                cout << "Диплом есть";
            }
            else{
                cout << "Диплома нет";
            }
        }
    }

    int return_gender(){//Функция возвращения пола---------------
        return gender;
    }

    int return_highed(){//Функция возвращения наличия диплома----
        return highed;
    }

    count_higher_woman(){//Функция поиска женщин с высшим образовавнием
        int n_n;
        if (gender == 2 && highed == 0 && num != 0){
            return 1;
        }
        else{
            return 0;
        }
    }

    static change_shop_name(){
        string shop_name_n;
        cout << "Новое название: ";
        cin.ignore(9999, '\n');
        getline(cin, shop_name_n);
        shop_name = shop_name_n;
        cin.clear();
    }
};
string prod::shop_name = "Шиша";

//--------------------------------------------------------

int main()
{
    system("chcp 1251");
    setlocale(LC_ALL, "Rus");

    prod prods[5];//Объявляем массив продавцов

    int n = 0, A = 0, gender_n = 0, menu, a, year_n, i, j;
    int num_n, day, month, year, n_n;
    string fam_n, nam_n, sur_n, addr_n, phon_n, shop_name_n;
    float salary_n;
    bool highed_n, block;

    for(i = 0; i < 5; i++){
        prods[i] = prod();
    }

    do{

            cout << "--------Ваш магазин--------" << endl;
            cout << "1. Добавление информации о новом продавце." << endl;
            cout << "2. Удаление информации о продавце." << endl;
            cout << "3. Отображении продавцов в виде таблицы." << endl;
            cout << "4. Поиск продавца по году рождения." << endl;
            cout << "5. Поиск продавцов женского пола с дипломом." << endl;
            cout << "6. Сменить название магазина." << endl;
            cout << "7. Выход из программы" << endl << endl;
            cout << "Выберите пункт меню: ";
            cin >> A; cout << endl;

            menu = A;
            switch(menu){
            case add:
                {
                    n++;
                    bool block = 0;
                    int A = 0;
                    for(i = 0; i < 5; i++){
                        if(prods[i].return_num() == 0){
                            break;
                        }
                    }
                    do{
                        cout << "Введите номер продавца: "; cin >> A;
                        cin.clear();
                        cin.ignore(9999, '\n');
                        if (A > 0){
                            num_n = A;
                            for (j = 0; j < 5; j++){
                                if (num_n == prods[j].return_num()){
                                    block = 1;
                                    break;
                                }
                                else{
                                    block = 0;
                                }
                            }
                        }
                        else{
                            block = 1;
                        }
                    }while(block == 1);
                    cout << "Введите Фамилию: ";
                    getline(cin, fam_n);
                    cin.clear(); cout << endl;
                    cout << "Введите имя: ";
                    getline(cin, nam_n);
                    cin.clear(); cout << endl;
                    cout << "Введите отчество: ";
                    getline(cin, sur_n);
                    cin.clear(); cout << endl;
                    cout << "Введите адрес: ";
                    getline(cin, addr_n);
                    cin.clear(); cout << endl;
                    cout << "Введите телефон: ";
                    getline(cin, phon_n);
                    cin.clear(); cout << endl;
                    do{
                        cout << "Выберите пол: " << endl << "1 - мужской\n2 - женский\n";
                        cin >> A;
                        cin.clear();
                        cin.ignore(9999, '\n');
                        if ((A > 0) && (A < 3)){
                            gender_n = A;
                            block = 0;
                        }
                        else{
                            block = 1;
                        }
                    }while (block == 1);
                    cout << endl;
                    block = 1;
                    cout << "Введите число:";  cin >> day; cout << endl;
                    cout << "Введите месяц:";  cin >> month; cout << endl;
                    cout << "Введите год:";  cin >> year; cout << endl;
                    cout << "Введите оклад: "; cin >> salary_n; cout << endl;
                    do{
                        cout << "Есть высшее образование?: \n0 - Есть\n1 - Нет" << endl;
                        cin >> A;
                        cin.clear(); cin.ignore(9999, '\n');
                        if (A == 0 || A == 1){
                            highed_n = A;
                            block = 0;
                        }
                    }while (block == 1);
                    cout << endl;
                    prods[i] = prod(num_n, fam_n, nam_n, sur_n, addr_n, phon_n,
                                    gender_n, day, month, year, salary_n, highed_n);
                    break;
                }

            case del:

                    block = 1;
                    A = 0;
                    cout << "Какой способ удаления?: \n1 - По номеру.\n2 - По фамилии и имени\n3 - По номеру и фамилии\n";
                    cin >> A; cin.clear(); cin.ignore(9999, '\n');
                    if (A > 0 && A < 4){
                        switch(A){
                        case numnum://Удаление по коду-----
                            cout << "Введите код продавца: ";
                            cin >> num_n;
                            for(i = 0; i < 5; i++){
                                if (prods[i].delet(num_n) == 1){
                                    prods[i] = prod();
                                    cout << "Успешно удалено." << endl;
                                    break;
                                }
                            }
                            break;
                        case famnam://Удаление по фамилии и имени--
                            cout << "Введите фамилию продавца: ";
                            getline(cin, fam_n); cin.clear(); cin.ignore(9999, '\n');
                            cout << endl;
                            cout << "Введите имя продавца: ";
                            getline(cin, nam_n); cin.clear(); cin.ignore(9999, '\n');
                            cout << endl;
                            for (i = 0; i < 5; i++){
                                if (prods[i].delet(fam_n, nam_n) == 1){
                                    prods[i] = prod();
                                    cout << "Успешно удалено." << endl;
                                    break;
                                }
                            }
                        case famnum:
                            cout << "Введите фамилию продавца: ";
                            getline(cin, fam_n); cin.clear(); cin.ignore(9999, '\n');
                            cout << endl;
                            cout << "Введите код продавца: ";
                            cin >> num_n;
                            cout << endl;
                            for (i = 0; i < 5; i++){
                                if (prods[i].delet(num_n, fam_n) == 1){
                                    prods[i] = prod();
                                    cout << "Успешно удалено." << endl;
                                    break;
                                }
                            }
                        }
                    }
                break;

            case show:
                {
                    for (i = 0; i < 5; i++){
                        prods[i].show_prod();
                    }
                }
            break;

            case search_year:
                cin.clear();
                cin.ignore(32767, '\n');
                cout << "Bведите год:";
                cin >> year_n;
                for (i = 0;i < 5; i++){
                    prods[i].found_year(year_n);
                }
			break;

			case found_smart_woman:
			    {
                int n_n = 0;
                for (i = 0; i < 5; i++){
                    if (prods[i].count_higher_woman() == 1){
                        n_n++;
                    }
                }
                cout << n_n << " женщин с высшим образованием" << endl;
                break;
			    }

            break;

            case change_shop_name:
                prod::change_shop_name();
            break;

            case exit_prog:
                cout << "Магазин закрыт." << endl;
            break;

            default:
                cout << "Некорректные данные." << endl;
                break;
            }


    }while (menu != 7);



    return 0;
}
