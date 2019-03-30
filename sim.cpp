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
  double waitTime;
  int isDone;
  int hasArrived;

  Process()
  {
    id = -1;
    arrivalTime = 0;
    serviceTime = 0;
    waitTime = 0;
    hasArrived = 0;
    isDone = 0;
  }

  Process(double l, double Ts, int i)
  {
    double r = ((double) rand() / (RAND_MAX));
    arrivalTime = (log(1 - r)) / (-1 * l);
    double mu = 1 / Ts;
    serviceTime = (-1 / mu) * log10(r);
    isDone = 0;
    hasArrived = 0;
    waitTime = 0;
    id = i;
    printf("Creating process: %d. servTime: %f. arrTime: %f.\n", id, serviceTime, arrivalTime);
  }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Services a process for one CPU tick
void FCFSservice(auto& start, auto& end, Process* p)
{
  std::chrono::duration<double> elapsedTime = end - start;
  if(elapsedTime.count() < p->serviceTime)
    end = std::chrono::system_clock::now();
  else
    p->isDone = 1;
}

// Check every CPU tick until the arrival time has been reached
void FCFSwaitForArrival(auto& start, auto& end, Process* n, Process* Ready)
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
        FCFSservice(start, end, current);
      if(Ready[0].id == -1) // Check if there is a process in the ready queue
        FCFSwaitForArrival(start, end, next, Ready);
    }
    Ready[0].id = -1; // Dequeue the Ready Queue
    current = next; // Set the serviced process as the next one in line
    if(i+1 < maxProc)
      next = new Process(lamda, avgServiceTime, i+1); // Create a new process to arrive
  }

  delete current;
  delete next;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void STRF(double l, double avgTs)
{
  const double interval = avgTs;
  Process* current = new Process(lamda, avgServiceTime, i);
  Process* next = new Process(lamda, avgServiceTime, i+1);
  vector<Process*> Ready[];
  int maxProc = 5;
  for(int i = 1; i < maxProc; i++)
  {
    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();
    double clockTick = 0;
    while(current->isDone == 0)
    {
      STRFservice(clockTick, current); // service for one clock tick
      if(next->hasArrived == 0)
        STRFwait(start, end, next); // wait for next's arrival by one clock tick
      else
      {
        Ready.push_back(next); // add next to readyQ
        STRFEvaluate(Ready, current, 1); // force service evaluation
        Process* temp = next;
        next = new Process(lamda, avgServiceTime, temp->id + 1); // Create a new next process
        delete temp;
      }
      if(clockTick == 0)
        clockTick = (end - start).count(); // change deltaTime if it is zero
    }
    STRFEvaluate(Ready, current, 0);
  }
  delete current;
  delete next;
}

void STRFservice(double tick, Process* p)
{
  if(p->serviceTime > 0)
    p->serviceTime = p->serviceTime - tick;
  else
    p->isDone = 1;
}

void STRFwait(auto& start, auto& end, Process* p)
{
  std::chrono::duration<double> elapsedTime = end - start;
  if(elapsedTime.count() < n->arrivalTime)
    end = std::chrono::system_clock::now();
  else
    p->hasArrived = 1;
}

