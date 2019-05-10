#include "process.h"
#include "frame.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;


int timePrevious = -1;


void printMemoryMap(vector <Frame> memoryMap, int pageSize)
{
  cout<<"\tMemory Map: "<<endl;
  bool inFreeFrameSection = false;
  int start;
    for (size_t i = 0; i < memoryMap.size(); i++)
    {

      if (!inFreeFrameSection && !memoryMap[i].isAssigned())
      {
            inFreeFrameSection = true;
            start = i;
        }
        else if (inFreeFrameSection && memoryMap[i].isAssigned())
        {
            inFreeFrameSection = false;
            cout<<"\t\t"<<start*pageSize<<" - "<<i*pageSize-1<<": Free frame(s)"<<endl;
        }

        if (memoryMap[i].isAssigned())
        {
            cout<<memoryMap[i];
        }
    }

    if (inFreeFrameSection) {

        cout<<"\t\t"<<start*pageSize<<" - "<<(memoryMap.size()*pageSize)-1<<": Free frame(s)"<<endl;

    }
}


void userInput(int & mem, int & page, string& nameFile)
{
  cout<<"\n**************************INPUT****************************"<<endl;

    while(1)
    {
            cin.clear();
            cout<<"Memory Size: ";
            cin>>mem;
            if (mem <= 0) {

            cerr<<"ERROR: You didn't enter valid input!"<<endl;

            continue;
            }

            cout<<"Page size (1: 100, 2: 200, 3: 400): ";
            cin>>page;
            if ( page < 1 || page > 3)
            {

                cerr<<"ERROR: You didn't enter an valid input!"<<endl;
                continue;
            }

        switch (page)
        {
        case 1: page = 100; break;
        case 2: page = 200; break;
        case 3: page = 400; break;
        }

        if (mem % page != 0)
        {
            printf("ERROR: Memory size must be a multiple of the page!");
            continue;
        }

        break;

    }

    while (1)
    {

        cin.clear();
        cin.ignore(1000, '\n');
        cout<<"Enter name file: ";
        getline(cin,nameFile);
        ifstream f(nameFile.c_str());

        if(!f.good())
        {
          cerr<<"ERROR: No exist file!"<<endl;
          continue;
        }

        break;

    }

cout<<"\n\n**************************OUTPUT****************************"<<endl;
}


// stores values processes in process array
void insertListProcess(string & nameFile, int & numProcess, vector<Process> & procList)
{

    int numMemReq,tmp, pid,arrival_time, life_time ;
    // int counter = 0;
    int totalMemReq;
    fstream inFile;

	  inFile.open(nameFile, ios::in);

    inFile>> numProcess;

    for (int i = 0; i < numProcess; i++) {

      inFile>>pid;
      inFile>>arrival_time;
      inFile>>life_time;
      inFile>>numMemReq;

      totalMemReq =0;
      for (int j = 0; j < numMemReq; j++) {
        inFile>>tmp;
        totalMemReq+=tmp;
      }

      Process process(pid,arrival_time,life_time,totalMemReq);
       procList.push_back(process);
    }

    inFile.close();



}


void createMemoryMapList(vector <Frame> & memoryMap, int & pageSize, int & memSize)
{
  int frame_start=0, frame_end = pageSize-1;
  int size = int (memSize/pageSize);
  for (int i = 0; i < size; i++) {
      Frame frame(frame_start,frame_end);
      memoryMap.push_back(frame);
      frame_start+= pageSize;
      frame_end+=pageSize;
  }

}


void printQueueProcess(vector <Process>  queueProcess)
{
  cout<<"\tInput Queue:[";
  if(queueProcess.size() != 0)
  {
    for (size_t i = 0; i < queueProcess.size(); i++) {
      cout<< queueProcess[i].getProcessId()<<" ";
    }
  }
  cout<<"]"<<endl;
}

void processArrival( int timeTrack, vector<Process> & queueProcess, vector<Process> processList)
{
    for (size_t i = 0; i < processList.size(); i++) {
      if(processList[i].isArrival(timeTrack))
      {
        if (timePrevious == timeTrack) {
          cout<<"\t";
        }
        else
        {
          timePrevious = timeTrack;
          cout<<"t = "<< timeTrack<<": ";
        }
        cout<<"Process "<< processList[i].getProcessId()<<" arrives"<<endl;
        queueProcess.push_back(processList[i]);
        printQueueProcess(queueProcess);

      }
    }
}




void updateMemoryMap(int pageSize, int timeTrack, vector <Frame> & memoryMap, vector<Process> & processList)
{
  for (size_t i = 0; i < processList.size(); i++)
  {
    if(processList[i].isFinishInMemory(timeTrack))
    {
      if (timePrevious == timeTrack) {
        cout<<"\t";
      }
      else
      {
        timePrevious = timeTrack;
        cout<<"t = "<< timeTrack<<": ";
      }
      cout <<"Process "<<processList[i].getProcessId()<<" completes"<<endl;
      for (size_t j = 0; j < memoryMap.size(); j++)
      {
          if(memoryMap[j].getProcessAssignId() == processList[i].getProcessId())
          {

            memoryMap[j].removeProcess();

          }
      }
      printMemoryMap(memoryMap,pageSize);
    }

  }
}


void removeProcessFromQueue(int processID,vector<Process> & queueProcess)
{
  for (size_t i = 0; i < queueProcess.size(); i++)
  {
      if(queueProcess[i].getProcessId() == processID)
      {

        queueProcess.erase (queueProcess.begin()+i);
        break;

      }
  }
}

void updateTimeProcess(int timeTrack, int id, vector<Process> & processList )
{

  for (size_t i = 0; i < processList.size(); i++)
  {

    if (processList[i].getProcessId()==id)
    {

      processList[i].setTimeAddToMen(timeTrack);
      break;

    }
  }
}

bool isEnoughFrame(int pageSize, Process p, vector<Frame> memoryMap) {
    int num_free_frames = 0;

    for (size_t i = 0; i < memoryMap.size(); i++)
    {
        if (!memoryMap[i].isAssigned())
        {
            num_free_frames += 1;
        }
    }

    // if the number of free frames * the page size is greater than the mem req
    // for the process in question we can fit it in.
    return (num_free_frames * pageSize) >= p.getMemRequest();
}

void insertProcessToMemMap(int pageSize, int timeTrack, vector <Frame> & memoryMap, vector<Process> & queueProcess,vector<Process> & processList)
{
  size_t size = queueProcess.size();
  for (size_t i = 0; i < size ; i++)
  {

      int id = queueProcess[i].getProcessId();
    if(isEnoughFrame(pageSize,queueProcess[i],memoryMap))
    {
        int pageNum = 1;

        int maxPage = queueProcess[i].getMemRequest();

        cout<<"\tMM moves Process "<<id<<" to memory"<<endl;
      for (size_t j = 0; j < memoryMap.size(); j++)
      {
        // if this frame is not assigned
        if (!memoryMap[j].isAssigned() && maxPage>0)
        {
            // assign it
            memoryMap[j].setAssign();
            // set the page number
            memoryMap[j].setPageNumber(pageNum);
            // set the proc num
            memoryMap[j].setProcessAssignId(id);

            pageNum++;
            maxPage-=pageSize;

        }

      }

      removeProcessFromQueue(id,queueProcess);
      updateTimeProcess(timeTrack ,id,processList);
      printQueueProcess(queueProcess);
      printMemoryMap(memoryMap,pageSize);
    }
  }

}
