#include <iostream>
#include <thread>

using namespace std;

void f(int N)
{
    while (N>=0)
    {
        cout<< N << endl;
        N--;
        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main()
{
    int n=9;
    thread tr(f,n);
    thread th(f,n);
    th.join();
    tr.join();
    //system("pause");
}