#include <stdio.h>
#include <stdlib.h>
#include<locale.h>
#include<math.h>

int main()
{
    setlocale(LC_ALL, "rus");
    system("chcp 1251");//Для нормального подключения русского языка
    char text[5];
    int count;




    do{
    puts("Введите одну из слудующих команд:");
    puts("Z1, Z2, Z3, Z4");
    scanf("%s", &text);

    if (strcmp(text, "Z1") == 0){
        int n, i;
        int a[50];
        int mul=1;
        getchar();
        puts("Введите количество символов в вашем массиве: ");
        scanf(" %d", &n);
        n = n+1;
        for (i=1; i<n; ++i){
            printf("Введите %d значение массива: ", i);
            scanf("%d", &a[i-1]);
            if (a[i-1]%2==0){
            mul = mul * a[i-1];
            }

        }
        printf("%d\n",mul);
        mul = 1;
    }

    else if (strcmp(text, "Z2") == 0){
        int x, y;
        int n, m;
        int i, j;
        int b[50][50];
        int max = -1000;
        puts("Введите количество строк матрицы: ");
        scanf("%d", &n);
        puts("Введите количество столбцов матрицы: ");
        scanf("%d", &m);
        for (i=0; i<n; i++){
            printf("Ввод %d строки матрицы\n", i+1);
            for (j=0; j<m; j++){
                printf("Введите %d значение: ", j+1);
                scanf(" %d", &b[i][j]);
            }
        }
        for (i=1; i<n; i=i+2){
            for (j=0; j<m; j++){
                if (abs(b[i][j]) >= b[i][j-1]){
                    max = abs(b[i][j]);
                    x = i;
                    y = j;
                }
            }
            printf("Максимальное по модулю значение в %d строке: %d\n", i+1, max);
            printf("Адрес элемента: [%d][%d]\n", x+1, y+1);
            max=-1000;
        }
    }

    else if (strcmp(text, "Z3")==0){
        count=0;
        int i;
        char c[50];
        puts("Введите строчку");
        getchar();
        gets(c);
        for (i=0; c[i]!='\0'; i++){
                if (isalpha(c[i])!=0){
                    if((c[i]!='a') && (c[i] != 'e') && (c[i] !=
                    'i') && (c[i] != 'o') && (c[i] != 'u') && (c[i] != 'y') &&
                    (c[i] != 'A') && (c[i] != 'E') && (c[i] !=
                    'I') && (c[i] != 'O') && (c[i] != 'U') && (c[i] != 'Y')){
                        count++;
                    }
                }
        }
        printf("Количество согласных - %d\n", count);
        count=0;
    }



    else if (strcmp(text, "Z4")==0){
        char d[50];
        int i;
        puts("Введите текст:");
        getchar();
        gets(&d);
        for(i=0; d[i]!='\0'; i++){
            if (d[i]=='-'){
                if (d[i+1]=='-'){
                    continue;
                }
                else if ((d[i-1]!=' ') || (d[i+1]!=' ')){
                    printf(" - ");
                    i++;
                }
            }
            printf("%c", d[i]);
        }
    }

    else if(strcmp(text, "Exit")==0||strcmp(text, "exit")==0){
        puts("Выход из программы");
        break;
    }

    else{
        puts("Введено некорректное значение, возможно, вы ошиблись в букве, промазали или еще что-то вам помешало, попробуйте снова <3\n");
    }


    }while(strcmp(text, "Exit") != 0);


    return 0;
}