#include "process.h"
#include "memory.h"
#include "functions.h"
#include <iostream>
#include <queue>
using namespace std;





int main()
{

  int currentTime=0;
  process * listProcess;
  queue <process> queueProcess;
  frameList * fList;

  int pageSize=0, memSize=0, queueSize=0, numProcess=0, turnAroundTime=0;
  char namefile[10];
  userInput(memSize,pageSize,nameFile);
  listProcess = insertListProcess(nameFile);

  fList = createFameList(memSize/pageSize, pageSize);




  while(1)
  {

    insertNewProcessToQueue(currentTime,listProcess,fList,numProcess,queueProcess, queueSize);
    terminateCompleteProcess(currentTime,numProcess,listProcess,fList);
    assignAvailableMemForWaitingProcess( currentTime, queueProcess, queueSize, fList);
    currentTime++;
    if (currentTime > TIME_MAX)
    {
        printf("DEADLOCK: max time reached\n");
        break;
    }

    if (queue->size == 0 && isfListEmpty(fList))
    {
        break;
    }

  }


  //print Average turnAroundTime
    for (int i = 0; i < numProcess; i++) {
         turnAroundTime += listProcess[i].time_finished - listProcess[i].arrival_time;
    }
    printf("Average Turnaround Time: %2.2f\n", total / numProcess);


    return 0;
}
