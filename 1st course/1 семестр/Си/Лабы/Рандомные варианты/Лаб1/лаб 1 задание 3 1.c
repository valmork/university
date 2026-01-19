#include <stdio.h>
#include <locale.h>
#include <math.h>
int main(void){
	setlocale(LC_ALL,"rus");
	char ch;
	int exit = 0 ;
    

    do {
    
    
	puts ("Программа для вычисления площади фигур");
	puts ("Выберите фигуру\n");
	puts ("*R*-Прямоугольный треугольник");
	puts ("*T*-Трапеция");
    puts ("*S*-Квадрат");
    puts ("*E*-Выход из программы");
    
    
    scanf (" %c",&ch);
    
    if (ch =='R'){
        float osn,vis;
    	float res1 ;
    	printf ("Введите основание и высоту треугольника\n");
        scanf(" %f %f",&osn,&vis );
    	if(osn<=0){
        puts("ОШИБКА,НЕВЕРНО ВВЕДЕНО ЗНАЧЕНИЕ\n");
    	}
    	if (vis<=0){
    	puts ("ОШИБКА,НЕВЕРНО ВВЕДЕНО ЗНАЧЕНИЕ\n");
    	} else {
    	
      	res1 = 0.5*osn*vis;
    	printf ("Площадь прямоугольного треугольника равна %.2f\n",res1);
    }
    }
    else if (ch =='T'){
    	float osn1, osn2,h;
    	float res2;
    	printf ("Введите основания трапеции\n");
    	scanf(" %f %f",&osn1,&osn2);
    	printf ("Введите высоту трапеции\n");
    	scanf(" %f",&h);
    	if(osn1<=0){
        puts("ОШИБКА,НЕВЕРНО ВВЕДЕНО ЗНАЧЕНИЕ\n");
    	}
    	if (osn2<=0){
    	puts ("ОШИБКА,НЕВЕРНО ВВЕДЕНО ЗНАЧЕНИЕ\n");
    	}
    	if(h<=0){
        puts("ОШИБКА,НЕВЕРНО ВВЕДЕНО ЗНАЧЕНИЕ\n");
        
    	} else {
    	

    	res2 = 0.5*(osn1+osn2)*h;
    	printf ("Площадь трапеции равна %.2f\n",res2);
    }
    	
    	
    }
    else 
	if (ch == 'S'){
    	float a ;
        float res3 ;
        printf ("Введите стороноу квадрата\n");
        scanf(" %f",&a);
        if(a<=0){
        puts("ОШИБКА,НЕВЕРНО ВВЕДЕНО ЗНАЧЕНИЕ\n");
    	} else {
    	
       res3 = a*a ;
       printf ("Площадь квадрата равна %.2f\n",res3);}
    	
    }
    else if ( ch == 'E'){
    	exit = 1;
    	return 0 ;
    }
    else 
    printf("ТАКОГО ПУНКТА НЕ СУЩЕСТВУЕТ!\nПопробуйте снова.\n");
}
    while (ch != 'E');

    
    
    
    
 
     
	

	

	
	
    
    
 
    
    

  system("pause");

}
