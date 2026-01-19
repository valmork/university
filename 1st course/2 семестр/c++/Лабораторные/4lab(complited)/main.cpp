#include <fstream>
#include <iomanip>
#include <cstdio>
#include <string>
#include <iostream>
#include<Windows.h>

using namespace std;

class numb{
private:
    float c;
    int d;
public:
    numb(){
        c = 1; d = 15;
    }
    get_d(){return d;}
    get_c(){return c;}
};

class matr{
private:
    float n = 0;
    float mas[20][20];
public:
    get_n(){return n;}
    get_mas(){return mas[0][0];}

    matr(numb num){
        n = num.get_d();
        float c = num.get_c();
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                mas[i][j] = c;
            }
        }
    }

    matr(){
        n = 1;
        mas[0][0] = 1;
    }

    matr (float k){
        n = 2;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                mas[i][j] = k;
            }
        }
    }

    friend ostream& operator << (ostream &out, const matr &matri);
	friend istream& operator >> (istream &in, matr& matri);

    matr operator += (float p){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                mas[i][j] += p;
            }
        }
    }

    matr operator /= (float p){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                mas[i][j] /= p;
            }
        }
    }

    matr operator ++ (int){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                mas[i][j] += 0.1;
            }
        }
    }

    matr operator ++ (){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                mas[i][j] += 0.1;
            }
        }
    }

    operator float() const
	{
	    float umn=1;
	    for (int i=0;i<n;i++)
        {
            for (int j=0;j<n;j++)
            {
                umn*=mas[i][j];
            }
        }
        return umn;
	}
};

	istream& operator >>  (istream &in, matr& matri)
    {
        cout << "¬ведите размер массива: ";
        cin >> matri.n;
        for (int i=0;i<matri.n;i++)
        {
            for (int j=0;j<matri.n;j++)
            {
                cout << "¬ведите элемент a[" << i << "][" << j << "]: ";
                in >> matri.mas[i][j];
            }
        }
        return in;
    }

    ostream& operator << (ostream &out, const matr &matri)
    {
        for (int i=0;i<matri.n;i++)
        {
            for (int j=0;j<matri.n;j++)
            {
                out << matri.mas[i][j];
            }
            cout << endl;
        }
        return out;
    }

int main()
{

    system("chcp 1251");
    setlocale(LC_ALL, "Rus");
    float s;
    matr matri;
	cin >> matri;
    cout << matri;
    cout << endl;

    matri += 1;
    cout << matri;
    cout << endl;

    matri /= 2;
    cout << matri;
    cout << endl;

    matri++;
    cout << matri;
    cout << endl;

    ++matri;
    cout << matri;
    cout << endl;

    s = static_cast<float>(matri);
    cout << s << endl <<endl;

    matr matri1 = 10;//из обычного в пользов.
    cout << matri1;

    numb num;
    matr matri2 = num;
    cout << matri2 << endl;

    return 0;

}
