#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <windows.h>
int main()
{
	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL,"rus");
    int **matr;
    int i,j,n=4,m=5,min=9999999999,q1=0,q2=0;
    matr=(int**)malloc(n*sizeof(int*));
    for(i=0; i<n; i++) {
        *(matr+i)=(int*)malloc(m*sizeof(int));
        for(j=0; j<m; j++) {
            printf("matr[%d][%d]= ",i,j);
            scanf("%d",&(*(*(matr+i)+j)));

        }
    }

    for(i=0; i<n; i++) {
        for(j=0; j<m; j++) {
            printf("%d ",(*(*(matr+i)+j)));
        }
        printf("\n");
    }

     for(i=0; i<n; i++) {
        for(j=0; j<(m-1)-j; j++) {
            if((*(*(matr+i)+j))<min){
                min=*(*(matr+i)+j);
                q1=i;
                q2=j;
            }
        }
    }
    printf ("Элемент с минимальным значением равен %d\n",min);
    printf ("Элемент находится в строке с номером %d \n", q1);
    printf ("Элемент находится в столбце с номером %d \n", q2);
    for(i=0; i<n; i++){
      free(*(matr+i));
    }
    return 0;
}
