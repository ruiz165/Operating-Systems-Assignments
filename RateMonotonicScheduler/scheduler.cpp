#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

mutex m;

int workArr[10][10] =
{
  {1,1,1,1,1,1,1,1,1,1},
  {2,1,1,1,1,1,1,1,1,1},
  {3,1,1,1,1,1,1,1,1,1},
  {4,1,1,1,1,1,1,1,1,1},
  {5,1,1,1,1,1,1,1,1,1},
  {6,1,1,1,1,1,1,1,1,1},
  {7,1,1,1,1,1,1,1,1,1},
  {8,1,1,1,1,1,1,1,1,1},
  {9,1,1,1,1,1,1,1,1,1},
  {10,1,1,1,1,1,1,1,1,1}
}

void doWork(int arr[10][10])
{
  for (int i = 0; i < 10; i++)
  {
    int sum = 1;
    for (int j = 0; j < 10; j++) {
      sum = sum * arr[j][i];
    }
  }
}

void scheduleThreads(thread t1, thread t2, thread t3, thread t4)
{

}

void thread1()
{
  int t1_count = 0;
  
  doWork(workArr);
}