#include<stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>
struct pro {
  char code[50];
  char proizvoditel[50];
  char gorod[50];
  char adr[50]; 
  char number[50];
};
struct micro {
    int art;
  char name[50];
  struct  pro made;
  int razr; 
  int chast;
  char arx[50];
  int cena;
    };
enum Menu {Z1,Z2,Z3,Z4,Z5,Z6,Z7,Z8} M;
//------------------------------------------------------------------
//------------------------------------------------------------------
void add_micro(int *n, struct micro **q) //P=*q
                    {*n=*n+1;
                    *q=(struct micro*)realloc(*q,*n*sizeof(struct micro));
                    printf("№%d Микроконтроллер:\n",*n);
                    printf("Введите Артикул: ");
                    scanf("%d",&(*(*q+*n-1)).art);
                    printf("Введите название: ");
                    scanf(" %s",(*(*q+*n-1)).name);
                    printf("Введите Код: ");
                    scanf(" %s",(*(*q+*n-1)).made.code);
                    printf("Введите название фирмы-производителя: ");
                    scanf(" %s",&(*(*q+*n-1)).made.proizvoditel);
                    printf("Введите Город: ");
                    scanf(" %s",(*(*q+*n-1)).made.gorod);
                    printf("Введите адресс: ");
                    gets((*(*q+*n-1)).made.adr);
                    gets((*(*q+*n-1)).made.adr);
                    printf("Введите номер телефона: ");
                    gets((*(*q+*n-1)).made.number);
                    printf("Введите Разрядность: "); 
                    scanf(" %d",&(*(*q+*n-1)).razr);
                    printf("Введите Частоту: ");
                    scanf(" %d",&(*(*q+*n-1)).chast);
                    printf("Введите Тип Архитектуры: ");
                    scanf(" %s",(*(*q+*n-1)).arx);
                    printf("Введите Цену: ");
                    scanf(" %d",&(*(*q+*n-1)).cena);
                    
                    }
//------------------------------------------------------------------
struct micro* del_art(int art,int *n, struct micro *P){
int i,j;
for( i=0; i<*n; i++){if (P[i].art==art)
    {for( j=i; j<*n; j++){P[j]=P[j+1];
    }
    *n=*n-1;
    P = (struct micro*)realloc(P,*n*sizeof(struct micro));
    return P;
}
}
return P;}
//------------------------------------------------------------------
int prn_tab(int s,struct micro *P){
if(s==0) return 0;
else{prn_tab(s-1, P);
                printf ("|------------------------------------|------------------------|\n");
				printf ("|         Микроконтроллер            |            %d           |\n", s);
				printf ("|------------------------------------|------------------------|\n");
		        printf ("|Артикул Микроконтроллера            |%24d|\n", P[s-1].art );
		        printf ("|Название Микроконтроллера           |%24s|\n", P[s-1].name);
		        printf ("|Код Производителя Микроконтроллера  |%24s|\n", P[s-1].made.code );
		        printf ("|Фирма-производитель                 |%24s|\n", P[s-1].made.proizvoditel);
		        printf ("|Город                               |%24s|\n", P[s-1].made.gorod);
		        printf ("|Адрес                               |%24s|\n", P[s-1].made.adr );
		        printf ("|Телефон                             |%24s|\n", P[s-1].made.number);
		        printf ("|Разрядность                         |%24d|\n", P[s-1].razr);
		        printf ("|Тактовая частота                    |%24d|\n", P[s-1].chast);
		        printf ("|Архитектура                         |%24s|\n", P[s-1].arx);
		        printf ("|Цена                                |%24d|\n", P[s-1].cena);
		        printf ("|------------------------------------|------------------------|\n");
};
}
//------------------------------------------------------------------
int f_arx(char c[5],int s,struct micro *P){
if(s==0) return 0;
else{f_arx(c, s-1, P);
    if (strcmp(P[s-1].arx,c)==0)
     { 
	            printf ("|------------------------------------|------------------------|\n");
				printf ("|         Микроконтроллер            |            %d           |\n", s);
				printf ("|------------------------------------|------------------------|\n");
		        printf ("|Артикул Микроконтроллера            |%24d|\n", P[s-1].art );
		        printf ("|Название Микроконтроллера           |%24s|\n", P[s-1].name);
		        printf ("|Код Производителя Микроконтроллера  |%24s|\n", P[s-1].made.code );
		        printf ("|Фирма-производитель                 |%24s|\n", P[s-1].made.proizvoditel);
		        printf ("|Город                               |%24s|\n", P[s-1].made.gorod);
		        printf ("|Адрес                               |%24s|\n", P[s-1].made.adr );
		        printf ("|Телефон                             |%24s|\n", P[s-1].made.number);
		        printf ("|Разрядность                         |%24d|\n", P[s-1].razr);
		        printf ("|Тактовая частота                    |%24d|\n", P[s-1].chast);
		        printf ("|Архитектура                         |%24s|\n", P[s-1].arx);
		        printf ("|Цена                                |%24d|\n", P[s-1].cena);
		        printf ("|------------------------------------|------------------------|\n");
				}
};
}
//------------------------------------------------------------------
int f_wm(char c[1],int s,struct micro *P){
       int tmp=0;
       char p1=16;
       if(s==0) return tmp;
       else {
            if((P[s-1].razr==16)&&(!strncmp(P[s-1].made.proizvoditel,c,50)))
            {   tmp=f_wm(c,s-1,P)+1;
                printf("%d %d %s %d\n",s,tmp,P[s-1].made.proizvoditel,P[s-1].razr);
                return tmp;
            }
       else
       {
        tmp=f_wm(c,s-1,P);
        printf("%d %d %s \n",s,tmp,P[s-1].made.proizvoditel);
        return tmp;
       };
       }
         }
