#include <iostream>
#include <ctime>
#include <iomanip>
#include <thread>

using namespace std;

void random_number(float *array, float a, int left, int right)
{
    for (int i = left; i < right; i++)
    {
        array[i]=((float)rand()/(float)(RAND_MAX))*a;
    }
}

int main()
{
    int n=14, k=3;
    thread *tr= new thread[k];
    float *array= new float[n];

    srand(time(0));

    int length = n / k;

    for (int i=0; i<k; i++)
    {
        float a=((float)rand()/(float)(RAND_MAX));

        int left = i * length;
        int right;
        if (i==(k-1)) { right = n; }
        else { right = left + length; }

        tr[i]=thread(random_number,array ,a, left, right);      
    }
    

    for (int i=0; i<k; i++)
    {
        tr[i].join();
    }

    for (int i=0; i<n; i++)
    {
        cout<<array[i]<<endl;
    }

    delete[] array; 
    delete[] tr;
    //system("pause");
}