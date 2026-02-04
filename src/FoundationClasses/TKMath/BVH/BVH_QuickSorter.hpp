#pragma once


#include <BVH_Sorter.hpp>
#include <NCollection_Allocator.hpp>

#include <algorithm>
#include <vector>

//! Performs centroid-based sorting of abstract set along
//! the given axis (X - 0, Y - 1, Z - 2) using std::sort.
//! Uses introsort algorithm which guarantees O(n log n) complexity.
template <class T, int N>
class BVH_QuickSorter : public BVH_Sorter<T, N>
{
public:
  //! Creates new BVH quick sorter for the given axis.
  BVH_QuickSorter(const int theAxis = 0)
      : myAxis(theAxis)
  {
  }

  //! Sorts the set.
  void Perform(BVH_Set<T, N>* theSet) override { Perform(theSet, 0, theSet->Size() - 1); }

  //! Sorts the given (inclusive) range in the set.
  void Perform(BVH_Set<T, N>* theSet, const int theStart, const int theFinal) override
  {
    const int aSize = theFinal - theStart + 1;
    if (aSize <= 1)
    {
      return;
    }

    // Create index array for sorting with OCCT allocator
    std::vector<int, NCollection_Allocator<int>> anIndices(aSize);
    for (int i = 0; i < aSize; ++i)
    {
      anIndices[i] = i;
    }

    // Sort indices by center value using std::sort (introsort - O(n log n) guaranteed)
    const int anAxis = myAxis;
    std::sort(anIndices.begin(), anIndices.end(), [theSet, theStart, anAxis](int a, int b) {
      return theSet->Center(theStart + a, anAxis) < theSet->Center(theStart + b, anAxis);
    });

    // Compute inverse permutation: invPerm[i] = where element i should go
    std::vector<int, NCollection_Allocator<int>> anInvPerm(aSize);
    for (int i = 0; i < aSize; ++i)
    {
      anInvPerm[anIndices[i]] = i;
    }

    // Apply permutation using cycle-based algorithm - O(n) swaps total
    for (int i = 0; i < aSize; ++i)
    {
      // Follow the cycle starting at position i
      while (anInvPerm[i] != i)
      {
        int j = anInvPerm[i];
        theSet->Swap(theStart + i, theStart + j);
        std::swap(anInvPerm[i], anInvPerm[j]);
      }
    }
  }

protected:
  //! Axis used to arrange the primitives (X - 0, Y - 1, Z - 2).
  int myAxis;
};

