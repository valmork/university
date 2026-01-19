#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>
typedef struct
 {
  int code;
  char proizvoditel[50];
  char gorod[50];
  char adr[50]; 
  int number;
}pro;
typedef struct
 {
  int art;
  char name[50];
  pro made;
  int razr; 
  int chast;
  char arx[50];
  int cena;

} micro;
int main(void) {
	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
 micro D[50];
 int n;
int i; 
int k ;
int L=0;
int R=0;
setlocale(LC_ALL,"rus");
enum Menu {Z1,Z2,Z3,Z4,Z5,Z6,Exit} P;
char AVR[] = "AVR";
char Microchip[] = "Microchip";


do { 
puts ("\nМеню Программы");
puts ("0-Добавление информации о новом микроконтроллере"); 
puts ("1-Поиск информации о микроконтроллерах с архитектурой <<AVR>>");
puts ("2-Поиск информации о микроконтроллерах со стоимостью 800-1000р");
puts ("3-Отображение информации о микроконтроллерах");
puts ("4-Определение количества 16-разрядных микроконтроллеров фирмы-производства <<Microchip>>");
puts ("5-Определение количества микроконтроллеров, название которых начинается на <<Mega>>");
puts ("6-Для выхода\n\n");

puts ("Выберите пункт программы");
scanf (" %d",&P);
switch (P) {
	case 0 :
		printf ("Вводите количесвто Микроконтроллеров\n");
		scanf (" %d", &n);
		printf("Ввод данных\n");
		for(i=0;i<n;i++)
		{ 
			printf("Данные о №%d Микроконтроллере:\n\n",i+1);
			printf("Введите данные Микроконтроллера:\n");
		    printf ("Артикул Микроконтроллера\n");
		    scanf(" %d", &D[i].art);
		    
		     
		    
	        for (k=i-1;k>=0;k--){
	        
		      if (D[i].art==D[k].art){
		       printf ("Микроконтроллер с таким Артикулем уже существует.\nВведите другой артикул.\n");
		       scanf(" %d", &D[i].art);
		      }
		    }
		     for (k=i-1;k>=0;k--){
	        
		      if (D[i].art==D[k].art){
		       printf ("Микроконтроллер с таким Артикулем уже существует.\nВведите другой артикул.\n");
		       scanf(" %d", &D[i].art);
		      }
		    }
		     for (k=i-1;k>=0;k--){
	        
		      if (D[i].art==D[k].art){
		       printf ("Микроконтроллер с таким Артикулем уже существует.\nВведите другой артикул.\n");
		       scanf(" %d", &D[i].art);
		      }
		    }
		     for (k=i-1;k>=0;k--){
	        
		      if (D[i].art==D[k].art){
		       printf ("Микроконтроллер с таким Артикулем уже существует.\nВведите другой артикул.\n");
		       scanf(" %d", &D[i].art);
		      }
		    }
		     for (k=i-1;k>=0;k--){
	        
		      if (D[i].art==D[k].art){
		       printf ("Микроконтроллер с таким Артикулем уже существует.\nВведите другой артикул.\n");
		       scanf(" %d", &D[i].art);
		      }
		    }
		  
		 	printf("Название Микроконтроллера\n");
		 	scanf(" %s", &D[i].name);
		 	printf ("Код Производителя Микроконтроллера\n");
		 	scanf(" %d", &D[i].made.code);
			printf ("Фирма-производитель\n");
			scanf(" %s", &D[i].made.proizvoditel);
			printf ("Город\n");
			scanf (" %s", &D[i].made.gorod);
			printf("Адрес\n");
			gets(D[i].made.adr);
			gets(D[i].made.adr);
			printf("Телефон\n");
			scanf(" %d", &D[i].made.number);
			printf("Разрядность\n");
			scanf(" %d", &D[i].razr);
			printf("Тактовая частота\n");
			scanf(" %d", &D[i].chast);
			printf("Архитектура\n");
			scanf(" %s", &D[i].arx);
			printf("Цена\n");
			scanf(" %d", &D[i].cena);
		
		}
		break;
	
	case 1 :
	printf("Микроконтроллеры с архитектурой <<AVR>>\n");
		for( i=0;i<n;i++) {
			if (strcmp(D[i].arx,AVR) == 0) {
				printf ("Микрокоетроллер - №%d\n", i+1);
		        printf ("Артикул Микроконтроллера - %d\n", D[i].art );
		        printf ("Название Микроконтроллера  -  %s\n", D[i].name);
		        printf ("Код Производителя Микроконтроллера - %d\n", D[i].made.code );
		        printf ("Фирма-производитель - %s\n", D[i].made.proizvoditel);
		        printf ("Город - %s\n", D[i].made.gorod);
		        printf ("Адрес - %s\n", D[i].made.adr );
		        printf ("Телефон - %d\n", D[i].made.number);
		        printf ("Разрядность - %d\n",D[i].razr);
		        printf ("Тактовая частота - %d\n", D[i].chast);
		        printf ("Архитектура - %s\n", D[i].arx);
		        printf ("Цена - %d\n\n", D[i].cena);
			}
			
		}
       break;
    case 2 :
    	printf("микроконтроллеры со стоимостью 800-1000р\n");
    	for( i=0;i<n;i++) {
    		if((D[i].cena>=800) && (D[i].cena<=1000)){
    			printf ("Микрокоетроллер - №%d\n", i+1);
		        printf ("Артикул Микроконтроллера - %d\n", D[i].art );
		        printf ("Название Микроконтроллера  -  %s\n", D[i].name);
		        printf ("Код Производителя Микроконтроллера - %d\n", D[i].made.code );
		        printf ("Фирма-производитель - %s\n", D[i].made.proizvoditel);
		        printf ("Город - %s\n", D[i].made.gorod);
		        printf ("Адрес - %s\n", D[i].made.adr );
		        printf ("Телефон - %d\n", D[i].made.number);
		        printf ("Разрядность - %d\n",D[i].razr);
		        printf ("Тактовая частота - %d\n", D[i].chast);
		        printf ("Архитектура - %s\n", D[i].arx);
		        printf ("Цена - %d\n\n", D[i].cena);
    		}
    
    	}
    	break;
	
			
	case 3 :
		printf("Отображение информации о микроконтроллерах\n\n");
		for( i=0;i<n;i++){
				printf ("|------------------------------------|------------------------|\n");
				printf ("|         Микроконтроллер            |           №%d           |\n", i+1);
				printf ("|------------------------------------|------------------------|\n");
		        printf ("|Артикул Микроконтроллера            |%24d|\n", D[i].art );
		        printf ("|Название Микроконтроллера           |%24s|\n", D[i].name);
		        printf ("|Код Производителя Микроконтроллера  |%24d|\n", D[i].made.code );
		        printf ("|Фирма-производитель                 |%24s|\n", D[i].made.proizvoditel);
		        printf ("|Город                               |%24s|\n", D[i].made.gorod);
		        printf ("|Адрес                               |%24s|\n", D[i].made.adr );
		        printf ("|Телефон                             |%24d|\n", D[i].made.number);
		        printf ("|Разрядность                         |%24d|\n", D[i].razr);
		        printf ("|Тактовая частота                    |%24d|\n", D[i].chast);
		        printf ("|Архитектура                         |%24s|\n", D[i].arx);
		        printf ("|Цена                                |%24d|\n", D[i].cena);
		        printf ("|------------------------------------|------------------------|\n");
		        
		
		}
		break;
	
	case 4 :
		printf ("Определение количества 16-разрядных микроконтроллеров фирмы-производства <<Microchip>>\n");
		for( i=0;i<n;i++) {
			if ((strcmp(D[i].made.proizvoditel,Microchip) == 0) && (D[i].razr == 16)) {
				L=L+1;
				
			}
			
		}
		printf ("-----------------------------------------------------------------------------------\n");
		printf ("                                      LOADING                                      \n");
		printf ("-----------------------------------------------------------------------------------\n");
		printf ("Количетсво таких микроконтроллеров - %d\n", L); 
		printf ("-----------------------------------------------------------------------------------\n");
		break;
		
	case 5 : 
	 printf("Определение количества микроконтроллеров, название которых начинается на <<Mega>>\n");
	for( i=0;i<n;i++) {
			if ((D[i].name[0] == 'M') && (D[i].name[1] == 'e') && (D[i].name[2] == 'g' && (D[i].name[3] == 'a'))) {
		      R = R+1;
				
		     }
	}
		printf ("-----------------------------------------------------------------------------------\n");
		printf ("                                      LOADING                                      \n");
		printf ("-----------------------------------------------------------------------------------\n");
		printf ("Количетсво таких микроконтроллеров - %d\n", R); 
		printf ("-----------------------------------------------------------------------------------\n");
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



