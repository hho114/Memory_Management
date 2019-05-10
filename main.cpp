#include "process.h"
#include "frame.h"
#include "functions.h"
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;


int main()
{
  vector<Process> processList;
  vector<Process> queueProcess;
  vector<Frame> memoryMap;
  string nameFile;
  int memSize=0, pageSize=0, numProcess=0, timeTrack =0;

  userInput(memSize,pageSize, nameFile);

  insertListProcess(nameFile, numProcess, processList);

  createMemoryMapList(memoryMap,pageSize, memSize);


  do
  {
    processArrival(timeTrack,queueProcess,processList);
    updateMemoryMap(pageSize, timeTrack, memoryMap,processList);
    insertProcessToMemMap(pageSize, timeTrack, memoryMap, queueProcess,processList);
    timeTrack++;

  }while(!(timeTrack > 10000 && queueProcess.size() == 0));


  calculateAverageTurnAround(processList);

  return 0;
}
