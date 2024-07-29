#include <iostream>
#include <queue>
#include <omp.h>
#include "windows.h"
#include <chrono>
#include <functional>
// чтобы позволить сохранить, передавать и вызывать функции как объекты

using namespace std;

void f1() { Sleep(2000); cout << "Задача 1" << endl; }
void f2() { Sleep(3000); cout << "Задача 2" << endl; }
void f3(int a) { cout << "Задача " << a << endl;}
void f4() { Sleep(4000); cout << "Задача 4" << endl; }
void f5() { Sleep(1000); cout << "Задача 5" << endl; }
void f6() { cout << "Задача 6" << endl; }


int main() 
{
    queue<function<void()>> tasks;
    // создаю очередь tasks, котоорая хранит функции 

    int a = 3; 

    tasks.push([](){ f1(); });
    tasks.push([](){ f2(); });
    tasks.push([a](){ f3(a); });
    tasks.push([](){ f4(); });
    tasks.push([](){ f5(); });
    tasks.push([](){ f6(); });

    const int numThreads = 5;
    auto start = chrono::high_resolution_clock::now();
    #pragma omp parallel num_threads(numThreads)
    {
        while (!tasks.empty()) 
        {
            function<void()> task; 
            // создается объект типа task, который будет использоваться для выполнения задач из очереди
            #pragma omp critical
            {
                if (!tasks.empty()) 
                {
                    task = tasks.front();
                    tasks.pop();
                }
            }
            if (task) 
            {
                // int num = omp_get_thread_num(); printf("Поток %d\n", num);
                task();
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    auto result = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Прошедшее время в миллисекундах: " << result.count() << " ms" << endl;
}
