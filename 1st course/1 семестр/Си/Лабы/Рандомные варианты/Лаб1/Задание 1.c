#include <stdio.h>
#include <locale.h>
#include <math.h>
int main(void){
	setlocale(LC_ALL,"rus");
	int m,n ,q,w,e,r,t,y;
	printf ("Пример №1\n");
	printf ("Ввод m и n для выражения m+--n\n");
	scanf ( "%d %d", &m, &n );
	q = m+--n;
	printf ("Значение Выражаения : %d\n",q );
	
    printf ("Пример №2\n");
	printf ("Ввод m и n для выражения  -n - --m\n");
	scanf ( "%d %d", &m, &n );
	w =  -n - --m;
	printf ("Значение Выражаения : %d\n",w );
	
	printf ("Пример №3\n");
	printf ("Ввод m и n для выражения   5*n-- > m++\n");
	scanf ( "%d %d", &m, &n );
	e =   5*n-- > m++;
	printf ("Значение Выражаения : %d\n", e );
	
	printf ("Пример №4\n");
	printf ("Ввод m и n для выражения  ++m << n--\n ");
	scanf ( "%d %d", &m, &n );
	r =   ++m << n--;
	printf ("Значение Выражаения : %d\n", r );
	
	printf ("Пример №5\n");
	printf ("Ввод m и n для выражения  (m && n) || (m & n) || m\n ");
	scanf ( "%d %d", &m, &n );
	t = (m && n) || (m & n) || m;
	printf ("Значение Выражаения : %d\n", t );
	
	 printf ("Пример №6\n");
	printf ("Ввод m и n для выражения  m++ % ~n\n ");
	scanf ( "%d %d", &m, &n );
	y =  m++ % ~n;
	printf ("Значение Выражаения : %d\n", y );
	
	system ("pause");
		
}

