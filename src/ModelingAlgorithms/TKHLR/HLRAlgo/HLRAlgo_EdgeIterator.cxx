#ifndef No_Exception
  #define No_Exception
#endif

#include <HLRAlgo_EdgeIterator.hpp>
#include <HLRAlgo_EdgeStatus.hpp>

//=================================================================================================

HLRAlgo_EdgeIterator::HLRAlgo_EdgeIterator()
    : myNbVis(0),
      myNbHid(0),
      EVis(nullptr),
      EHid(nullptr),
      iVis(0),
      iHid(0),
      myHidStart(0.0),
      myHidEnd(0.0),
      myHidTolStart(0.0),
      myHidTolEnd(0.0)
{
}

//=================================================================================================

void HLRAlgo_EdgeIterator::InitHidden(HLRAlgo_EdgeStatus& status)
{
  EHid = &status;
  iHid = 1;
  if (((HLRAlgo_EdgeStatus*)EHid)->AllHidden())
  {
    ((HLRAlgo_EdgeStatus*)EHid)->Bounds(myHidStart, myHidTolStart, myHidEnd, myHidTolEnd);
    myNbHid = 0;
  }
  else
  {
    myNbHid = ((HLRAlgo_EdgeStatus*)EHid)->NbVisiblePart();
    double B1;
    float  B2;
    ((HLRAlgo_EdgeStatus*)EHid)->Bounds(myHidStart, myHidTolStart, B1, B2);
    ((HLRAlgo_EdgeStatus*)EHid)->VisiblePart(iHid, myHidEnd, myHidTolEnd, B1, B2);
  }
  if (myHidStart + myHidTolStart >= myHidEnd - myHidTolEnd
      && myHidEnd + myHidTolEnd >= myHidStart - myHidTolStart)
    NextHidden();
}

//=================================================================================================

void HLRAlgo_EdgeIterator::NextHidden()
{
  if (iHid >= myNbHid + 1)
    iHid++;
  else
  {
    double B1;
    float  B2;
    ((HLRAlgo_EdgeStatus*)EHid)->VisiblePart(iHid, B1, B2, myHidStart, myHidTolStart);
    iHid++;
    if (iHid == myNbHid + 1)
    {
      ((HLRAlgo_EdgeStatus*)EHid)->Bounds(B1, B2, myHidEnd, myHidTolEnd);
      if (myHidStart + myHidTolStart >= myHidEnd - myHidTolEnd
          && myHidEnd + myHidTolEnd >= myHidStart - myHidTolStart)
        iHid++;
    }
    else
      ((HLRAlgo_EdgeStatus*)EHid)->VisiblePart(iHid, myHidEnd, myHidTolEnd, B1, B2);
  }
}
