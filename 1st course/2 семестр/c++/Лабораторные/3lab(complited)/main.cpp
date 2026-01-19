#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

string num_alphabet = "0123456789";

int main()
{
    system("chcp 1251");
    setlocale(LC_ALL, "Rus");
    int block = 1, i = 0, j = 0, n = 0, len, len1, f = 0;
    string A, text, str1;
    do{
        cout << "\nМеню:" << endl << endl;
        cout << "Task1. Задать с клавиатуры текст. Посчитать количество цифр в тексте." << endl << endl;
        cout << "Task2. Задать с клавиатуры текст. Удалить все строчные буквы в тексте." << endl;
        cout << "   Вывести содержимое строкой переменной с отредактированным текстом на экран." << endl << endl;
        cout << "Task3. Задать с клавиатуры текст. Отредактировать текст по следующим правилам:" << endl;
        cout << "   в начале строки не должно быть знаков препинания; в конце строки должна стоять точка;" << endl;
        cout << "   после каждой точки в тексте должен стоять пробел, за которым следует заглавная буква." << endl;
        cout << "   Вывести содержимое строковой переменной с отредактированным текстом на экран." << endl << endl;
        cout << "Выберите пункт меню: ";
        getline(cin, A); cin.clear(); cout << endl;

        if (A == "Task1" || A == "task1"){//Первый кейс--------------------------------
            cout << "Введите строку: " << endl;
            getline(cin, text);
            len = text.length();
            len1 = num_alphabet.length();
            for(i = 0; i < len; i++){
                for (j = 0; j < len1; j++){
                    if (text[i] == num_alphabet[j]){
                        n++;
                    }
                }
            }
            cout << "Количество цифр в строке: " << n << endl;
            n = 0;
        }

        else if (A == "Task2" || A == "task2"){//Второй кейс--------------------------------
            cout << "Введите строку: " << endl;
            getline(cin, text);
            string str;
            len = text.length();
            str.clear();
            for(i = 0; i < len; i++){
                if (isupper(text[i])){ str += text[i];}
                else{continue;}
            }
            cout << "полученная строка: " << str << endl;
            str.clear();
            text.clear();
        }

        else if (A == "Task3" || A == "task3"){//Третий кейс----------------------------
            cout << "Введите строку: " << endl;
            getline(cin, text);
            len = text.length();

            for (j = 0; j < len; j++){
                if (isalnum(text[j])){f = 1;}
                if (f != 0) str1 += text[j];
            }
            text.clear();

            if (islower(str1[0])){
                str1[0] = toupper(str1[0]);
            }

            for (i = 0; i < str1.size(); i++){
                text += str1[i];
                if (str1[i+1] == '\0'){break;}
                if (str1[i] == '.'){
                    while (!isalpha(str1[i+1])){
                        i++;
                    }
                    text += ' ';
                    text += toupper(str1[i+1]);
                    i++;
                }
            }
            str1.clear();

            cout << text << endl;
        }

        else if (A == "Exit" || A == "exit"){
            block = 0;
            cout << "Выход из программы." << endl;
            cout << "Выход из программы.." << endl;
            cout << "Выход из программы..." << endl;
        }

        else{
            cout << "Bведены некорректные данные <3" << endl;
        }


    }while (block == 1);



    return 0;
}
