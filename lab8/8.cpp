#include <iostream>
#include <cmath>
#include <omp.h>
#include <chrono>

using namespace std;

double f(double x) { return sin(x); }

double integral(double a, double b, int n, int NT) 
{
    double sum = 0.0;
    double h = (b - a) / n; // "ширина" прямоугольника

    // метод средних прямоугольников
    omp_set_num_threads(NT);
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; ++i) 
    {
        double xi = a + (i + 0.5) * h;
        sum += f(xi);
    }
    return sum * h;
}

int main() 
{
    double a = 0.0;
    double b = M_PI; // значение пи
    int n = 10000000; // количество прямоугольников


    int numThreads = 8;
    auto start1 = chrono::high_resolution_clock::now();
    double result1 = integral(a, b, n, numThreads);
    auto end1 = chrono::high_resolution_clock::now();

    auto result_time1 = chrono::duration_cast<chrono::milliseconds>(end1 - start1);

    cout << "Количество потоков: " << numThreads;
    cout << " Прошедшее время: " << result_time1.count() << " ms" << endl;
    cout << "Определенный интеграл: " << result1 << endl;


    numThreads = 1;
    auto start2 = chrono::high_resolution_clock::now();
    double result2 = integral(a, b, n, numThreads);
    auto end2 = chrono::high_resolution_clock::now();

    auto result_time2 = chrono::duration_cast<chrono::milliseconds>(end2 - start2);

    cout << "Количество потоков: " << numThreads;
    cout << " Прошедшее время: " << result_time2.count() << " ms" << endl;
    cout << "Определенный интеграл: " << result2 << endl;
}
