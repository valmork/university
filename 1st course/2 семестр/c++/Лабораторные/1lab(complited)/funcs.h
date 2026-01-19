#ifndef FUNCS_H_INCLUDED
#define FUNCS_H_INCLUDED
#include <iostream>
#include <string>
using namespace std;

enum menu{             //Меню
    addinfo = 1,
    deleteinfo,
    showinfo,
    showyear,
    foundsmartwoman,
    saveinfo,
    loadinfo,
    stop,
};

enum selectgender{     //Перечисление с выбором пола
    man = 1,
    woman,
};

struct setdate{        //Структура даты
    int day;
    int month;
    int year;
};

struct seller{         //Структура продавца
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
};

enum delet{
    number = 1,
    famnam,
    numfam,
};
seller* add(seller* S, int& n);
seller* del(seller* S, int& n, int numb);
seller* del(seller* S, int& n, string fam, string nam);
seller* del(seller* S, int& n, int numb, string fam);
void show(seller* S, int n);
void showone(seller* S, int i);
void foundyear(seller* S, int n, int setyear, int& i);
void womanhigh(seller* S, int n, int& i);
void saveinf(seller* S, int& n);
seller* loadinf(seller* S, int& n);




#endif // FUNCS_H_INCLUDED
