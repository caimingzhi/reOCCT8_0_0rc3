#pragma once

#include <BVH_PrimitiveSet.hpp>

template <class NumType, int Dimension, class DataType = int>
class BVH_BoxSet : public BVH_PrimitiveSet<NumType, Dimension>
{
public:
  BVH_BoxSet()
      : BVH_PrimitiveSet<NumType, Dimension>()
  {
  }

  BVH_BoxSet(const opencascade::handle<BVH_Builder<NumType, Dimension>>& theBuilder)
      : BVH_PrimitiveSet<NumType, Dimension>(theBuilder)
  {
  }

public:
  virtual void SetSize(const size_t theSize)
  {
    myElements.reserve(theSize);
    myBoxes.reserve(theSize);
  }

public:
  virtual void Add(const DataType& theElement, const BVH_Box<NumType, Dimension>& theBox)
  {
    myElements.push_back(theElement);
    myBoxes.push_back(theBox);
    BVH_Object<NumType, Dimension>::myIsDirty = true;
  }

public:
  void Build() { BVH_PrimitiveSet<NumType, Dimension>::Update(); }

public:
  virtual void Clear()
  {
    myElements.clear();
    myBoxes.clear();
    BVH_Object<NumType, Dimension>::myIsDirty = true;
  }

public:
  using BVH_PrimitiveSet<NumType, Dimension>::Box;

  BVH_Box<NumType, Dimension> Box(const int theIndex) const override { return myBoxes[theIndex]; }

  double Center(const int theIndex, const int theAxis) const override
  {
    return Box(theIndex).Center(theAxis);
  }

  int Size() const override { return static_cast<int>(myBoxes.size()); }

  void Swap(const int theIndex1, const int theIndex2) override
  {
    std::swap(myElements[theIndex1], myElements[theIndex2]);
    std::swap(myBoxes[theIndex1], myBoxes[theIndex2]);
  }

  virtual DataType Element(const int theIndex) const { return myElements[theIndex]; }

protected:
  std::vector<DataType>                    myElements;
  std::vector<BVH_Box<NumType, Dimension>> myBoxes;
};
