#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <tgmath.h>
#include <ctime>
#include <chrono>
#include <math.h>

using namespace std;

class Process
{
  public:
  int id;
  double arrivalTime;
  double serviceTime;
  int isDone;

  Process()
  {
    id = -1;
    arrivalTime = 0;
    serviceTime = 0;
    isDone = false;
  }

  Process(double l, double Ts, int i)
  {
    double r = ((double) rand() / (RAND_MAX));
    arrivalTime = (log(1 - r)) / (-1 * l);
    double mu = 1 / Ts;
    serviceTime = (-1 / mu) * log10(r);
    isDone = 0;
    id = i;
    printf("Creating process: %d. servTime: %f. arrTime: %f.\n", id, serviceTime, arrivalTime);
  }
};

// Services a process for one CPU tick
void service(auto& start, auto& end, Process* p)
{
  std::chrono::duration<double> elapsedTime = end - start;
  if(elapsedTime.count() < p->serviceTime)
    end = std::chrono::system_clock::now();
  else
    p->isDone = 1;
}

// Check every CPU tick until the arrival time has been reached
void waitForArrival(auto& start, auto& end, Process* n, Process* Ready)
{
  std::chrono::duration<double> elapsedTime = end - start;
  if(elapsedTime.count() < n->arrivalTime)
    end = std::chrono::system_clock::now();
  else
    Ready[0] = *n;
}

// Simulate a First Come First Serve scheduler
void FCFS(double lamda, double avgServiceTime)
{
  auto start = std::chrono::system_clock::now();
  auto end = std::chrono::system_clock::now();
  Process* current = new Process(lamda, avgServiceTime, 0);
  Process* next = new Process(lamda, avgServiceTime, 1);
  Process Ready[1];
  const int maxProc = 10000;
  for(int i = 1; i < maxProc; i++)
  {
    start = std::chrono::system_clock::now();
    end = std::chrono::system_clock::now();

    // Wait until there is something in queue, and nothing is being serviced
    while((Ready[0].id == -1) || (current->isDone == 0))
    {
      if(current->isDone == 0) // Check if process has finished service
        service(start, end, current);
      if(Ready[0].id == -1) // Check if there is a process in the ready queue
        waitForArrival(start, end, next, Ready);
    }
    Ready[0].id = -1; // Dequeue the Ready Queue
    current = next; // Set the serviced process as the next one in line
    if(i+1 < maxProc)
      next = new Process(lamda, avgServiceTime, i+1); // Create a new process to arrive
  }

  delete current;
  delete next;
}

void STRF(double l, double avgTs)
{
   int maxProc = 5;
   for(int i = 0; i < maxProc; i++)
   {
     //while serviceTime > 0
     //  service current proc
     //    if serviceTime <= 0, break from while
     //    else, serviceTime = serviceTime - tickTime
     //  manage readyQ vector
     //    if next arrival not met, wait
     //    else, enqueue readyQ and make another next proc. Force readyQ and service evaluation.
     //  clock tick
     //    if tick = 0, evaluate readyQ and service
     //then evaluate readyQ and service
     //  find lowest serviceTime proc in service and readyQ
     //  Set it as current
     //  set older proc to back of readyQ vector
   }
}

void NewEvaluate(Process* Ready) // for when a process is finished
{
  
}

void ForceEvaluate(Process* Ready, Process* current) // for a forced evaluation
{

}

int main(int argc, char *argv[])
{
  int whichSim = atoi(argv[1]);
  double lamda = atof(argv[2]);
  double avgServiceTime = atof(argv[3]);
  double quantum = atof(argv[4]);

  switch(whichSim)
  {
    case 1:
      FCFS(lamda, avgServiceTime);
      break;
    case 2:
      STRF(lamda, avgServiceTime)
  }
}

