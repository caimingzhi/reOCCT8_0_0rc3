#pragma once

#include <BVH_BoxSet.hpp>

template <class NumType, int Dimension, class DataType = int>
class BVH_IndexedBoxSet : public BVH_BoxSet<NumType, Dimension, DataType>
{
public:
  BVH_IndexedBoxSet()
      : BVH_BoxSet<NumType, Dimension, DataType>()
  {
  }

  BVH_IndexedBoxSet(const opencascade::handle<BVH_Builder<NumType, Dimension>>& theBuilder)
      : BVH_BoxSet<NumType, Dimension, DataType>(theBuilder)
  {
  }

public:
  void SetSize(const size_t theSize) override
  {
    myIndices.reserve(theSize);
    BVH_BoxSet<NumType, Dimension, DataType>::SetSize(theSize);
  }

public:
  void Add(const DataType& theElement, const BVH_Box<NumType, Dimension>& theBox) override
  {
    myIndices.push_back(static_cast<int>(myIndices.size()));
    BVH_BoxSet<NumType, Dimension, DataType>::Add(theElement, theBox);
  }

public:
  void Clear() override
  {
    myIndices.clear();
    BVH_BoxSet<NumType, Dimension, DataType>::Clear();
  }

public:
  using BVH_BoxSet<NumType, Dimension, DataType>::Box;

  BVH_Box<NumType, Dimension> Box(const int theIndex) const override
  {
    return this->myBoxes[myIndices[theIndex]];
  }

  void Swap(const int theIndex1, const int theIndex2) override
  {
    std::swap(myIndices[theIndex1], myIndices[theIndex2]);
  }

  DataType Element(const int theIndex) const override
  {
    return this->myElements[myIndices[theIndex]];
  }

protected:
  std::vector<int> myIndices;
};
