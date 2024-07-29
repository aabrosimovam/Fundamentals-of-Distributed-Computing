#include <iostream> 
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <shared_mutex>

using namespace std;

shared_mutex last,first, add_del;

class Queue
{
  queue <int> q;

public:
  Queue(){}
  ~Queue(){}

  void Add(int x)
  {
    lock_guard<shared_mutex> lock2(last); // -> last.lock()
    unique_lock<shared_mutex> lockall(add_del, defer_lock);
    if (q.size() == 1) lock_guard<shared_mutex> lockall(add_del);
    //else lock_guard<shared_mutex> lock(last);
    q.push(x);  

  }

  void Del()
  {
    lock_guard<shared_mutex> lock1(first);
    unique_lock<shared_mutex> lockall(add_del, defer_lock);
    if (q.empty())
      {
        cout<<"Queue is empty"<<endl;
        exit(EXIT_FAILURE);
      }
    if (q.size() == 1) lock_guard<shared_mutex> lockall(add_del);
    //else lock_guard<shared_mutex> lock(first);
    q.pop();
  }

  void max()
  {
    last.lock_shared();
    first.lock_shared();
    if (q.empty())
    {
      cout << "Queue is empty"<<endl;
      last.unlock_shared();
      first.unlock_shared();
      exit(EXIT_FAILURE);
    }
    queue <int> qmax = q;
    int MAX = qmax.front();
    while (!qmax.empty())
    {
      if (qmax.front() > MAX)MAX = qmax.front();
      qmax.pop();
    }
    cout << "max = " << MAX << endl;
    last.unlock_shared();
    first.unlock_shared();
  }

  void min()
  {
    last.lock_shared();
    first.lock_shared();
    if (q.empty())
    {
      cout << "Queue is empty "<<endl;
      last.unlock_shared();
      first.unlock_shared();
      exit(EXIT_FAILURE);
    }
    queue <int> qmin = q;
    int MIN = qmin.front();
    while (!qmin.empty())
    {
      if (qmin.front() < MIN)MIN = qmin.front();
      qmin.pop();
    }
    cout << "min = " << MIN << endl;
    last.unlock_shared();
    first.unlock_shared();
  }

  void Output()
  {
    last.lock_shared();
    first.lock_shared();
    if (q.empty())
    {
      cout << "Queue is empty "<<endl;
      last.unlock_shared();
      first.unlock_shared(); 
      exit(EXIT_FAILURE);
    }
    queue <int> qout = q;
    while (!qout.empty())
    {
      cout << qout.front()<<' ';
      qout.pop();
    }
    cout << endl;
    last.unlock_shared();
    first.unlock_shared();
  }
};

int main()
{
  Queue q;
  q.Add(1);
  // q.Add(2);
  // q.Add(4);

  int k = 8;
  thread *tr = new thread[k];

  tr[0] = thread(&Queue::Output, &q);
  tr[5] = thread(&Queue::Add,&q,3);
  tr[1] = thread(&Queue::Del,&q);
  tr[2] = thread(&Queue::Output, &q);
  tr[3] = thread(&Queue::min, &q);
  tr[4] = thread(&Queue::max, &q);
  tr[6] = thread(&Queue::Del,&q);
  tr[7] = thread(&Queue::Output, &q);

  for (int i = 0; i < k; i++)
  {
    tr[i].join();
  }

  delete[] tr;
}