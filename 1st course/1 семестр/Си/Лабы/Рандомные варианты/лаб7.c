#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<string.h>
#include<limits.h>
#include<stdlib.h>


enum Menu {Z1,Z2,Z3,Z4,Z5,Z6,Z7,Z8,Z9} M;

void obr(FILE *f, char s[255]){
    int i=1, j, ch;
    s[0]=' ';
    while((ch = getc(f)) != EOF)
    s[i++]=ch;
    s[i++]=' ';
    s[i] = '\0';

    for (i=0;i<strlen(s)-1;i++){if(s[i]=='\n')s[i]=' ';}

m1:   for (i=1;i<strlen(s)-2;i++){
      if(s[i]==' '&&s[i+1]==' '){
        //printf(" %d",i);
       for(j=i;j<strlen(s)-2;j++) s[j]=s[j+1];
       s[strlen(s)-2]=' ';
       s[strlen(s)-1]='\0';
       goto m1;
      }
    }
}
void obr2(FILE *f, char s[255]){
    int i=1, j, ch;
    while((ch = getc(f)) != EOF)
    s[i++]=ch;
    s[i] = '\0';

    for (i=0;i<strlen(s)-1;i++){if(s[i]=='\n')s[i]=' ';}

m1:   for (i=1;i<strlen(s)-2;i++){
      if(s[i]==' '&&s[i+1]==' '){
        //printf(" %d",i);
       for(j=i;j<strlen(s)-2;j++) s[j]=s[j+1];
       s[strlen(s)-2]=' ';
       s[strlen(s)-1]='\0';
       goto m1;
      }
    }
}

int main()
{     	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char s[255], s1[255], tm[255];
    char res[BUFSIZ]= {'\0'},*z,*r=res;
    char dig[]="0123456789";
    char def[]="-";
    char lit[]="aeiouAEIOU";
    int lines=0,sum,i,j,imin,jmin,min;
    int any;    //any типа int, потому что EOF имеет тип int!
    FILE *f, *f1;

    do {
        printf("\n");
        puts("------------------Меню---------------");
        puts("1 - Добавление текста");
        puts("2 - Сумма всех цифр в файле ");
        puts("3 - Кол-во гласных букв ");
        puts("4 - Слова с 6-ю буквами");
        puts("5 - Самое длиннсе слово");
        puts("6 - Дефис");
        puts("7 - Точка");
        puts("8 - Чтение файла");
        puts("9 - Выход");
        puts("-------------------------------------");
        printf("\nВыберите пункт: ");
        scanf("%d",&M);
        printf("\n");
        switch(M-1) {
 //-----------------------------------------------------------
        case Z1:
        
              printf("Введите строку: ");
              gets(s);
              gets(s);
              f = fopen("file.txt", "a");
              if (f == NULL) {
               return -1;
               }
               for( i=0;i < strlen(s);i++)
                 putc(s[i],f);
             fclose(f);
               break;
 //-----------------------------------------------------------
        case Z2:
            f = fopen("file.txt", "r");
            sum=0;
             if (f == NULL) {
              return -1;
               }
           do {
             any = fgetc(f);
               printf("%c", any);//debug
               for(i=0;i<10;i++){
                     if (any == dig[i])
                     sum=sum+i;
                    }
             } while(any != EOF);
            fclose(f);
             printf("\n\nСумма = %d\n",sum);
             break;
 //-----------------------------------------------------------
         case Z3:
            f = fopen("file.txt", "r");
            sum=0;
             if (f == NULL) {
                return -1;
                }
             do {
                any = fgetc(f);
                  printf("%c", any);//debug
                for(i=0;i<42;i++){
                      if (any == lit[i])
                        sum=sum+1;
                     }
                  } while(any != EOF);
                 fclose(f);
              printf("\n\nКол-во гласных: %d\n",sum);
                 break;
 //-----------------------------------------------------------
        case Z4:
                strcpy(s1,"");
               f1 = fopen("file1.txt", "w");
                f = fopen("file.txt", "r");
                if (f == NULL) {
        return -1;
               }obr(f,s);
                      for(i=0;i<strlen(s)-7;i++){
                          if(s[i]==' '&&s[i+1]!=' '&&s[i+2]!=' '&&s[i+3]!=' '&&s[i+4]!=' '&&s[i+5]!=' '&&s[i+6]!=' '&&s[i+7]==' '){
                           strncpy(tm,&s[i+1],6);
                                tm[6]=' ';
                               tm[7]='\0';
                             //printf("\n%s",tm);
                              strcat(s1,tm);
                           }
                          }
                     printf("\n%s",s);
                     printf("\n%s\n",s1);
                     fputs(s1,f1);
                     fclose(f);
                     fclose(f1);
                      break;
 //-----------------------------------------------------------
        case Z5:
                   f = fopen("file.txt", "r");
                   if (f == NULL) {
                       return -1;
                    }obr(f,s);

                  min=0;
                 imin=0;
                 jmin=0;

                 for (i=0;i<strlen(s);i++){
                     if (s[i]!=' ') jmin+=1;
                   else{
                         if (jmin > min) {
                             min = jmin;
                              imin = i - jmin;
                          }
                     jmin=0;
                        }
                   }
                    printf(s);
                if (jmin > min) {
                      min = jmin;
                       imin = i - jmin;
                 }
                 min += imin;
                 printf("\n");
                  for (i=imin; i<min; i++)
                     putchar(s[i]);
                 printf("\n");
                 //printf ("\n\nmin=%d",min);
                    //printf ("\nimin=%d",imin);
                //printf ("\njmin=%d\n\n",jmin);
                 //printf("\nshort: ");
                  //for (i=jmin+1;i<jmin;i++) printf("%c",s[i]);
                    //printf("\n");
                   fclose(f);
                      break;
 //-----------------------------------------------------------
        case Z6:
            f = fopen("file.txt", "r");
               if (f == NULL) {
                      return -1;
                    fclose(f);
                 }obr(f,s);
                 printf(s);
              f = fopen("file.txt", "w");
             for(z=s; *z; ++z) {
                  if(*z=='-') {
                           *r++=' ';
                         *r++=*z;
                          *r++=' ';
                          }
                 else
                     *r++=*z;
                   }
                fputs(res,f);
                fclose(f);
                 break;
 //-----------------------------------------------------------
         case Z7:
                f = fopen("file.txt", "r");
               if (f == NULL) {
                      return -1;
                    fclose(f);
                 }obr(f,s);
                 printf(s);
              f = fopen("file.txt", "w");
             for(z=s; *z; ++z) {
                  if(*z=='.') {
                         *r++=*z;
                          *r++=' ';
                          *r++='A';
                          
                           
                   
                          }
                 else {
                 	 
                     *r++=*z;
                    
                 }
                   }
                fputs(res,f);
                fclose(f);
                           break;
 //-----------------------------------------------------------
         case Z8:
          f = fopen("file.txt", "r");
              if (f == NULL) {
                 return -1;
                        }
                  obr(f,s);
                   printf(s);
                 fclose(f);
                printf("\n");
                   break;
 //-----------------------------------------------------------
                      case Z9:
                        exit(0);
                        break;
 //-----------------------------------------------------------
                     default:
                        printf("error\n\n");
    }
}
while(1==1);
}
