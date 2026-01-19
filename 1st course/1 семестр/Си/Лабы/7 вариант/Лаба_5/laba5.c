#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>



int main(){
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
	setlocale(LC_ALL,"rus");
    system("chcp 1251");
    unsigned int* mas;
    int n=0;
    mas = (int*)malloc(n*sizeof(int));
    enum Menu {Z1=1, Z2, Z3, Z4, Z5, Z6, Exit} select;

    while (select != exit){
          printf("\n---------Меню---------\n");
          puts("1 - Добавление элемента в указанную позицию");
          puts("2 - Удаление первого элемента массива");
          puts("3 - Отображение значений элементов массива");
          puts("4 - Очистка массива");
          puts("5 - Поиск указанного пользователем элемента");
          puts("6 - Сортировка элементов массива по возрастанию");
          puts("7 - Выход");
          scanf("%d", &select);

          switch(select){

              case Z1:
                   printf("Введите номер позиции: ");
                   int a, c, d=0;
                   scanf("%d", &a);
                   c=n;
                   if (n<a){//Если введенное значение больше массива, увеличим память
                      n=a;
                   }
                   mas=(int*)realloc(mas, n*sizeof(int));
                   if (c<a){
                      for (int i=с; i<n; i++){
                          *(mas+i) = d;
                      }
                   }
                   printf("\nВведите значение элемента массива: ");
                   scanf("%u", mas+(a-1));
                   break;

              case Z2:
                   for (int i=0; i<n; i++){
                       *(mas+i)=*(mas+i+1);
                       }
                   n--;
                   mas=(int*)realloc(mas,n*sizeof(int));

              case Z3:
                   printf("Отображение элементов массива\n");
                   for(int i=0; i<n; i++){
                       printf("%u ", *(mas+i));
                   }
                   printf("\n");
                   break;
              case Z4:
                   printf("\nОчистка массива\n");
                   free(mas);
                   mas = (int*)malloc(n*sizeof(int));
                   break;
              case Z5:
                   printf("\nВведите элемент для поиска\n");
                   int b;
                   scanf("%d", &b);
                   a = -1;
                   for (int i=0; i<n; i++){
                       if (*(mas+i)==b){
                          a=i;
                          break;
                       }
                   }
                   if (a==-1){
                      printf("\nНе найдено ни одного элемента\n");
                   }
                   else{
                        printf("Введенный элемент на %d позиции\n", a+1);
                   }
                   break;
              case Z6:
                   printf("\nСортировка элементов массива по возрастанию\n");
                   int j, min, t, tmin;
                   for(int i=0; i < n; i++){
                         min=*(mas+i);
                         for(j = i+1; j < n; j++){
                               if (min>*(mas+j)){
                                  tmin=min; min=*(mas+j);
                                  *(mas+j)=tmin;
                               }
                               *(mas+i)=min;
                         }
                   }
                   printf("Отсортировано\n");
              case Exit:
                free(mas);
                return 0;
              default:
                printf("\nВведены некорректные данные, попробуйте снова <3\n");
                break;
          }


    }



}
