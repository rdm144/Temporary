#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <tgmath.h>
#include <time.h>
#include <unistd.h>

using namespace std;

void FCFS(float l, float Ts)
{
  float r = (float)(rand()) / (float)(RAND_MAX);
  
  printf("FCFS!\n");\
  float mu = 1 / Ts;
  printf("Mu: %f\n", mu);
  for(int i = 0; i < 31; i++)
  {
    srand ((time(NULL)));
    float arrivalTime = (log(1 - r)) / (-1 * l);
    
    float serviceTime = (-1 / mu) * log10(r);
    printf("#%d Arrival Time: %f\n", i, arrivalTime);
    sleep(serviceTime);
    printf("#%d Service Time: %f\n", i, serviceTime);
  }
  
}

int main(int argc, char *argv[])
{
  int whichSim = atoi(argv[1]);
  float lamda = atof(argv[2]);
  float avgServiceTime = atof(argv[3]);
  float quantum = atof(argv[4]);

  switch(whichSim)
  {
    case 1:
      FCFS(lamda, avgServiceTime);
      break;
  }
}
