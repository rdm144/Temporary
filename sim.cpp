#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <math.h>
#include <ctime>
#include <chrono>
#include <vector>
#include <string>
#include <fstream>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h>
#include <unistd.h> 

using namespace std;

struct EventQueue
{
  double serviceList[10000];
  double waitList[10000];
  int queueList[10000];
  int cpuUtilList[10000];
};

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
    arrivalTime = (log(r)) / (-1 * l);
    double mu = 1 / Ts;
    serviceTime = (-1 / mu) * log10(r);
    isDone = 0;
    hasArrived = 0;
    waitTime = 0;
    id = i;
  }

  void service(double tick)
  {
    serviceTime -= tick;
    if(serviceTime <= 0)
      isDone = 1;
  }

  void ArrivalWait(double tick)
  {
    arrivalTime -= tick;
    if(arrivalTime <= 0)
      hasArrived = 1;
  }

  void Wait(double tick)
  {
    this->waitTime = this->waitTime + tick;
  }
};

int getCPU() 
{
	int FileHandler;
	char FileBuffer[1024];
	float load;

	FileHandler = open("/proc/loadavg", O_RDONLY);
	if(FileHandler < 0) 
    return -1; 
  read(FileHandler, FileBuffer, sizeof(FileBuffer) - 1);
  sscanf(FileBuffer, "%f", &load);
	close(FileHandler);
  return (int)(load * 100);
}

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
  printf("FCFS\n");
  EventQueue e;
  auto start = std::chrono::system_clock::now();
  auto startAbs = std::chrono::system_clock::now();
  auto end = std::chrono::system_clock::now();
  Process* current = new Process(lamda, avgServiceTime, 0);
  Process* next = new Process(lamda, avgServiceTime, 1);
  Process Ready[1];
  const int maxProc = 10;

  e.serviceList[current->id] = current->serviceTime;
  e.waitList[current->id] = current->waitTime;
  e.serviceList[next->id] = next->serviceTime;
  e.waitList[next->id] = next->waitTime;
  e.cpuUtilList[0] = getCPU();
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
    {
      next = new Process(lamda, avgServiceTime, i+1); // Create a new process to arrive
      e.serviceList[next->id] = next->serviceTime;
      e.waitList[next->id] = next->waitTime;
    }
    e.cpuUtilList[i] = getCPU();
  }

  delete current;
  delete next;

  auto endAbs = std::chrono::system_clock::now();
  double totalTime = (endAbs - startAbs).count();
  double totalService = 0;
  double totalWait = 0;
  int totalcpu = 0;
  for(int i = 0; i < 10000; i++)
  {
    totalService = totalService + e.serviceList[i];
    totalWait = totalWait + e.waitList[i];
    totalcpu = totalcpu + e.cpuUtilList[i];
  }
  ofstream data;
  data.open("data.txt", ofstream::app);
  data << "FCFS," << lamda << "," << (totalService + totalWait)/10000 << "," << 10000/totalTime << "," << totalcpu/10000 << "," << 1 << endl;
  data.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void HRRNevaluate(Process* current, vector<Process*>& Ready, int& candidates)
{
  double highestRatio = 0;
  int index = -1;
  for(int i = 0; i < Ready.size(); i++)
  {
    if(Ready[i]->id > -1)
    {
      double tempRatio = (Ready[i]->waitTime + Ready[i]->serviceTime) / Ready[i]->serviceTime;
      if(highestRatio < tempRatio)
        index = i;
    }
  }
  *current = *Ready[index];
  Ready[index]->id = -1;
  candidates --;
}

void HRRNtickWaitTime(double tick, vector<Process*>& Ready)
{
  for(int i = 0; i < Ready.size(); i++)
      Ready[i]->Wait(tick);
}

