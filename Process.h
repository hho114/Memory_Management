
#pragma once
#include <iostream>
#include <queue>
#include <fstream>
#include <vector>


using namespace std;


class Process
{
public:

  Process(){}

  bool operator < (const Process & process) const
  {
    
  }

private:

  int id;
  int mem_block_count;
  int tot_memory;
  int turn_around;
  int start_at;
  int end_at;
  int life_time;
  vector <int> memmory_block;


};
