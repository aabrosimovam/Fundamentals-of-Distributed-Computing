#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex mtx;
condition_variable barrier;
int count = 0;

void bar(int id, int n) 
{
    unique_lock<mutex> lock(mtx);
    
    if (++count < n) 
    {
        barrier.wait(lock);
    } 
    else 
    {
        count = 0;
        barrier.notify_all();
    }
}

void work(int id, int n) 
{
    cout << "Поток " << id << " начал работу" << endl;
    bar(id, n);
    cout << "Поток " << id << " завершил работу" << endl;
}

int main() 
{
    int threadsNum = 5;

    thread *threads = new thread[threadsNum];

    for (int i = 0; i < threadsNum; i++) 
    {
        threads[i] = thread(work, i, threadsNum);
    }

    for (int i = 0; i < threadsNum; i++) 
    {
        threads[i].join();
    }

    delete[] threads;
}
