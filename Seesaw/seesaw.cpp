#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <unistd.h>

using namespace std;

struct Semaphore {
  int size;
  atomic<int> count;
  mutex updateMutex;

  Semaphore(int n) : size(n) { count.store(0); }
  void signal() {
      while (1) {
          while (count >= size) {}
          updateMutex.lock();
          if (count >= size) {
              updateMutex.unlock();
              continue;
          }
          ++count;
          updateMutex.unlock();
          break;
      }
  }

  void wait() {
      updateMutex.lock();
      if (count > 0) {
          --count;
      }
      updateMutex.unlock();
  }
};

int count = 0;
double fHeight = 1.0, wHeight = 7.0;
Semaphore fredSemaphore(10);
Semaphore wilmaSemaphore(10);

void fredSee()
{
  if(fHeight < 7 )
  {
    while(fHeight != 7)
    {
      fredSemaphore.wait();
      fHeight++;
      wHeight--;
      cout << "Fred is " << fHeight << " feet off the ground.\n";
      sleep(1);
      fredSemaphore.signal();
    }
  }
  else
  {
    while(fHeight != 1)
    {
      fredSemaphore.wait();
      fHeight--;
      wHeight++;
      cout << "Fred is " << fHeight << " feet off the ground.\n";
      sleep(1);
      fredSemaphore.signal();
    }
  }
}

void wilmaSaw()
{
  if( wHeight > 1 )
  {
    while(wHeight != 7)
    {
      wilmaSemaphore.wait();
      wHeight = wHeight + 1.5;
      fHeight = fHeight - 1.5;
      cout << "Wilma is " << wHeight << " feet off the ground.\n";
      sleep(1);
      wilmaSemaphore.signal();
    }
  }
  else
  {
    while(wHeight != 1)
    {
      wilmaSemaphore.wait();
      wHeight = wHeight - 1.5;
      fHeight = fHeight + 1.5;
      cout << "Wilma is " << wHeight << " feet off the ground.\n";
      sleep(1);
      wilmaSemaphore.signal();
    }
  }
}

int main()
{

  while(count < 20)
  {
    thread t1(fredSee);
    thread t2(wilmaSaw);
    t1.join();
    t2.join();
    count++;
  }
  //thread t1(fredSee);
  //thread t2(wilmaSaw);

  //t1.join();
  //t2.join();
}














//