void STRFEvaluate(Process* Ready, Process* current, int useCurrent) // for when a process is finished
{
  Process lowest;
  int index = -1;
  if(useCurrent == 1)
    Ready.push_back(current); // push current on to readyQ
  lowest = Ready[0];
  for(int i = 0; i < Ready.size(); i++)
  {
    if(Ready[i]->serviceTime < lowest->serviceTime)
    {
      lowest = Ready[i];
      index = i;
    }
  }
  current = lowest; // Set newly selected process as the next to be serviced
  Ready.erase(Ready.begin()+index); // remove the newly selected process from readyQ
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void HRRN(double l, double avgTs)
{
  const double interval = avgTs;
  Process* current = new Process(lamda, avgServiceTime, i);
  Process* next = new Process(lamda, avgServiceTime, i+1);
  vector<Process*> Ready[];
  int maxProc = 5;
  for(int i = 1; i < maxProc; i++)
  {
    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();
    double clockTick = 0;
    while(current->isDone == 0)
    {
      HRRNservice(current); // service for one clock tick.
      if(next->hasArrived == 0)
        HRRNwait(start, end, next); // wait for next's arrival by one clock tick
      else
      {
        Ready.push_back(next); // add next to readyQ
        Process* temp = next;
        next = new Process(lamda, avgServiceTime, temp->id + 1); // Create a new next process
        delete temp;
      }
      if(clockTick == 0)
        clockTick = (end - start).count();
      HRRNtickWait(clockTick, Ready);
    }
    HRRNEvaluate(Ready, current);
  }
  delete current;
  delete next;
}

void HRRNservice(auto& start, auto& end, Process* p)
{
  std::chrono::duration<double> elapsedTime = end - start;
  if(elapsedTime.count() < p->serviceTime)
    end = std::chrono::system_clock::now();
  else
    p->isDone = 1;
}

void HRRNwait(auto& start, auto& end, Process* p)
{
  std::chrono::duration<double> elapsedTime = end - start;
  if(elapsedTime.count() < n->arrivalTime)
    end = std::chrono::system_clock::now();
  else
    p->hasArrived = 1;
}

void HRRNtickWait(double tick, Process* Ready)
{
  for(int i = 0; i < Ready.size(); i++)
  {
    Ready[i]->waitTime = Ready[i]->waitTime + tick;
  }
}

void HRRNtickClock(auto& start, auto& end, int& interrupt, double interval)
{
  std::chrono::duration<double> elapsedTime = end - start;
  if(interval < elapsedTime.count())
    interrupt = 1;
  else
    end = std::chrono::system_clock::now();
}

void HRRNEvaluate(Process* Ready, Process* current) // for when a process is finished
{
  Process selected;
  int index = -1;
  double highestRatio = 0;
  selected = Ready[0];
  for(int i = 0; i < Ready.size(); i++)
  {
    double tempRatio = (Ready[i]->waitTime + Ready[i]->serviceTime) / Ready[i]->serviceTime;
    if(tempRatio > highestRatio)
    {
      highestRatio = tempRatio;
      selected = Ready[i];
      index = i;
    }
  }
  current = selected; // Set newly selected process as the next to be serviced
  Ready.erase(Ready.begin()+index); // remove the newly selected process from readyQ
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RR(double l, double mu)
{
  const double interval = mu;
  double timeSinceInterrupt = 0;
  int interrupt = 0;
  Process* current = new Process(lamda, avgServiceTime, i);
  Process* next = new Process(lamda, avgServiceTime, i+1);
  vector<Process*> Ready[];
  int maxProc = 5;
  for(int i = 1; i < maxProc; i++)
  {
    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();
    double clockTick = 0;
    while(current->isDone == 0)
    {
      RRservice(clockTick, current); // service for one clock tick
      if(next->hasArrived == 0)
        RRwait(start, end, next); // wait for next's arrival by one clock tick
      else
      {
        Ready.push_back(next); // add next to readyQ
        RREvaluate(Ready, current, 1); // force service evaluation
        Process* temp = next;
        next = new Process(lamda, avgServiceTime, temp->id + 1); // Create a new next process
        delete temp;
      }

      RRtickClock(clockTick, *timeSinceInterrupt, *interrupt, mu);
      if(interrupt == 1)
      {
        RREvaluate(Ready, current, 1); // force service evaluation
        interrupt = 0;
      }
      if(clockTick == 0)
        clockTick = (end - start).count(); // change deltaTime if it is zero
    }
    RREvaluate(Ready, current, 0);
  }
  delete current;
  delete next;
}

void RRtickClock(double tick, double& currentTime, double& interrupt, double quantum)
{
  currentTime += tick;
  if(currentTime >= quantum)
  {
    interrupt = true;
    currentTime = 0;
  }
}

void RRservice(double tick, Process* p)
{
  p->serviceTime = p->serviceTime - tick;
  if(p->serviceTime <= 0)
    p->isDone = 1;
}

void RRwait(auto& start, auto& end, Process* p)
{
  std::chrono::duration<double> elapsedTime = end - start;
  if(elapsedTime.count() < n->arrivalTime)
    end = std::chrono::system_clock::now();
  else
    p->hasArrived = 1;
}

void RREvaluate(Process* Ready, Process* current, int useCurrent) // for when a process is finished
{
  Process lowest;
  int index = -1;
  if(useCurrent == 1)
    Ready.push_back(current); // push current on to readyQ
  lowest = Ready[0];
  for(int i = 0; i < Ready.size(); i++)
  {
    if(Ready[i]->serviceTime < lowest->serviceTime)
    {
      lowest = Ready[i];
      index = i;
    }
  }
  current = lowest; // Set newly selected process as the next to be serviced
  Ready.erase(Ready.begin()+index); // remove the newly selected process from readyQ
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
      STRF(lamda, avgServiceTime);
      break;
    case 3:
      HRRN(lamda, avgServiceTime);
      break;
    case 4:
      RR(lamda, mu);
      break;
    default:
      break;
  }
}

