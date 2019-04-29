
#pragma once
#include <iostream>
#include <queue>
#include <fstream>
#include <vector>
using namespace std;

struct BMemory
{
  int start;
  int end;
  int process_number;
  int page_number;
  int total_size;
  int release_time;
  bool available;
};


class Process
{


public:

  friend ostream& operator<<(ostream& os, Process const & p ) {
      return
        cout << "\nProcess id: " << id << endl;
        cout << "Process Time Start: " << arrival_time << endl;
        cout << "Process Time End: " << end_at << endl;
        cout << "Process Time Life: " << life_time << endl;
        cout << "Total Memory: " << tot_memory << endl;
	      cout << "Turnaround Time: " << turn_around << endl;
    }





  void bool operator < (const Process & process) const
  {
    return arrival_time < process.arrival_time;
  }



private:

  int id;
  int mem_block_count;
  int tot_memory;
  int turn_around;
  int arrival_time;
  int end_at;
  int life_time;
  vector <int> memmory_block;


};
