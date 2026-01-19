#include <stdio.h>
#include <stdlib.h>
#include<locale.h>
#include<math.h>
#include<windows.h>//тоже для языка

struct date{
    int day;
    int month;
    int year;
};
struct prodavci{
    int num;
    char name[20];
    char surname[20];
    char familiya[20];
    char address[20];
    long int phone;
    char gender[2];
    long int oklad;
    struct date date2;
}prod[3];

int main()
{
    setlocale(LC_ALL, "Rus");
    system("chcp 1251");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    //-------Объявление переменных------


    int i, j, count=0;

    for(i=0; i<4; i++){
      prod[i].num=0;
    };

    //-------КОД-------
    enum Menu {Z1=1,Z2,Z3,Exit} select;
    char ivanov[7] = "Иванов";
    char pol[]="f";

    do{
        puts("\n\n-----МЕНЮ-----");
        puts("1. Показать информацию о всех продавцах");
        puts("2. Добавить продавца");
        puts("3. Вывести поисковую информацию");
        puts("4. Выход из программы");
        printf("\n\n-Выберите пункт меню: ");

        scanf(" %d", &select);
        getchar();
        switch(select){
        case 1:
                for (i=0; i<4; i++){
                    if (prod[i].num==0){
                        break;
                    }
                    printf("Табельный номер - %d\n", prod[i].num);
                    printf(" ----Фамилия-----------Имя----------Фамилия----\n");
                    printf("|               |              |               |\n");
                    printf("|%15s|%14s|%15s|\n", prod[i].familiya, prod[i].name, prod[i].surname);
                    printf("|               |              |               |\n");
                    printf(" -------Пол-----------Адрес---------Телефон----\n");
                    printf("|               |              |               |\n");
                    printf("|%15s|%14s|%15ld|\n", prod[i].gender, prod[i].address, prod[i].phone);
                    printf("|               |              |               |\n");
                    printf(" ----------------------------------------------\n");
                }
            break;



        case 2:
            for (i=0; i<4; i++){
                if (prod[i].num==0){
                    printf("Введите данные %d продавца\n", i+1);

                    printf("Введите табельный номер: ");
                    scanf("%d", &prod[i].num);
                    m1:
                    for (j=i-1; j>=0; j--){
                        if (prod[i].num==prod[j].num){
                            printf("Продавец с таким номером уже существует, введите другого: ");
                            scanf("%d", &prod[i].num);
                            goto m1;
                        }
                    }


                    printf("Введите фамилию: ");
                    getchar();
                    gets(prod[i].familiya);

                    printf("Введите имя: ");
                    gets(prod[i].name);

                    printf("Введите отчество: ");
                    gets(prod[i].surname);

                    printf("Введите адрес: ");
                    gets(prod[i].address);

                    printf("Введите телефон: ");
                    scanf("%li", &prod[i].phone);

                    printf("Введите пол(мужчина - 'm', женщина - 'f'): ");
                    getchar();
                    gets(prod[i].gender);

                    printf("Введите оклад: ");
                    scanf("%ld", &prod[i].oklad);


                    printf("Введите дату: ");
                    scanf("%d.%d.%d", &prod[i].date2.day, &prod[i].date2.month, &prod[i].date2.year);
                    break;
                }
                else{
                    continue;
                }
             break;
            };
            break;


        case 3:
            //-----Иванов-----
            puts("Выводим поисковую информацию о продавцах с фамилией Иванов");
            for (i=0; i<4; i++){
                if (strcmp(prod[i].familiya, ivanov)==0){
                    printf("Найден человек с фамилией Иванов: %s %s %s Адрес - %s Телефон - %d Дата рождения - %d.%d.%d\n",
                    prod[i].familiya, prod[i].name, prod[i].surname, prod[i].address, prod[i].phone, prod[i].date2.day
                    , prod[i].date2.month, prod[i].date2.year);
                    count++;

                }
            }
            if(count==0){
                    puts("!Не найдено ни одного Иванова!");
            }

            //------Оклад-----

            printf("\n\nВыводим информацию о работниках с окладом 10000-20000\n");
            count=0;
            for (i=0; i<4; i++){
                if((9999<prod[i].oklad) && (prod[i].oklad<20001)){
                    printf("Найден человек с нужным окладом: %s %s %s Табельный номер - %d Оклад - %d\n", prod[i].familiya, prod[i].name,
                    prod[i].surname, prod[i].num, prod[i].oklad);
                    count++;
                }
            }
            if (count==0){
                puts("!Не найдено ни одного человека с нужным окладом!\n");
            }

            //------Женщины 1990 года-----

            printf("\nВыводим информацию о работниках женского пола 1990 года рождения\n");
            count=0;
            for(i=0; i<4;i++){
                if((strcmp(prod[i].gender, pol)==0)&&(prod[i].date2.year==1990)){
                    count++;

                }
            }
            if (count==0){
                printf("!Не найдено ни одного работника, удовлетворяющего характеристикам!\n");
            }
            else{
                printf("Количество продавцов, удовлетворяющих характеристикам: %d\n", count);
            }

            //------Средний возраст продавцов-------

            int age=0;
            int prodcount=0;
            for (i=0; i<4; i++){
                if(prod[i].date2.year!=NULL){
                    age=age+(2021-prod[i].date2.year);
                    prodcount++;
                }
            }
            printf("\nСредний возраст продавцов - %d\n", age/prodcount);
            break;

        case 4:
            printf("Выход из программы...");
            return 0;
    }

    }while(select!=4);



}
