#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <semaphore.h>
#include <string.h>

#define LEFT (i + N - 1) % N                                                        // устанавливаем константы
#define RIGHT (i + 1) % N
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define MAX_TIME 5
int N;
sem_t *mutex = NULL;                                                               //Объявляем семафор mutex
sem_t *eaters = NULL;                                                              //Объявляем семафор eaters
int* state = NULL;

void eat(int i) {                                                                  // функция кушат
int time = rand() % MAX_TIME;                                                     //случайно выбираем время, которое философ будет есть
printf("Philosopher #%d is eating...\n", i + 1);                                  // филосов номер такой-то ест
sleep(time);                                                                      //Ждем пока философ не поест
printf("Philosopher #%d stopped eating...\n", i + 1);                             // филосов номер такой-то перестал есть
}

void think(int i) {                                                               // функция думать
int time = rand() % MAX_TIME;                                                     //случайно выбираем время, которое философ будет думать
printf("Philosopher #%d is thinking...\n", i + 1);                                // филосов номер такой-то думает
sleep(time);                                                                      //Философ думает
printf("Philosopher #%d want to eat...\n", i+1);                                  // филосов номер такой-то хочет есть
}

//----------------------------------------------------------------------------------------------------------------------------------------------

void test(int i) {                                                                // функция тест
if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)  // 
{
state[i] = EATING;
sem_post(&eaters[i]);                                                              // Функция увеличивает (разблокирует) семафор.
}
}

void take_sticks(int i) {                                                          // взятие вилок
sem_wait(mutex);
state[i] = HUNGRY;
test(i);
sem_post(mutex);
sem_wait(&eaters[i]);
}

void put_sticks(int i) {                                                          // положить вилки
sem_wait(mutex);                                                                  // блокирует семафор
state[i] = THINKING;
test(LEFT);
test(RIGHT);
sem_post(mutex);                                                                 // Функция увеличивает (разблокирует) семафор.
}

void* philosopher(void* arg) {                                                   // философ
int i = *((int*)arg);
while (1)
{
think(i);                                                                        // думает
take_sticks(i);                                                                  // берет вилки
eat(i);                                                                          // ест
put_sticks(i);                                                                   // отпускает вилки
}
}

int main(int argc, char* argv[]) {
if (argc != 2) {
fprintf(stderr, "Usage: %s <NUMBER_OF_PHILOSOPHERS>\n", argv[0]);               // stderr — для записи на консоль.  обработка ошибок
return 1;
}
N = atoi(argv[1]);                                                              //Переводим содержимое argv[1] в тип int
if (N <= 1) {                                                                   // проверка на ошибку
fprintf(stderr, "Error by transformation of the argument...\n");                // обработка ошибок
return 2;
}
mutex = (sem_t*)malloc(sizeof(sem_t));                                         //Выдделяем память под mutex
if (sem_init(mutex, 0, 1) != 0) {                                              //Инициализируем семафор типа mutex
fprintf(stderr, "Error by creating semaphore...\n");                            //Если инициализация была проведена с ошибкой, выводим 
                                                                                //сообщение об ошибке создания семафора
return 3;
}
eaters = (sem_t*)calloc(N, sizeof(sem_t));                                     // указатель на выделенную память  sem_t - семафор
state = (int*)calloc(N, sizeof(int));                                          // указатель на выделенную память   
memset(state, 0, N);                                                          // функция из string.h заполняет N байтов блока памяти, 
                                                                              // через указатель state. 
                                                                              //Код заполняемого символа передаётся в функцию через параметр 0.
srand(time(NULL));                                                            // функция из stdlib.h выполняет инициализацию генератора
                                                                              // случайных чисел rand. 
                                                                              // Внутри функция обычно инициализируется 
                                                                              //некоторыми различными значениями, здесь при помощи time (объявлена в заголовке <time.h>) 
                                                                              // Это дает возможность получать совершенно случайные последовательности чисел, при каждом новом вызове.
pthread_t *philosophers = (pthread_t*)malloc(N * sizeof(pthread_t));          // массив индификаторов потока
int i;                                                                        // для циклов
for (i = 0; i < N; i++) {                                                     // столько же сколько и потоков будет
if (sem_init(&eaters[i], 0, 0) != 0) {                                        //Инициализируем семафор eaters
fprintf(stderr, "Error by creating semaphore...\n");                          // обработка ошибок
return 3;
}
}
int *t = (int *)malloc(sizeof(int));                                          // выделяем память под переменные
for (i = 0; i < N; i++) {                                                     // создаем N потоков (философов)
*t = i;                                                                       // для перердачи переменных, т.е. i
if (pthread_create(&philosophers[i], NULL, philosopher, t) != 0) {            // создание потока функция получает в качестве аргументов указатель на поток,
                                                                              // переменную &philosophers[i], в которую, в случае удачного завершения сохраняет id потока. 
                                                                              // используются атрибуты по умолчанию, передаем NULL. 
                                                                              // philosopher будет выполняться в новом потоке. t – аргументы, которые будут переданы функции.
fprintf(stderr, "Error by creating thread\n");                                // обработка ошибок
return 2;
}
usleep(100000);                                                               // приостанавливает работу потока, в котором она была вызвана, 
                                                                              // на указанное в аргументе время в микросекундах
                                                                              // или до поступления сигнала по которому вызывается функция обработки
}                                                                             // сигналов или программа завершает свою работу.
void* result;                                                                  // для статуса выхода из потока
for (i = 0; i < N; i++) {                                                      // всех философов
if (philosophers[i] != -1) {                                                   // проверка на ошибки
if (pthread_join(philosophers[i], &result) != 0) {                             // Функция блокирует вызывающий поток, пока указанный (все потоки) поток не завершится.
                                                                               // Если status не равен NULL, он указывает на переменную, которая принимает значение статуса 
                                                                               // выхода завершенного потока.
fprintf(stderr, "Error by joining thread\n");                                  // обработка ошибок
return 3;
}
}
}
return 0;}