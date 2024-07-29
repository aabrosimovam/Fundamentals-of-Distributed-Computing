#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;
#define N 100

int main() 
{
    vector <int> A(N), B(N);
    int summary = 0;

    #pragma omp parallel for
    for (int i = 0; i < N; i++) 
    {
        // int num = omp_get_thread_num();
        // printf("Поток %d\n", num);
        A[i] = i;
        B[i] = N - i;
    }

    #pragma omp parallel for reduction(+:summary)
    for (int i = 0; i < N; i++) 
    {
        // int num = omp_get_thread_num();
        // printf("Поток %d\n", num);
        summary += A[i] * B[i];
    }

    cout << "Скалярное произведение: " << summary << endl;
}