void HRRN(double l, double ts)
{
  printf("HRRN\n");
  EventQueue e;
  double clockTick = 0.001;
  vector<Process*> Ready;
  Process* current = new Process(l, ts, 0);
  Process* next = new Process(l, ts, 1);
  int candidates = 0;
  e.serviceList[current->id] = current->serviceTime;
  e.waitList[current->id] = current->waitTime;
  e.serviceList[next->id] = next->serviceTime;
  e.waitList[next->id] = next->waitTime;
  e.cpuUtilList[0] = getCPU();
  auto startAbs = std::chrono::system_clock::now();
  for(int i = 0; i < 10000; i++)
  {
    while(current->isDone == 0)
    {
      current->service(clockTick);
      HRRNtickWaitTime(clockTick, Ready);
      if(next->hasArrived == 0)
        next->ArrivalWait(clockTick);
      else
      {
        e.waitList[next->id] = next->waitTime;
        Process* temp = next;
        Ready.push_back(temp);
        next = new Process(l, ts, temp->id+1);
        e.serviceList[next->id] = next->serviceTime;
        candidates++;
      }
    }
    while(candidates < 1)
    {
      next->ArrivalWait(clockTick);
      if(next->hasArrived == 1)
      {
        e.waitList[next->id] = next->waitTime;
        Process* temp = next;
        Ready.push_back(temp);
        next = new Process(l, ts, temp->id+1);
        e.serviceList[next->id] = next->serviceTime;
        candidates++;
      }
    }
    HRRNevaluate(current, Ready, candidates);
    e.queueList[i] = Ready.size();
    e.cpuUtilList[i] = getCPU();
  }
  auto endAbs = std::chrono::system_clock::now();
  double totalTime = (endAbs - startAbs).count();
  double totalService = 0;
  double totalWait = 0;
  int totalcpu = 0;
  int totalQ = 0;
  for(int i = 0; i < 10000; i++)
  {
    totalService = totalService + e.serviceList[i];
    totalWait = totalWait + e.waitList[i];
    totalcpu = totalcpu + e.cpuUtilList[i];
    totalQ = totalQ + e.queueList[i];
  }
  ofstream data;
  data.open("data.txt", ofstream::app);
  //type, lamda, avg turnaround, throughput, avg cpu, avg num proc in ready Q.
  data << "HRRN," << l << "," << (totalService + totalWait)/10000 << "," << 10000/totalTime << "," << totalcpu/10000 << "," << totalQ/10000 << endl;
  data.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void STRFservice(double tick, Process* p)
{
    if(p->serviceTime > 0)
        p->serviceTime = p->serviceTime - tick;
    else
        p->isDone = 1;
}

void STRFEvaluate(std::vector<Process*>& Ready, Process* current, int useCurrent, int& candidates) // for when a process is finished
{
    int index = 0;
    double lowest = 999;
    if(useCurrent == 1 && current->serviceTime > 0)
        Ready.push_back(current);// push current on to readyQ

    for(int i = 0; i < Ready.size(); i++)
    {
      if(Ready[i]->id > -1)
      {
        if(Ready[i]->serviceTime < lowest)
        {
          index = i;
          lowest = Ready[i]->serviceTime;
        }
      }
    }
    *current = *Ready[index]; // Set newly selected process as the next to be serviced
    Ready[index]->id = -1; // remove the newly selected process from readyQ
    candidates--;
}

void STRF(double l, double Ts)
{
    printf("STRF\n");
    Process* current = new Process(l, Ts, 0);
    Process* next = new Process(l, Ts, 1);
    double clockTick = 0.001;
    vector<Process*> Ready;
    int candidates = 0;
    EventQueue e;
    e.serviceList[current->id] = current->serviceTime;
    e.waitList[current->id] = current->waitTime;
    e.serviceList[next->id] = next->serviceTime;
    e.waitList[next->id] = next->waitTime;
    e.cpuUtilList[0] = getCPU();
    auto startAbs = std::chrono::system_clock::now();
    for(int i = 0; i < 10000; i++)
    {
        auto start = std::chrono::system_clock::now();
        auto end = std::chrono::system_clock::now();
        while(current->isDone == 0)
        {
            STRFservice(clockTick, current);
            HRRNtickWaitTime(clockTick, Ready);
            next->ArrivalWait(clockTick);
            if(next->hasArrived == 1)
            {
                e.waitList[next->id] = next->waitTime;
                Ready.push_back(next); // add next to readyQ
                STRFEvaluate(Ready, current, 1, candidates); // force service evaluation
                Process* temp = next;
                next = new Process(l, Ts, temp->id + 1); // Create a new next process
                e.serviceList[next->id] = next->serviceTime;
                candidates++;
            }
        }
        while(candidates < 1)
        {
            next->ArrivalWait(clockTick);
            if(next->hasArrived == 1)
            {
                e.waitList[next->id] = next->waitTime;
                Ready.push_back(next); // add next to readyQ
                Process* temp = next;
                next = new Process(l, Ts, temp->id + 1); // Create a new next process
                e.serviceList[next->id] = next->serviceTime;
                candidates++;
            }
        }
        STRFEvaluate(Ready, current, 0, candidates); // force service evaluation
        e.queueList[i] = Ready.size();
        e.cpuUtilList[i] = getCPU();
    }
  auto endAbs = std::chrono::system_clock::now();
  double totalTime = (endAbs - startAbs).count();
  double totalService = 0;
  double totalWait = 0;
  int totalcpu = 0;
  int totalQ = 0;
  for(int i = 0; i < 10000; i++)
  {
    totalService = totalService + e.serviceList[i];
    totalWait = totalWait + e.waitList[i];
    totalcpu = totalcpu + e.cpuUtilList[i];
    totalQ = totalQ + e.queueList[i];
  }
  ofstream data;
  data.open("data.txt", ofstream::app);
  //type, lamda, avg turnaround, throughput, avg cpu, avg num proc in ready Q.
  data << "STRF," << l << "," << (totalService + totalWait)/10000 << "," << 10000/totalTime << "," << totalcpu/10000 << "," << totalQ/10000 << endl;
  data.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RRservice(double tick, Process* p)
{
    if(p->serviceTime > 0)
        p->serviceTime = p->serviceTime - tick;
    else
    {
        p->isDone = 1;
        p->id = -1;
    }
}

void RRevaluate(vector<Process*>& Ready, Process* current, int useCurrent, int& index, int& candidates)
{
  if(useCurrent == 1 && current->serviceTime > 0)
    //Ready.push_back(current);
  do{
    index++;
  }while(Ready[index]->id < 0);
  
  
  if(index > Ready.size() - 1)
    index = 0;
  *current = *(Ready[index]);
  candidates--;
}

void RR(double l, double ts, double mu)
{
  printf("RR\n");
  double currentTime = 0;
  Process* current = new Process(l, ts, 0);
  Process* next = new Process(l, ts, 1);
  double clockTick = 0.001;
  vector<Process*> Ready;
  int candidates = 0;
  int prevIndex = -1;
  EventQueue e;
    e.serviceList[current->id] = current->serviceTime;
    e.waitList[current->id] = current->waitTime;
    e.serviceList[next->id] = next->serviceTime;
    e.waitList[next->id] = next->waitTime;
    e.cpuUtilList[0] = getCPU();
    auto startAbs = std::chrono::system_clock::now();
  for(int i = 0; i < 10000; i++)
  {
    while(true)
    {
      HRRNtickWaitTime(clockTick, Ready);
      if(currentTime < mu)
        currentTime += clockTick;
      else
      {
        while(candidates < 1)
        {
          if(next->hasArrived == 0)
            next->ArrivalWait(clockTick); //wait one tick
          else
          {
            e.waitList[next->id] = next->waitTime;
            Ready.push_back(next); // Add next to readyQ
            Process* temp = next;
            next = new Process(l, ts, temp->id + 1);
            candidates++;
            e.serviceList[next->id] = next->serviceTime;
          }
        }
        RRevaluate(Ready, current, 1, prevIndex, candidates); //evaluate with current
        currentTime = 0;
      }
        
      if(next->hasArrived == 0)
        next->ArrivalWait(clockTick); //wait one tick
      else
      {
        e.waitList[next->id] = next->waitTime;
        Ready.push_back(next); // Add next to readyQ
        Process* temp = next;
        next = new Process(l, ts, temp->id + 1);
        e.serviceList[next->id] = next->serviceTime;
        RRevaluate(Ready, current, 1, prevIndex, candidates); //evaluate with current
      }
        
      if(current->isDone == 0)
        RRservice(clockTick, current); //service
      else
      {
        while(candidates < 1)
        {
          if(next->hasArrived == 0)
            next->ArrivalWait(clockTick); //wait one tick
          else
          {
            e.waitList[next->id] = next->waitTime;
            Ready.push_back(next); // Add next to readyQ
            Process* temp = next;
            next = new Process(l, ts, temp->id + 1);
            candidates++;
            e.serviceList[next->id] = next->serviceTime;
          }
        }
        RRevaluate(Ready, current, 0, prevIndex, candidates); //evaluate without current
        //break;
      }
      
    }
    e.queueList[i] = Ready.size();
    e.cpuUtilList[i] = getCPU();
  }
  auto endAbs = std::chrono::system_clock::now();
  double totalTime = (endAbs - startAbs).count();
  double totalService = 0;
  double totalWait = 0;
  int totalcpu = 0;
  int totalQ = 0;
  for(int i = 0; i < 10000; i++)
  {
    totalService = totalService + e.serviceList[i];
    totalWait = totalWait + e.waitList[i];
    totalcpu = totalcpu + e.cpuUtilList[i];
    totalQ = totalQ + e.queueList[i];
  }
  ofstream data;
  data.open("data.txt", ofstream::app);
  //type, lamda, avg turnaround, throughput, avg cpu, avg num proc in ready Q.
  data << "RR," << l << "," << (totalService + totalWait)/10000 << "," << 10000/totalTime << "," << totalcpu/10000 << "," << totalQ/10000 << endl;
  data.close();
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
      RR(lamda, avgServiceTime, quantum); // Broken! Seg faults!
    default:
      break;
  }
  return 0;
}

