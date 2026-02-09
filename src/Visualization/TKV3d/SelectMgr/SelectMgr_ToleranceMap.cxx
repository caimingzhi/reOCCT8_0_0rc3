

#include <SelectMgr_ToleranceMap.hpp>

SelectMgr_ToleranceMap::SelectMgr_ToleranceMap()
    : myLargestKey(-1),
      myCustomTolerance(-1)
{
}

SelectMgr_ToleranceMap::~SelectMgr_ToleranceMap()
{
  myTolerances.Clear();
}

void SelectMgr_ToleranceMap::Add(const int& theTolerance)
{
  if (int* aFreq = myTolerances.ChangeSeek(theTolerance))
  {
    ++(*aFreq);
    if (*aFreq == 1 && theTolerance != myLargestKey)
    {
      myLargestKey = std::max(theTolerance, myLargestKey);
    }
    return;
  }

  myTolerances.Bind(theTolerance, 1);
  if (myTolerances.Extent() == 1)
  {
    myLargestKey = theTolerance;
  }
  else
  {
    myLargestKey = std::max(theTolerance, myLargestKey);
  }
}

void SelectMgr_ToleranceMap::Decrement(const int& theTolerance)
{
  int* aFreq = myTolerances.ChangeSeek(theTolerance);
  if (aFreq == nullptr)
  {
    return;
  }

  Standard_ProgramError_Raise_if(*aFreq == 0,
                                 "SelectMgr_ToleranceMap::Decrement() - internal error");
  --(*aFreq);

  if (theTolerance == myLargestKey && *aFreq == 0)
  {
    myLargestKey = -1;
    for (NCollection_DataMap<int, int>::Iterator anIter(myTolerances); anIter.More(); anIter.Next())
    {
      if (anIter.Value() != 0)
      {
        myLargestKey = std::max(myLargestKey, anIter.Key());
      }
    }
  }
}
