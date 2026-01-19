#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <windows.h>
int main() {
	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
setlocale(LC_ALL,"rus");
char Z1[] = "Z1";
char Z2[] = "Z2";
char Z3[] = "Z3";
char Z4[] = "Z4";
char exit[] = "exit";
char meniu[6];
 

 
		

while (strcmp(meniu,exit)!=0) {
	
 puts ("Введите команду для выполнения задания");
 puts ("Z1 - Задание №1");
 puts ("Z2 - Задание №2");
 puts ("Z3 - Задание №3");
 puts ("Z4 - Задание №4");
 puts ("exit - Выход из программы\n");
 scanf (" %6s" , meniu , 6);
 
 

    if (strcmp(meniu,Z1) == 0)
			{   int tmp;
			    int j;
				int i;
				int n;
				int a[i];
				printf("Введите размер одномерного массива: ");			
				scanf(" %d", &n);		
				printf ("Ввод элментов массива:\n");	
				for (i = 0; i < n; i++)
				{ 
				    printf("a[%d]=", i);
				    scanf(" %d", &a[i]);					
				}
			    printf ("Вывод элементов массива:\n");
				for (i = 0; i < n; i++) {
					printf ("%d ", a[i]);
				} printf ("\n");
				printf ("Сортировка массива по возрастанию значений элементов:\n");
				for (i = 1; i < n; i++){
			
	           for (j = 1; j < n; j++){
			
					if (a[j] < a[j-1]) {
						tmp = a[j];
						a[j] = a[j-1];
						a[j-1] = tmp;
					}
				}
				}
			 for (i = 0; i < n; i++){
			  printf("%d ", a[i]);}
			  printf ("\n\n");
				
			}
      else	if (strcmp(meniu,Z2) == 0){
	    int T,R;
		int max;
		int i,j;
		int N=5;
		int M=5;
		int b[N][M];

		
		
	    printf ("Ввод элментов массива:\n");
		for (i = 0 ; i < N ; i++){
			printf ("Ввод строки № %d:\n", i);
			for (j = 0; j < M; j++){
				printf("b[%d][%d] = ", i, j);
				scanf(" %d", &b[i][j]);	
		      }
				
			}
		printf ("Вывод элементов массива:\n");
		for (i = 0; i < N ; i++){
			for (j = 0; j < M; j++){
				printf ("%d ", b[i][j]);
			}
			printf ("\n");
		}
		for (i=1;i<N;i=i+2){
			for (j=0;j<M;j++){
			if (b[i][j]>=b[i][j-1]){
				max = b[i][j];
				T=i;
				R=j;
			
			
			
			}
			
			}
			printf("Элемент с максимальным значением в №%d строке равен:%d\n",i,max);
			printf("Элемент находится в %d строке и в %d столбце\n",T,R);
			    
			
			
		}
	
		
		}
	else if (strcmp(meniu,Z3) == 0){
		int i;
		int k;
		char str1[] = "Введите строку:";
		char str2[50];
		
		puts (str1);
	    gets (str2);
	    gets (str2);
	    printf ("Вывод строки\n");
	    puts (str2);
	    printf ("\n");
	    
	    for ( i = 0; i < sizeof (str2); i++)
    {
        switch (str2[i]) // проводи анализ предложения
        {
        case 'А': case 'а': case 'О': case 'о': case 'И': case 'и': case 'Е': case 'е': case 'Ё': case 'ё':
        case 'Э': case 'э': case 'Ы': case 'ы': case 'У': case 'у': case 'Ю': case 'ю': case 'Я': case 'я':
        {   
            k++;
            break;
        }
        }
         while (str2[i] != ' ') // перескакивает на следующее слово
        {
            if (str2[i] == '.') break; // если в составе слова найдена точка, то осуществляется вывод результатов
            i += 1; 
        }
	
	
	    
    }
    printf ("Количесвто слов в тексте, начинающихся  с гласной буквы = %d\n", k);
        
        
        }
  else if (strcmp(meniu,Z4) == 0) {
  	char str1[256];
  	int i;
  	printf ("Введите текст\n");
  	gets(str1);
  	gets(str1);


	for ( i = 0; i <256; i++)
	{

		if (str1[i] == ' ' && str1[i + 1] == ',')
		{
			str1[i] = ',';
			if (str1[i] != '\0')
			{
				str1[i + 1] = str1[i + 2];

			}
		}

	}

	for ( i = 1; i < 256; i++)
	{
		if (str1[i - 1] == ',')
		{
			str1[i] = ' ';

		}
		
	}

    printf("Вывод отредактированного текста\n");
	puts(str1);
  	
  	
  }
  else if (strcmp(meniu,exit) == 0){
  	return 0 ;
  }
  else  {
  	printf("ОШИБКА!!\nТакой команды нет!\n\n\n");
  }
	

		
		
		
	
		
	
			
			
 


	
	
	

   
	

} 
	system("pause");
}
