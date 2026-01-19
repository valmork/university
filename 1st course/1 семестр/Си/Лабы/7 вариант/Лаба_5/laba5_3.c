#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>
#include <malloc.h>

typedef struct date{
    int day;
    int month;
    int year;
};

typedef struct{
    int num;
    char name[50];
    char surname[50];
    char familiya[50];
    char address[50];
    long int phone;
    char gender[50];
    long int oklad;
    struct date date2;
}prod;


//-----КОД-----
int main(void){
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL,"rus");//--Подрубаем русский язык--

    prod *D;
    D = (prod*)malloc(50*sizeof(prod));
    int n;
    int i;
    int k;
    int L=0;
    int R=0;
    int prodavci = 0;

    enum Menu{Z1=1, Z2, Z3, Z4, Z5, Z6, Exit}select;//--Делаем меню--
    do{
        puts("\n-----Меню программы-----");
        puts("1 - Добавить информацию о новом продавце");
        puts("2 - Отображение информации о продавцах");
        puts("3 - Поиск информации о продавцах с фамилией Иванов");
        puts("4 - Поиск информации о продавцах с окладом 10 000 - 20 000 рублей");
        puts("5 - Определение количества продавцов женского пола, родившихся в 1990 году");
        puts("6 - Определение среднего возраста продавцов");
        puts("7 - Выход из программы");

        puts("Выберите нужный пункт программы: ");
        scanf("%d", &select);
        switch(select){

            case 1:
                printf("Введите количество продавцов\n");
                scanf("%d", &n);
                prodavci +=n;
                printf("Ввод данных\n");
                for(i=0; i<n; i++){
                    printf("\nДанные о %d продавце:\n\n", i+1);
                    //--Табельный номер--
                    printf("Введите табельный номер: ");
                    scanf(" %d", &((D+i)->num));
                    for(k=i-1; k>=0; k--){
                        if (((D+i)->num)==((D+k)->num)){
                            printf("Такой номер уже существует, попробуйте еще раз <3\n");
                            scanf(" %d", &((D+i)->num));
                        }
                    }
                    //--Все остальное--
                    printf("\nВведите фамилию: ");
                    scanf(" %s", &((D+i)->familiya));

                    printf("\nВведите имя: ");
                    scanf(" %s", &((D+i)->name));

                    printf("\nВведите отчество: ");
                    scanf(" %s", &((D+i)->surname));

                    printf("\nВведите адрес: ");
                    gets(((D+i)->address));
                    gets(((D+i)->address));

                    printf("\nВведите телефон: ");
                    scanf(" %d", &((D+i)->phone));

                    printf("\nВведите пол (м, ж, да и все тысячи гендеров, которые придумаете): ");
                    scanf(" %s", &((D+i)->gender));

                    printf("\nВведите оклад: ");
                    scanf(" %d", &((D+i)->oklad));

                    printf("\nВведите дату рождения в формате ДД.ММ.ГГГГ: ");
                    scanf(" %d.%d.%d", &((D+i)->date2.day), &((D+i)->date2.month), &((D+i)->date2.year));
                }
                break;

            case 2:
                printf("Отображение информации о продавцах\n\n");
                for(i=0; i<n; i++){
                    printf ("|------------------------------------|------------------------|\n");
                    printf ("|            Продавец                |           №%d           |\n", i+1);
                    printf ("|------------------------------------|------------------------|\n");
                    printf ("|Табельный номер                     |%24d|\n", ((D+i)->num));
                    printf ("|Фамилия                             |%24s|\n", ((D+i)->familiya));
                    printf ("|Имя                                 |%24d|\n", ((D+i)->name));
                    printf ("|Отчество                            |%24d|\n", ((D+i)->surname));
                    printf ("|Пол                                 |%24d|\n", ((D+i)->gender));
                    printf ("|Адрес                               |%24d|\n", ((D+i)->address));
                    printf ("|Телефонный номер                    |%24d|\n", ((D+i)->phone));
                    printf ("|------------------------------------|------------------------|\n");
                }
                break;

            case 3:
                printf("Поиск информации о продавцах с фамилией Иванов\n");
                for (i=0; i<n; i++){
                    if((((D+i)->familiya[0])=='И')&&(((D+i)->familiya[1])=='в')&&(((D+i)->familiya[2])=='а')&&(((D+i)->familiya[3])=='н')&&(((D+i)->familiya[4])=='о')&&(((D+i)->familiya[5])=='в')){
                        printf("Найден человек с фамилией Иванов: %s %s %s Адрес - %s Телефон - %d Дата рождения - %d.%d.%d\n", ((D+i)->familiya), ((D+i)->name), ((D+i)->surname), ((D+i)->address), ((D+i)->phone), ((D+i)->date2.day), ((D+i)->date2.month), ((D+i)->date2.year));

                    }
                }
                break;

            case 4:
                printf("Продавцы с окладом 10000-20000\n");
                for (i=0; i<n; i++){
                    if((((D+i)->oklad)>=10000)&&(((D+i)->oklad)<=20000)){
                        printf("Найден человек с нужным окладом! %s %s %s Адрес - %s Телефон - %d Дата рождения - %d.%d.%d\n", ((D+i)->familiya), ((D+i)->name), ((D+i)->surname), ((D+i)->address), ((D+i)->phone), ((D+i)->date2.day), ((D+i)->date2.month), ((D+i)->date2.year));
                    }
                }
                break;

            case 5:
                printf("Определение количества продавцов женского пола, родившихся в 1990 году\n");
                int count = 0;
                for (i=0; i<n; i++){
                    if((((D+i)->date2.year)==1990)&& (((D+i)->gender[0])=='ж')){
                        count++;
                    }
                }
                printf("Количство, удовлетворяющее характеристикам - %d\n", count);

            case 6:
                printf("Определение среднего возраста продавцов\n");
                int vozrast;
                for (i=0; i<n; i++){
                    vozrast = vozrast + (2021-((D+i)->date2.year));
                }
                printf("Средний возраст продавцов(примерно): %d\n", vozrast/prodavci);

            case 7:
                return 0;
                break;

            default:
                printf("Вы ввели неправельные данные. Возможно, вы где-то ошиблись, попробуйте снова <3\n");

        }

    }while(select != 7);
    system("pause");
}
