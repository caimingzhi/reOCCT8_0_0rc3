#pragma once

#include <BVH_Set.hpp>

template <class T, int N>
class BVH_Sorter
{
public:
  BVH_Sorter()
      : myIsParallel(false)
  {
  }

  virtual ~BVH_Sorter() = default;

  virtual void Perform(BVH_Set<T, N>* theSet) = 0;

  virtual void Perform(BVH_Set<T, N>* theSet, const int theStart, const int theFinal) = 0;

  inline bool IsParallel() const { return myIsParallel; }

  inline void SetParallel(const bool isParallel) { myIsParallel = isParallel; }

private:
  bool myIsParallel;
};
