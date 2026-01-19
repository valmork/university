#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <locale.h>

// !!!!!!!!! mass[i]=*(mass+i)
int main()
{ 	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
	setlocale(LC_ALL,"rus");
        int n, ni, di, i, j, min, tmin, *mass;
        //char tmp[1];
        n=5;
        mass = (int*)malloc(n*sizeof(int));
        srand(time(NULL));
        for(i = 0; i < n; i++)
                //mass[i] = 100*(int)rand() / RAND_MAX;
                *(mass+i)= 100*(int)rand() / RAND_MAX;
*(mass+3)=123;

        enum Menu {Z1,Z2,Z3,Z4,Z5,Z6,Z7} M;
        do {
        printf("\n");
        puts("---------------------Меню--------------------\n");
        puts("1 - Добавление элемента в указанную позицию");
        puts("2 - Удаление первого элемента массива");
        puts("3 - Отображение значений элементов массива");
        puts("4 - Очистка массива");
        puts("5 - Поиск указанного пользователем элемента");
        puts("6 - Сортировка элементов массива по возрастанию");
        puts("7 - Выход");
        puts("---------------------Меню--------------------\n");
        printf("\nВведите значение: ");
        scanf("%d",&M);
        printf("\n");
        switch(M-1) {

        case Z1:
        printf("Выберите позицию ");
        //gets(tmp);
        scanf("%d%d",&ni,&di);
        if(ni>n+1){printf("error\n"); break;}
        n=n+1;
        mass=(int*)realloc(mass,n*sizeof(int));
        for(i = 0; i < n-ni; i++){*(mass+n-i-1)=*(mass+n-i-2);}
        *(mass+ni-1)=di;
        goto m1;
        break;

        case Z2:
        for(i = 0; i < n; i++){
        //printf("%d ",*(mass+n-i-1));
        *(mass+i)=*(mass+i+1);}
        n=n-1;
        mass=(int*)realloc(mass,n*sizeof(int));
        printf("Удалено:\n");
        goto m1;
        break;

 m1:    case Z3:
        /*for(i = 0; i < n; i++)
        printf("%d ",mass[i]);
        printf("\n");*/
        for(i = 0; i < n; i++)
        printf("%d ",*(mass+i));
        printf("\n");
        break;

        case Z4:
            n=0;
            mass=(int*)realloc(mass,n*sizeof(int));
            //break;
        //n=1;
       // mass=(int*)realloc(mass,n*sizeof(int));
      //  *mass=0;
        printf("Очищено:\n");
        goto m1;
        break;

        case Z5:
        printf("Поиск: ");
        //gets(tmp);
        scanf("%d",&di);
        for(i = 0; i < n; i++)
        {if(di==*(mass+i)){ni=i; break;}}
        if (i==n){printf("\nНе найдено\n");} else {printf("\nНомер %d\n",ni+1);}
        break;

        case Z6:
        for(i = 0; i < n; i++){
        min=*(mass+i);
        for(j = i+1; j < n; j++){
        if (min>*(mass+j)){tmin=min; min=*(mass+j); *(mass+j)=tmin;}
        *(mass+i)=min;
        }
        }
        printf("Отсортировано:\n");
        goto m1;
        break;

        case Z7:
        exit(0);
        break;

        default:
        printf("error\n\n");

}
        }
        while(1==1);
        free(mass);
}
