#pragma once

#include <BVH_Set.hpp>

//! Tool object to sort abstract primitive set.
template <class T, int N>
class BVH_Sorter
{
public:
  //! Performs default initialization.
  BVH_Sorter()
      : myIsParallel(false)
  {
  }

  //! Releases resources of BVH sorter.
  virtual ~BVH_Sorter() = default;

  //! Sorts the set.
  virtual void Perform(BVH_Set<T, N>* theSet) = 0;

  //! Sorts the given (inclusive) range in the set.
  virtual void Perform(BVH_Set<T, N>* theSet, const int theStart, const int theFinal) = 0;

  //! Returns parallel flag.
  inline bool IsParallel() const { return myIsParallel; }

  //! Set parallel flag controlling possibility of parallel execution.
  inline void SetParallel(const bool isParallel) { myIsParallel = isParallel; }

private:
  bool myIsParallel;
};
