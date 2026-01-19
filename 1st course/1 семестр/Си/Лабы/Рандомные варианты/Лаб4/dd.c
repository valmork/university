#define_CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<locale.h>
#include<cctype>

enummenu { Add = 1, View, Tabl, Quontity, Search, Exit };

structdate
{
	int digit;
	int month;
	int year;
}D1;

structpupils
{
	int kod;
	char lastname[20];
	char middlename[20];
	char name[20];
	char gender[6];
	structdate D1;
	char number[15];
	char location[50];
	char klass[2];
}pupil;

structteachers
{
	int tabel;
	char lastname[20];
	char middlename[20];
	char name[20];
	char lesson[15];
	int timework;
} teacher;

unionteachandpup
{
	structpupils pupil;
	structteachers teacher;
}tepu;

int main()
{
	constint SIZE = 100;
	unionteachandpup tepu[SIZE];

	int sel1;
	system("chcp 1251");
	int countT = 0;
	int countP = 0;
	int count = 0;
	int check[SIZE];
	int sel;
	while (true)
	{
		puts("\t\t\t\t\t\tМЕНЮ\n\n");
		puts("1. Добавить новую информацию о новом ученике или учителе");
		puts("2. Отображение информации об учителях и учениках");
		puts("3. Отображение информации об учениках в виде таблицы");
		puts("4. Определить количество учителей");
		puts("5. Вывести информацию об учителях со стажем работы от 25 до 30 лет");

		scanf("%d", &sel);
		switch (sel)
		{
				case Add:
				{
					int sel1;
					printf("Введитекогохотитеввести\n1.Ученик\n2.Учитель\n");
					for (int vixod = 0; vixod != -1; )
					{

						scanf("%d", &sel1);
						if (sel1 == 1)
						{

							printf("Введитекодученика: ");
							scanf("%d", &tepu[count].pupil.kod);


							char kod1 = tepu[count].pupil.kod;
							for (int j = 0; j < SIZE; j++)  //исправитьб
							{
								if (tepu[count].pupil.kod == tepu[j].pupil.kod && count != j)
								{
									printf("Данный код занят! Введите другой!\n");
									scanf("%d", &tepu[count].pupil.kod);
										for (int ko = 0; ; )
										{
											if (kod1 == tepu[count].pupil.kod)
											{
												printf("Данный код занят! Введите другой!\n");
												scanf("%d", &tepu[count].pupil.kod);
											}
											elseif (kod1 != tepu[count].pupil.kod)
											{
												break;
											}
										}
									j = 0;
								}
							}






							printf("ВведитеФ.И.О.: ");
							scanf("%s %s %s", tepu[count].pupil.lastname, tepu[count].pupil.name, tepu[count].pupil.middlename);
							printf("Введитепол: ");
							scanf("%s", tepu[count].pupil.gender);
							printf("Введите дату рождения(dd.mm.yy.): ");
							scanf("%d.%d.%d", &tepu[count].pupil.D1.digit, &tepu[count].pupil.D1.month, &tepu[count].pupil.D1.year);
							printf("Введитеномертелефона: ");
							scanf("%s", tepu[count].pupil.number);
							printf("Введитеадреспроживания: ");
							gets_s(tepu[count].pupil.location, 50);
							gets_s(tepu[count].pupil.location, 50);
							printf("Введитекласс: ");
							scanf("%s", tepu[count].pupil.klass);
							check[count] = 1;
							count++;
							countP++;
							vixod = -1;
							
						}

						elseif (sel1 == 2)
						{
							printf("Введите табельный номер учителя: ");
							scanf("%d", &tepu[count].teacher.tabel);

							char kod2 = tepu[count].teacher.tabel;
							for (int j = 0; j < SIZE; j++)  //исправитьб
							{
								if (tepu[count].teacher.tabel == tepu[j].teacher.tabel && count != j)
								{
									printf("Данный код занят! Введите другой!\n");
									scanf("%d", &tepu[count].teacher.tabel);
									for (int ko = 0; ; )
									{
										if (kod2 == tepu[count].teacher.tabel)
										{
											printf("Данный код занят! Введите другой!\n");
											scanf("%d", &tepu[count].teacher.tabel);
										}
										elseif (kod2 != tepu[count].teacher.tabel)
										{
											break;
										}
									}

									j = 0;
								}
							}




								printf("ВведитеФ.И.О.: ");
								scanf("%s %s %s", tepu[count].teacher.lastname, tepu[count].teacher.name, tepu[count].teacher.middlename);
								printf("Введитепреподоваеымйпредмет: ");
								gets_s(tepu[count].teacher.lesson, 15);
								gets_s(tepu[count].teacher.lesson, 15);
								printf("Введитестажработы: ");
								scanf("%d", &tepu[count].teacher.timework);
								check[count] = 2;
								count++;
								countT++;
								vixod = -1;
							}

							else
							{
								puts("НЕВЕРНО ВВЕДЕНО ЗНАЧЕНИЕ!! ");
							}

						}
						break;
					}

					caseView:
					{
						
						if (countP != 0)
						{
							printf("\t\t\t\t\t\tУЧЕНИКИ\n\n");
							for (int i = 0; i < count; i++)
							{
								if (check[i] ==1)
								{
									
									printf("Ф.И.О: %s %s %s\n", tepu[i].pupil.lastname, tepu[i].pupil.name, tepu[i].pupil.middlename);
									printf("Код: %d\n", tepu[i].pupil.kod);
									printf("Пол: %s\n", tepu[i].pupil.gender);
									printf("Датарождения: %d.%d.%d\n", tepu[i].pupil.D1.digit, tepu[i].pupil.D1.month, tepu[i].pupil.D1.year);
									printf("Номертелефона: %s\n", tepu[i].pupil.number);
									printf("Местожительства: %s\n", tepu[i].pupil.location);
									printf("Класс: %s\n", tepu[i].pupil.klass);
									printf("\n");
								}
							}
						}

						if (countT != 0)
						{
							printf("\t\t\t\t\t\tУЧИТЕЛЯ\n\n");
							for (int i = 0; i < count; i++)
						    {
									if (check[i] == 2)
									{
											printf("Ф.И.О.: %s %s %s\n", tepu[i].teacher.lastname, tepu[i].teacher.name, tepu[i].teacher.middlename);
											printf("Табельныйномер: %d\n", tepu[i].teacher.tabel);
											printf("Преподаваемыйпредмет: %s\n", tepu[i].teacher.lesson);
											printf("Стажработы: %d лет\n", tepu[i].teacher.timework);
											printf("\n");
									}
						    }
					}
					break;
				}

				caseTabl:
				{
					char str1[]{ "Номер" };
					char str2[]{ "Код" };
					char str3[]{ "Фамилия" };
					char str4[]{ "Имя" };
					char str5[]{ "Отчество" };
					char str6[]{ "Пол" };
					char str7[]{ "Класс" };

					printf("%s\t|\t%s\t|\t%10s\t|\t%10s\t|\t%10s\t|\t%s\t|\t%s\t|", str1, str2, str3, str4, str5, str6, str7);
					printf("\n");

					for (int i = 0; i < count; i++)
					{
						if (check[i] == 1)
						{
							printf("%d\t|\t%d\t|\t%10s\t|\t%10s\t|\t%10s\t|\t%s\t|\t%s\t|", i + 1, tepu[i].pupil.kod, tepu[i].pupil.lastname, tepu[i].pupil.name,
								tepu[i].pupil.middlename, tepu[i].pupil.gender, tepu[i].pupil.klass);
							printf("\n");
						}
					}
					break;
				}

				caseQuontity:
				{
					printf("Количество учителей равно %d", countT);
					break;
				}

				caseSearch:	
				{
					printf("\t\t\t\tИнформация об учителях со стажем 25-30 лет\n\n");
					
					for (int i = 0; i < count; i++)
					{
						if (tepu[i].teacher.timework >= 25 && tepu[i].teacher.timework <= 30)
						{
							printf("Учитель №%d\n", i + 1);
							printf("Ф.И.О.: %s %s %s\n", tepu[i].teacher.lastname, tepu[i].teacher.name, tepu[i].teacher.middlename);
							printf("Табельныйномер: %d\n", tepu[i].teacher.tabel);
							printf("Преподаваемыйпредмет: %s\n", tepu[i].teacher.lesson);
							printf("Стажработы: %d лет\n", tepu[i].teacher.timework);
							printf("\n");
						}
					}
					break;
				}

				caseExit:
				{
					return 0;
				}

				default:
				{
					printf("Неттакогопункта ;v; ");
				}
		}
	}
}

