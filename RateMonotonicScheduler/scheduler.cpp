#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

int prod = 0;
int work[10][10] =
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
};

void doWork(int arr[10][10])
{
  for (int j = 0; j < 10; j++)
  {
      for (int i = 0; i < 10; i++) {
        prod = arr[i][j] * arr[i][j];
      }
  }
}

int main()
{
  doWork(work);
}
