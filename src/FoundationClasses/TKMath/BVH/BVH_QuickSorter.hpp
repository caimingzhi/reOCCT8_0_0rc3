#pragma once

#include <BVH_Sorter.hpp>
#include <NCollection_Allocator.hpp>

#include <algorithm>
#include <vector>

template <class T, int N>
class BVH_QuickSorter : public BVH_Sorter<T, N>
{
public:
  BVH_QuickSorter(const int theAxis = 0)
      : myAxis(theAxis)
  {
  }

  void Perform(BVH_Set<T, N>* theSet) override { Perform(theSet, 0, theSet->Size() - 1); }

  void Perform(BVH_Set<T, N>* theSet, const int theStart, const int theFinal) override
  {
    const int aSize = theFinal - theStart + 1;
    if (aSize <= 1)
    {
      return;
    }

    std::vector<int, NCollection_Allocator<int>> anIndices(aSize);
    for (int i = 0; i < aSize; ++i)
    {
      anIndices[i] = i;
    }

    const int anAxis = myAxis;
    std::sort(
      anIndices.begin(),
      anIndices.end(),
      [theSet, theStart, anAxis](int a, int b)
      { return theSet->Center(theStart + a, anAxis) < theSet->Center(theStart + b, anAxis); });

    std::vector<int, NCollection_Allocator<int>> anInvPerm(aSize);
    for (int i = 0; i < aSize; ++i)
    {
      anInvPerm[anIndices[i]] = i;
    }

    for (int i = 0; i < aSize; ++i)
    {

      while (anInvPerm[i] != i)
      {
        int j = anInvPerm[i];
        theSet->Swap(theStart + i, theStart + j);
        std::swap(anInvPerm[i], anInvPerm[j]);
      }
    }
  }

protected:
  int myAxis;
};
