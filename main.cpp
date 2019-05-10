#include "process.h"
#include "frame.h"
#include "functions.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;


int main()
{
  vector<Process> processList;
  vector<Process> queueProcess;
  vector<Frame> memoryMap;
  string nameFile;
  int memSize=0, pageSize=0, numProcess=0,sumTurnAroundTime = 0, timeTrack =0;

  userInput(memSize,pageSize, nameFile);

  insertListProcess(nameFile, numProcess, processList);

  createMemoryMapList(memoryMap,pageSize, memSize);


  while(1)
  {
    processArrival(timeTrack,queueProcess,processList);
    updateMemoryMap(pageSize, timeTrack, memoryMap,processList);
    insertProcessToMemMap(pageSize, timeTrack, memoryMap, queueProcess,processList);
    timeTrack++;

      if (timeTrack > 10000 && queueProcess.size() == 0 )
      {
          break;
      }

  }

  for (size_t i = 0; i < processList.size(); i++)
  {
    sumTurnAroundTime += processList[i].getTurnAroundTime();
  }
  cout<< "\nAverage Turnaround Time: " <<fixed << setprecision(2) << (float) (sumTurnAroundTime/numProcess) <<endl;

    return 0;
}
