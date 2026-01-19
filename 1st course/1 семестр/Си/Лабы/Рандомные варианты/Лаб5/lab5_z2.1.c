#include<stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>
#include<malloc.h>
int main()
{
	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL,"rus");
    int *matr;
    int N=4, M=5;
    int i,j,min,k,l;
   
    matr=(int*)malloc(N*M*sizeof(int));
    for(i=0; i<N; i++)
    {
        for(j=0; j<M; j++)
        {
            printf("matr[%d][%d]= ",i,j);
            scanf("%d",(matr+i*M+j));
        }
    }
    for(i=0; i<N; i++)
    {
        for(j=0; j<M; j++)
        {
            printf("%d ",*(matr+i*M 
        }
        printf("\n");
    }
     min = 999999;
     for(i=0; i<N; i++)
    {
        for(j=0; j<(M-1)-j; j++)
        {
           if (min>*(matr+i*M+j)){
           	min = *(matr+i*M+j);
           	k = i;
           	
           	l = j;
           	
           }
            
        }
    }
    printf ("Ёлемент с минимальным значением равен %d\n",min);
    printf ("Ёлемент находитс€ в строке с номером %d \n", k);
    printf ("Ёлемент находитс€ в столбце с номером %d \n", l);
    
free(matr);
}
