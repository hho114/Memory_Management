#include <string>
#include "process.h"
using namespace std;
#pragma once



class Frame
{
public:

  friend ostream & operator<<(ostream& os, Frame & f)
  {
      return os <<"\t\t"<< f.mStart<<" - "<<f.mEnd <<": Process "<<f.mProcessAssignId<<", Page "<<f.mPageNumber<< endl;
  }


  Frame( int frame_start, int frame_end)
  {

    mStart = frame_start;
    mEnd = frame_end;
    mProcessAssignId =0;
    mPageNumber = 0;
    mIsAssigned = false;
  }

  Frame & operator= (const Frame & f)
  {
      // do the copy

      mStart = f.mStart;
      mEnd = f.mEnd;
      mProcessAssignId = f.mProcessAssignId;
      mPageNumber = f.mPageNumber;

      // return the existing object so we can chain this operator
      return *this;
  }
  void removeProcess()
  {
    mProcessAssignId = 0;
    mPageNumber =0;
    mIsAssigned = false;
  }

  void setAssign()
  {
    mIsAssigned = true;
  }

  void setPageNumber(int page_num)
  {
    mPageNumber = page_num;
  }

  void setProcessAssignId(int id)
  {
    mProcessAssignId = id;
  }

  int getProcessAssignId()const
  {
    return mProcessAssignId;
  }
  bool isAssigned() const
  {
    return mIsAssigned;
  }
  int getStart()const
  {
    return mStart;
  }
  int getEnd()const
  {
    return mEnd;
  }

private:

  int mStart;
  int mEnd;
  int mProcessAssignId;
  int mPageNumber;
  bool mIsAssigned;

};
