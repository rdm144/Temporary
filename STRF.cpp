#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <math.h>
#include <ctime>
#include <chrono>
#include <vector>

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

    void Wait(double tick)
    {
        if(arrivalTime > 0)
            arrivalTime -= tick;
        else
            hasArrived = 1;
    }
};

void STRFservice(double tick, Process* p)
{
    if(p->serviceTime > 0)
        p->serviceTime = p->serviceTime - tick;
    else
        p->isDone = 1;
}

void STRFEvaluate(std::vector<Process*> Ready, Process* current, int useCurrent) // for when a process is finished
{
    Process* lowest;
    int index = 0;
    if(useCurrent == 1 && current->serviceTime > 0){ printf("pushing function\n");
        Ready.push_back(current); }// push current on to readyQ
    lowest = Ready[0];
    printf("lowest id before loop: %d\n", lowest->id);
    for(int i = 0; i < Ready.size(); i++)
    {
        //printf("Ready has id: %d. serv time: %f\n", Ready[i]->id, Ready[i]->serviceTime);
        if(Ready[i]->serviceTime < lowest->serviceTime)
        {
            lowest = Ready[i];
            index = i;
        }
    }
    *current = *lowest; // Set newly selected process as the next to be serviced
    printf("current id after loop: %d at Ready[%d]\n", current->id, index);
    Ready.erase(Ready.begin()+index); // remove the newly selected process from readyQ
}

void STRF(double l, double Ts)
{
    Process* current = new Process(l, Ts, 0);
    Process* next = new Process(l, Ts, 1);
    double clockTick = 0;
    vector<Process*> Ready;
    for(int i = 0; i < 5; i++)
    {
        auto start = std::chrono::system_clock::now();
        auto end = std::chrono::system_clock::now();
        printf("******** for loop index %d ************\n", i);
        printf("Current id: %d. Current ServiceTime: %f\n", current->id, current->serviceTime);
        while(current->isDone == 0)
        {
            printf("Current id: %d. clockTick: %f\n", current->id, clockTick);
            STRFservice(clockTick, current);
            next->Wait(clockTick);
            if(next->hasArrived == 1)
            {
                printf("pushing inner\n");
                Ready.push_back(next); // add next to readyQ
                STRFEvaluate(Ready, current, 1); // force service evaluation
                Process* temp = next;
                next = new Process(l, Ts, temp->id + 1); // Create a new next process
                delete temp;
            }
            if(clockTick == 0)
                clockTick = 0.001;//(end - start).count(); // change deltaTime if it is zero
        }
        while(Ready.size() < 1)
        {
            next->Wait(clockTick);
            if(next->hasArrived == 1)
            {
                printf("pushing outer\n");
                Ready.push_back(next); // add next to readyQ
                Process* temp = next;
                next = new Process(l, Ts, temp->id + 1); // Create a new next process
                delete temp;
            }
        }
        printf("Outer evaluation\n");
        STRFEvaluate(Ready, current, 0); // force service evaluation
        printf("######## Current id at end of loop: %d ############\n", current->id);
    }
}

int main()
{
    double lamda = 5;
    double avgServiceTime = 0.06;
    STRF(lamda, avgServiceTime);
    return 0;
}