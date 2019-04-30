#include "Process.h"
#include "Memory.h"
#include <iostream>
#include <queue>
using namespace std;


Process * list_process;
queue <Process> queue_process;
frame_list* framelist;
int number_of_procs = 0;
int termination = -1;

int main()
{
  int page_size  = 0;
 int mem_size   = 0;

}
