#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>
 struct sellers
 {
  int tabnum;
  char fio[50];
  char adr[50];
  int number;
  int oklad;
}seller;
 struct micros
 {
  int art;
  char name[50];
  char proizv[50];
  int razr; 
  int chast;
  char arx[50];
  int cena;
} micro;
union all
{
struct  sellers seller ;
struct  micros micro;
};
int main(void) {
	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
union all D[50];
char V;
int i;
int count=0;
int countM=0;
int countS=0;
int check[50];
 
setlocale(LC_ALL,"rus");
enum Menu {Z1=1,Z2,Z3,Z4,Z5,Exit} P;
do { 
puts ("\nМеню Программы");
puts ("1-Добавление информации о новом микроконтроллере или продавце в массив"); 
puts ("2-Отображение информации о микроконтроллерах и продавцах");
puts ("3-Отображение информации о микроконтроллерах в виде таблицы");
puts ("4-Определение количества Продавцов");
puts ("5-Поиск информации о продавцах с окладом менее 20000 рублей");
puts ("6-Для выхода\n\n");

puts ("Выберите пункт программы");
scanf (" %d",&P);
switch (P) {
	case 1 :
		puts ("\nМеню Выбора ввода");
        puts ("M-Добавление информации о новом микроконтроллере"); 
        puts ("S-Добавление информации о новом продавце");
		scanf (" %c",&V);
		if(V=='M'){
		  printf("Ввод данных о новом микроконтроллере\n");
		    printf ("Артикул Микроконтроллера\n");
		    scanf(" %d", &D[count].micro.art);
		 	printf("Название Микроконтроллера\n");
		 	scanf(" %s", &D[count].micro.name);
			printf ("Фирма-производитель\n");
			scanf(" %s", &D[count].micro.proizv);
			printf("Разрядность\n");
			scanf(" %d", &D[count].micro.razr);
			printf("Тактовая частота\n");
			scanf(" %d", &D[count].micro.chast);
			printf("Архитектура\n");
			scanf(" %s", &D[count].micro.arx);
			printf("Цена\n");
			scanf(" %d", &D[count].micro.cena);
			check[count]=1;
			countM++;
		    count++;
	    }
		 else if (V=='S'){
	       printf("Ввод данных о новом продавце\n");
	    	printf("Табельный номер продавца\n");
		    scanf(" %d", &D[count].seller.tabnum);
		 	printf("Ф.И.О. продавца\n");
		 	gets(D[count].seller.fio);
		 	gets(D[count].seller.fio);
			printf ("Адрес продавца\n");
			gets(D[count].seller.adr);
			printf("Телефонный номер продавца\n");
			scanf(" %d", &D[count].seller.number);
			printf("Оклад продавца\n");
			scanf(" %d", &D[count].seller.oklad);
			check[count]=2;
			countS++;
			count++;
	     }
	     else 
	     printf("\nERROR...\nПопробуйте снова!\n\n");
		break;
	case 2 :
		printf ("Отображение информации о микроконтроллерах и продавцах\n\n");
		for( i=0;i<count;i++){
			if(check[i]==1){
			
			    printf ("|------------------------------------|------------------------|\n");
				printf ("|         Микроконтроллер            |                        |\n");
				printf ("|------------------------------------|------------------------|\n");
		        	printf ("|Артикул Микроконтроллера            |%24d|\n", D[i].micro.art );
		        	printf ("|Название Микроконтроллера           |%24s|\n", D[i].micro.name);
		        	printf ("|Фирма-производитель                 |%24s|\n", D[i].micro.proizv);
		        	printf ("|Разрядность                         |%24d|\n", D[i].micro.razr);
		        	printf ("|Тактовая частота                    |%24d|\n", D[i].micro.chast);
		        	printf ("|Архитектура                         |%24s|\n", D[i].micro.arx);
		        	printf ("|Цена                                |%24d|\n", D[i].micro.cena);
		        	printf ("|------------------------------------|------------------------|\n");
	    }
		}
		for( i=0;i<count;i++){
			if (check[i]==2){
			
			    printf ("|------------------------------------|------------------------|\n");
				printf ("|          Продавец                  |                        |\n");
				printf ("|------------------------------------|------------------------|\n");
		        printf ("|Табельный номер                     |%24d|\n", D[i].seller.tabnum );
		        printf ("|Ф.И.О.                              |%24s|\n", D[i].seller.fio);
		        printf ("|Адрес                               |%24s|\n", D[i].seller.adr);
		        printf ("|Телефонный номер                    |%24d|\n", D[i].seller.number);
		        printf ("|Оклад                               |%24d|\n", D[i].seller.oklad);
		        printf ("|------------------------------------|------------------------|\n");
		    }
		}
	break;
	case 3 :
		printf ("Отображение информации о микроконтроллерах в виде таблицы\n\n");
			for( i=0;i<count;i++){
			if(check[i]==1){
			
			    printf ("|------------------------------------|------------------------|\n");
				printf ("|         Микроконтроллер            |                        |\n");
				printf ("|------------------------------------|------------------------|\n");
		        printf ("|Артикул Микроконтроллера            |%24d|\n", D[i].micro.art );
		        printf ("|Название Микроконтроллера           |%24s|\n", D[i].micro.name);
		        printf ("|Фирма-производитель                 |%24s|\n", D[i].micro.proizv);
		        printf ("|Разрядность                         |%24d|\n", D[i].micro.razr);
		        printf ("|Тактовая частота                    |%24d|\n", D[i].micro.chast);
		        printf ("|Архитектура                         |%24s|\n", D[i].micro.arx);
		        printf ("|Цена                                |%24d|\n", D[i].micro.cena);
		        printf ("|------------------------------------|------------------------|\n");
	    }
		}
		break;
	case 4 :
		printf ("Количество продавцов равно %d", countS );
		break;
	case 5 :
		printf("\t\t\t\tИнформация о продавцах с окладом менее 20000 рублей\n\n");
		for ( i = 0; i < count; i++)
					{
						if ((D[i].seller.oklad<20000) && (check[i] == 2 ))
						{
						 printf ("|------------------------------------|------------------------|\n");
			           	 printf ("|          Продавец                  |                        |\n");
				         printf ("|------------------------------------|------------------------|\n");
		                 printf ("|Табельный номер                     |%24d|\n", D[i].seller.tabnum );
		                 printf ("|Ф.И.О.                              |%24s|\n", D[i].seller.fio);
		                 printf ("|Адрес                               |%24s|\n", D[i].seller.adr);
		                 printf ("|Телефонный номер                    |%24d|\n", D[i].seller.number);
		                 printf ("|Оклад                               |%24d|\n", D[i].seller.oklad);
		                 printf ("|------------------------------------|------------------------|\n");
						}
					}
					break;
	case 6 :
		return 0 ;
		break;
		default :
			printf("ERROR!!!!\nТакого пунтка в меню не существует\n");
			break;
 	
}


 
} while ( P != 6);


system("pause");

}

