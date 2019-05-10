#include <iostream>
using namespace std;
#pragma once


class Process
{
  public:

  friend ostream & operator<<(ostream& os, Process & p)
  {
      return os <<"Process ID: "<< p.mProcessId << endl
                <<"Arrive Time: "<<p.mArrivalTime<<endl
                <<"Life Time: "<<p.mLifeTime<<endl
                <<"Memory Request: "<<p.mMemRequest<<endl;
  }

  Process(int id, int arrival_time, int life_time, int mem_reqs)
  {
    mProcessId = id;
    mArrivalTime = arrival_time;
    mLifeTime = life_time;
    mMemRequest = mem_reqs;
    mTimeAddToMem = -1;
    mTurnAroundTime = -1;
    mIsActive = false;
  }


  bool isFinishInMemory(int timeTrack)
  {
    if (mLifeTime == (timeTrack - mTimeAddToMem) && mIsActive)
    {
      mIsActive = false;
      setTurnAroundTime(timeTrack);
      return true;

    }
      return false;
  }


  Process & operator= (const Process &p)
  {
      // do the copy
      mProcessId = p.mProcessId;
      mArrivalTime = p.mArrivalTime;
      mLifeTime = p.mLifeTime;
      mMemRequest = p.mMemRequest;

      // return the existing object so we can chain this operator
      return *this;
  }

  bool isArrival(int timeTrack) const
  {
      return timeTrack == mArrivalTime;
  }

  int getProcessId() const
  {
    return mProcessId;
  }

  int getMemRequest()const
  {
    return mMemRequest;
  }
  int getTimeAddTomen() const
  {
    return mTimeAddToMem;
  }
  int getTurnAroundTime()const
  {
    return mTurnAroundTime;
  }
  void setTurnAroundTime(int timeTrack)
  {
    mTurnAroundTime = timeTrack - mArrivalTime;
  }
  void setTimeAddToMen(int timeTrack)
  {
    mTimeAddToMem = timeTrack;
    mIsActive = true;
  }
  void setActive()
  {
    mIsActive = true;
  }
  int getLifeTime()const
  {
    return mLifeTime;
  }

  private:
    int mProcessId;
    int mArrivalTime;
    int mLifeTime;
    int mMemRequest;
    int mTimeAddToMem;
    bool mIsActive;
    int mTurnAroundTime;

};
