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
    int **a;
    int i,j,n=4,m=5,min=9999999999,q1=0,q2=0;
    a=(int**)malloc(n*sizeof(int*));
    for(i=0; i<n; i++) {
        *(a+i)=(int*)malloc(m*sizeof(int));
        for(j=0; j<m; j++) {
            printf("a[%d][%d]= ",i,j);
            scanf("%d",&(*(*(a+i)+j)));

        }
    }
  
    for(i=0; i<n; i++) {
        for(j=0; j<m; j++) {
            printf("%d ",(*(*(a+i)+j)));
        }
        printf("\n");
    }
    
     for(i=0; i<n; i++) {
        for(j=0; j<(m-1)-j; j++) {
            if((*(*(a+i)+j))<min){
                min=*(*(a+i)+j);
                q1=i;
                q2=j;
            }
        }
    }
    printf ("Ёлемент с минимальным значением равен %d\n",min);
    printf ("Ёлемент находитс€ в строке с номером %d \n", q1);
    printf ("Ёлемент находитс€ в столбце с номером %d \n", q2);
    for(i=0; i<n; i++){
      free(*(a+i));
    }
    return 0;
}