//------------------------------------------------------------------
long int filesize( FILE *fp )
  {
    long int save_pos, size_of_file;

    save_pos = ftell( fp );
    fseek( fp, 0L, SEEK_END );
    size_of_file = ftell( fp );
    fseek( fp, save_pos, SEEK_SET );
    return( size_of_file );
  }
//------------------------------------------------------------------
int main()
{ 	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL,"rus");
    int n=0,i,d,raz;
    char c[5], l[1], tmp[1], f[250];

    struct micro *P;
    struct micro **q=&P;

    FILE *file;
n=4;

    P = (struct micro*)malloc(n*sizeof(struct micro));

    (*P).art=123;
    strcpy((*P).name, "Demix");
    strcpy((*P).made.code, "asdd89");
    strcpy((*P).made.proizvoditel, "WR");
    strcpy((*P).made.gorod, "Dubai");
    strcpy((*P).made.adr, "Y polyana");
    strcpy((*P).made.number, "4849848484");
    (*P).razr=16;
    (*P).chast=1;
    strcpy((*P).arx, "AVR");
    (*P).cena=9999;
    
    (*(P+1)).art=999;
    strcpy((*(P+1)).name, "De");
    strcpy((*(P+1)).made.code, "asd98");
    strcpy((*(P+1)).made.proizvoditel, "WA");
    strcpy((*(P+1)).made.gorod, "NY");
    strcpy((*(P+1)).made.adr, "Y marta");
    strcpy((*(P+1)).made.number, "494484");
    (*(P+1)).razr=9;
    (*(P+1)).chast=6;
    strcpy((*(P+1)).arx, "Kiborg");
    (*(P+1)).cena=222;
    
    (*(P+2)).art=456;
    strcpy((*(P+2)).name, "cpu");
    strcpy((*(P+2)).made.code, "sadsds9");
    strcpy((*(P+2)).made.proizvoditel, "KL");
    strcpy((*(P+2)).made.gorod, "GE");
    strcpy((*(P+2)).made.adr, "Deadline");
    strcpy((*(P+2)).made.number, "889595945");
    (*(P+2)).razr=8;
    (*(P+2)).chast=5;
    strcpy((*(P+2)).arx, "NLO");
    (*(P+2)).cena=11111;
    
    (*(P+3)).art=789;
    strcpy((*(P+3)).name, "AMK");
    strcpy((*(P+3)).made.code, "84844ss");
    strcpy((*(P+3)).made.proizvoditel, "GG");
    strcpy((*(P+3)).made.gorod, "LA");
    strcpy((*(P+3)).made.adr, "Paris");
    strcpy((*(P+3)).made.number, "8484848");
    (*(P+3)).razr=80;
    (*(P+3)).chast=16;
    strcpy((*(P+3)).arx, "Micros");
    (*(P+3)).cena=8888;

  

    do {
        printf("\n");
        puts("---------------------------------------Меню-------------------------------------------");
        puts("1 - Добавление информации о новом Микроконтроллере в конец  ");
        puts("2 - Удаление информации о Микроконтроллере по артикулу ");
        puts("3 - Отображение информации о Микроконтроллерах");
        puts("4 - Поиск информации о Микроконтроллерах с указанной Архитектурой");
        puts("5 - Определение кол-ва 16-разрядных Микроконтроллеров указанной фирмы-производителя");
        puts("6 - Выход из программы");
        puts("7 - Сохранение");
        puts("8 - Загрузка");
        puts("--------------------------------------------------------------------------------------");
        printf("\nВыберие пункт из меню: ");
        scanf("%d",&M);
        printf("\n");
        switch(M-1) {

          case Z1:
            add_micro(&n,q);
            break;

          case Z2:
            printf("Введите Атикул: ");
            gets(tmp);
            scanf("%d",&d);
            del_art(d,&n,P);
            break;
          case Z3:
            prn_tab(n,P);
            break;
          case Z4:
            printf("Введите название Архитектуры: ");
            gets(c);
            gets(c);
            f_arx(c,n,P);
            break;
          case Z5:
            printf("Введите название Производителя ");
            gets(c);
            gets(c);
            printf("\nРезультат:= %d\n",f_wm(c,n,P));
            break;
          case Z6:
            exit(0);
            break;
           case Z7:
            gets(f);
            gets(f);
             file = fopen(f, "wb");
	        fwrite(&P[0], sizeof(struct micro), n, file);
         	P = (struct micro*)realloc(P,n*sizeof(struct micro));
        	fclose(file);
            break;

          case Z8:
          gets(f);
          gets(f);
            file = fopen(f, "rb");
            if( file != NULL ) {
            printf( "File size=%ld\n", filesize( file ) );
            }
           raz=filesize( file )/368;
            n=raz;
            P = (struct micro*)realloc(P,n*sizeof(struct micro));
         	fread(&P[0], sizeof(struct micro), n, file);
        	fclose(file);
        	printf("Количесвто  загруженных микроконтроллеров  %d\n", n);
            break;

   

          default:
        printf("error\n\n");
    }
}
while(1==1);

}
