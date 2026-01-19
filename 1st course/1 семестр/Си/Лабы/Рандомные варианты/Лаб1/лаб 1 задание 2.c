#include <stdio.h>
#include <locale.h>
#include <math.h>
#define Pi 3.14

int main(void)
{
    setlocale(LC_ALL,"rus");
    float x,y,F;
      printf ("Ввод x и y для выражения (3*pow(cos(x- (Pi/6)),2)) / (1/2+sin(pow(y,2)))\n ");
      scanf ("%f %f",&x, &y);
      if ( (1/2+sin(pow(y,2))) != 0 ) F=(3*pow(cos(x- (Pi/6)),2)) / (1/2+sin(pow(y,2)));
      printf ("Результат работы равен : %.2f\n",F );
      if ( (1/2+sin(pow(y,2))) == 0 )("ОШИБКА,ЗНАМЕНАТЕЛЬ РАВЕН НУЛЮ" );
     
     
     system("pause");
     
}
