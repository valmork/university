#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include<windows.h>//тоже для языка

//--Структуры-----------------------------------------

struct date{
        int day;
        int month;
        int year;
};

struct sellers{
    char fio[50];
    char adr[50];
    int number;
    int phone;
    char gender;
    struct date dat;
    int oklad;
}seller;

struct products{
    int code;
    char name[50];
    struct date dat2;
    char otdel[50];
    int price;
    char descr[50];
}product;

//--Объединение------------------------------------------

union all{
    struct sellers seller;
    struct products product;
};

//--Основная часть--------------------------------------------------------------------

int main(void)
{
    setlocale(LC_ALL,"rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);//Для нормального русского языка
    union all D[50];
    char V;
    int i;
    int count=0;
    int countS=0;
    int countP=0;
    int check[50];

//--Меню---------------------------------------------------

    enum Menu {Z1=1,Z2,Z3,Z4,Z5,Exit} select;
    do{
        puts("\n----Меню----");
        puts("1 - Добавление информации о новом продавце или товаре");
        puts("2 - Отображение информации о продавцах и товарах");
        puts("3 - Отображение информации о продавцах в виде таблицы");
        puts("4 - Определение количества товаров");
        puts("5 - Поиск информации о товарах со стоимостью 500 рублей");
        puts("6 - Выход из программы\n");

        printf("Выберите пункт программы: ");
        scanf("%d", &select);
        switch(select){

            case 1:
                puts("S - добавление информации о продавце");
                puts("P - добавление информации о товаре");
                scanf(" %c", &V);

                if(V=='P'){
                    printf("Ввод данных о товаре\n");

                    printf("Код товара: ");
                    scanf(" %d", &D[count].product.code);

                    printf("\nНазвание товара: ");
                    scanf(" %s", &D[count].product.name);

                    printf("\nДата выпуска в формате ДД.ММ.ГГГГ: ");
                    scanf(" %d.%d.%d", &D[count].product.dat2.day, &D[count].product.dat2.month, &D[count].product.dat2.year);

                    printf("\nНазвание отдела: ");
                    scanf(" %s", &D[count].product.otdel);

                    printf("\nСтоимость: ");
                    scanf(" %d", &D[count].product.price);

                    printf("\nОписание: ");
                    scanf(" %s", &D[count].product.descr);

                    check[count]=1;
                    countP++;
                    count++;
                }

                else if(V=='S'){
                    printf("Ввод данных о новом продавце\n");

                    printf("Табельный номер продавца: ");
                    scanf(" %d", &D[count].seller.number);

                    printf("\nФИО продавца: ");
                    gets(D[count].seller.fio);
                    gets(D[count].seller.fio);

                    printf ("\nАдрес продавца: ");
                    scanf(" %s", &D[count].seller.adr);

                    printf("\nТелефонный номер продавца: ");
                    scanf(" %d", &D[count].seller.phone);

                    printf("\nПол продавца: ");
                    scanf(" %c", &D[count].seller.gender);

                    printf("\nДата рождения в формате ДД.ММ.ГГГГ: ");
                    scanf(" %d.%d.%d", &D[count].seller.dat.day, &D[count].seller.dat.month, &D[count].seller.dat.year);

                    printf("\nОклад: ");
                    scanf(" %dn", &D[count].seller.oklad);

                    check[count]=2;
                    countS++;
                    count++;
                }

                else{
                    printf("Введено неверное значение, попробуйте снова <3\n");
                    break;
                }
                break;

//--Отображение информации-------------------------------------------------------
            case 2:
                printf("Отображение информации о продавцах и товарах\n\n");

                for(i=0; i<count; i++){
                    if(check[i]==1){
                        printf ("|------------------------------------|------------------------|\n");
                        printf ("|              Товар                 |                        |\n");
                        printf ("|------------------------------------|------------------------|\n");
                        printf ("|Код                                 |%24d|\n", D[i].product.code);
                        printf ("|Название                            |%24s|\n", D[i].product.name);
                        printf ("|Дата выпуска                        |%16d.%d.%14d|\n", D[i].product.dat2.day, D[i].product.dat2.month, D[i].product.dat2.year);
                        printf ("|Название отдела                     |%24s|\n", D[i].product.otdel);
                        printf ("|Стоимость                           |%24d|\n", D[i].product.price);
                        printf ("|Описание                            |%24s|\n", D[i].product.descr);
                        printf ("|------------------------------------|------------------------|\n");
                    }
                }

                for(i=0; i<count; i++){
                    if(check[i]==2){
                        printf ("|------------------------------------|------------------------|\n");
                        printf ("|              Продавец              |                        |\n");
                        printf ("|------------------------------------|------------------------|\n");
                        printf ("|Табельный номер                     |%24d|\n", D[i].seller.number);
                        printf ("|ФИО                                 |%24s|\n", D[i].seller.fio);
                        printf ("|Адрес                               |%24s|\n", D[i].seller.adr);
                        printf ("|Телефон                             |%24d|\n", D[i].seller.phone);
                        printf ("|Дата рождения                       |%16d.%d.%d|\n", D[i].seller.dat.day, D[i].seller.dat.month, D[i].seller.dat.year);
                        printf ("|Оклад                               |%24d|\n", D[i].seller.oklad);
                    }
                }
                break;

            case 3:
                printf ("Отображение информации о продавцах в виде таблицы\n\n");
                i=0;
                for(i=0; i<count; i++){
                    if(check[i]==2){
                        printf ("|-----|-------------------------|-------------|-------------|---------------|--------|\n");
                        printf ("|Номер|           ФИО           |    Адрес    |   Телефон   | Дата рождения | Оклад  |\n");
                        printf ("|-----|-------------------------|-------------|-------------|---------------|--------|\n");
                        for (int j=0; j<countS; ++j){
                            printf ("|%5d|%25s|%13s|%13d|%7d.%d.%d|%8d|\n", D[j].seller.number, D[j].seller.fio, D[j].seller.adr, D[j].seller.phone, D[j].seller.dat.day, D[j].seller.dat.month, D[j].seller.dat.year, D[j].seller.oklad);
                        }
                        break;
                    }
                }
                break;

            case 4:
                printf ("Количество товаров равно %d", countP);
                break;

            case 5:
                printf("Информация о товарах стоимостью 500 рублей\n\n");
                for (i=0; i<count; i++){
                    if ((D[i].seller.oklad==500)&&(check[i]==1)){
                        printf ("|------------------------------------|------------------------|\n");
                        printf ("|              Продавец              |                        |\n");
                        printf ("|------------------------------------|------------------------|\n");
                        printf ("|Табельный номер                     |%24d|\n", D[i].seller.number);
                        printf ("|ФИО                                 |%24s|\n", D[i].seller.fio);
                        printf ("|Адрес                               |%24s|\n", D[i].seller.adr);
                        printf ("|Телефон                             |%24d|\n", D[i].seller.phone);
                        printf ("|Дата рождения                       |%19d.%d.%d|\n", D[i].seller.dat.day, D[i].seller.dat.month, D[i].seller.dat.year);
                        printf ("|Оклад                               |%24d|\n", D[i].seller.oklad);
                    }
                }
                break;

            case 6:
                return 0;
                break;
                default:
                    printf("Такого пункта в меню не существует, попробуйте еще раз <3\n");
                    break;
        }





    }while(select != 6);




}
