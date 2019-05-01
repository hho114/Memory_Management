#include "process.h"
#include "memory.h"
#include <queue>
using namespace std;


void userInput(int & mem, int & page, char & nameFile)
{
    char buf[10];
    bool invalid = true;

    do
    {

        do {
            printf("Memory size: ");
            sscanf(buf, "%d", &mem);
            if ( mem <= 0)
            {
                clear_stdin(buf);
                printf("ERROR: You didn't enter a number!\n");
                invalid = true;
            }
            else
            {
              invalid = false;
            }
          } while(invalid);



            do {
                printf("Page size (1: 100, 2: 200, 3: 400): ");
                sscanf(buf, "%d", &page);
                if ( page < 1 && page > 3)
                {
                    clear_stdin(buf);
                    printf("ERROR: You didn't enter a number!\n");
                    invalid = true;
                }
                else
                {
                  invalid = false;
                }

              } while(invalid);

        switch (page)
        {
        case 1: page = 100; break;
        case 2: page = 200; break;
        case 3: page = 400; break;
        }

        if ((mem) % (page) == 0)
        {
            invalid = true;
            printf("ERROR: Memory size must be a multiple of the page!");
            printf(" %d is not a multiple of %d, please retry.\n", *mem, *page);
        }

    }while(invalid);

  do {
      printf("Input file: ");
      sscanf(buf, "%s", nameFile);

      if (!(ifile = fopen(nameFile, "r")))
      {
            perror("ERROR: Could not open file!\n");
            invalid = true;
      }
      else
      {
            invalid = false;
      }

    } while(invalid);

}



// stores values processes in process array
process * insertListProcess(const char & fileName, int & numProcess)
{
  if (!filePtr)
  {
      printf("ERROR: Failed to open file %s", file_path);
      exit(1);
  }

    process * procList;
    int numSpace,tmp;
    int counter = 0;
    int totalSpace =0;
    FILE * filePtr = fopen(file_path, "r");


    fscanf(filePtr, "%d", &numProcess);

    while (!feof(filePtr) && counter < numProcess)
    {
        // store values for processes
        fscanf(filePtr, "%d %d %d %d",
               &(procList[counter].pid),
               &(procList[counter].arrival_time),
               &(procList[counter].life_time),
               &numSpace);

        // get total memory requirements for process
        for (int i = 0; i < numSpace; i++)
        {
            fscanf(filePtr, "%d", &tmp);
            totalSpace += tmp;
        }

        procList[counter].mem_reqs = totalSpace;
        procList[counter].is_active = 0;
        procList[counter].time_added_to_memory = -1;
        procList[counter].time_finished = -1;

        counter++;
    }

    fclose(filePtr);

    return procList;
}

void insertNewProcessToQueue(int & currentTime, process * listProcess,
  frameList * fList, int & numProcess, queue<process> & queueProcess, int & queueSize)
{

    process * p;

    for (int i = 0; i < numProcess; i++)
    {
        p = &listProcess[i];

        if (p->arrival_time == currentTime) {
            printf("Process %d arrives\n",p->pid);

            queueProcess.push(p);
            queueSize++;

            printQueueStatus(queueProcess);
            printfList(fList);
        }
    }
}



void printQueueStatus(queue <process> queueProcess) {


    process * p;

    printf("\tInput queue: [ ");
    for (int i = 0; i < queueProcess.size(); i++)
    {
        p = &queueProcess.front();
        queueProcess.pop();
        printf("%d ", p->pid);


    }
    printf("]\n");
}

void terminateCompleteProcess(const int & currentTime, int & numProcess, process * listProcess, frameList * fList)
{
    int  timeInMem;
    process * p;

    // dequeue any procs that need it
    for (int i = 0; i < numProcess; i++)
    {
        p = &listProcess[i];
        timeInMem = currentTime - p->time_added_to_memory;

        if (p->is_active && (timeInMem >= p->life_time))
        {
            printf("%sProcess %d completes\n",p->pid);

            p->is_active = 0;
            p->time_finished = currentTime;

            freeMemory(fList, p->pid);

            printfList(fList);
        }
    }
}


void assignAvailableMemForWaitingProcess(const int & currentTime,queue<process> & queueProcess, int & queueSize, frameList * fList)
{

    process * p;
    int dequeueCounter = 0;
    // dequeue any procs that can be put into mem
    for (int i = 0; i < queueSize; i++)
    {

        p = queueProcess.pop();

        if (isEnoughMemoryForProcess(fList, p))
        {
          printf("%sMM moves Process %d to memory\n", proc->pid);

          putProcessIntoMemory(fList, p);

          p->is_active = 1;
          p->time_added_to_memory = currentTime;

          dequeueCounter++;
          printQueueStatus(queueProcess);
          printFrameList(fList);
        }
        else
        {
          queueProcess.push(p);
        }
    }

    queueSize-=dequeueCounter;
}
