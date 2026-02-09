#pragma once

#include <BVH_Box.hpp>

template <class T, int N>
class BVH_Set
{
public:
  typedef BVH_Box<T, N> BVH_BoxNt;

public:
  BVH_Set() = default;

  virtual ~BVH_Set() = default;

  virtual BVH_Box<T, N> Box() const
  {
    BVH_Box<T, N> aBox;
    const int     aSize = Size();
    for (int anIndex = 0; anIndex < aSize; ++anIndex)
    {
      aBox.Combine(Box(anIndex));
    }
    return aBox;
  }

public:
  virtual int Size() const = 0;

  virtual BVH_Box<T, N> Box(const int theIndex) const = 0;

  virtual T Center(const int theIndex, const int theAxis) const = 0;

  virtual void Swap(const int theIndex1, const int theIndex2) = 0;
};
