#include <iostream>
#include <omp.h>
#include <chrono>

using namespace std;

int main()
{
    int n = 400;
    int A[n][n], B[n][n];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            A[i][j] = i + j;
            B[i][j] = i * j;
        }
    }

    // перемножение матриц
    int C[n][n];

    auto start = chrono::high_resolution_clock::now();

    omp_set_num_threads(8);
    #pragma omp parallel 
    // #pragma omp for schedule (static, 6)
    // #pragma omp for schedule (dynamic, 6)
    // #pragma omp for schedule (dynamic, 2)
     #pragma omp for schedule (guided, 6)
    for (int i = 0; i < n; i++) 
    {
        // int num = omp_get_thread_num();
        // printf("Поток %d\n", num);
        for (int j = 0; j < n; j++) 
        {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) 
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto result = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Прошедшее время в милисекундах: " << result.count() << " ms" << endl;

}
