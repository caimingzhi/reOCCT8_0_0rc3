#pragma once


#include <BVH_PrimitiveSet.hpp>

//! Implements easy to use interfaces for adding the elements into
//! BVH tree and its following construction.
//! To make it more effective it is better to set the number of elements
//! that are going to be added into BVH tree.
//! For better efficiency on heavy data types it is recommended to use
//! either BHV_IndexedBoxSet which uses indirect indexing for accessing
//! the elements and their boxes or set the element to be an index
//! of the real element in the application's internal data structures.
//!
//! \tparam NumType Numeric data type
//! \tparam Dimension Vector dimension
//! \tparam DataType Type of elements on which the boxes are built
template <class NumType, int Dimension, class DataType = int>
class BVH_BoxSet : public BVH_PrimitiveSet<NumType, Dimension>
{
public: //! @name Constructors
  //! Empty constructor for use the default BVH_Builder
  BVH_BoxSet()
      : BVH_PrimitiveSet<NumType, Dimension>()
  {
  }

  //! Constructor for usage the custom BVH builder
  BVH_BoxSet(const opencascade::handle<BVH_Builder<NumType, Dimension>>& theBuilder)
      : BVH_PrimitiveSet<NumType, Dimension>(theBuilder)
  {
  }

public: //! @name Setting expected size of the BVH
  //! Sets the expected size of BVH tree
  virtual void SetSize(const size_t theSize)
  {
    myElements.reserve(theSize);
    myBoxes.reserve(theSize);
  }

public: //! @name Adding elements in BVH
  //! Adds the element into BVH
  virtual void Add(const DataType& theElement, const BVH_Box<NumType, Dimension>& theBox)
  {
    myElements.push_back(theElement);
    myBoxes.push_back(theBox);
    BVH_Object<NumType, Dimension>::myIsDirty = true;
  }

public: //! @name BVH construction
  //! BVH construction
  void Build() { BVH_PrimitiveSet<NumType, Dimension>::Update(); }

public: //! @name Clearing the elements and boxes
  //! Clears the vectors of elements and boxes
  virtual void Clear()
  {
    myElements.clear();
    myBoxes.clear();
    BVH_Object<NumType, Dimension>::myIsDirty = true;
  }

public: //! @name Necessary overrides for BVH construction
  //! Make inherited method Box() visible to avoid CLang warning
  using BVH_PrimitiveSet<NumType, Dimension>::Box;

  //! Returns the bounding box with the given index.
  BVH_Box<NumType, Dimension> Box(const int theIndex) const override { return myBoxes[theIndex]; }

  //! Returns centroid position along specified axis.
  double Center(const int theIndex, const int theAxis) const override
  {
    return Box(theIndex).Center(theAxis);
  }

  //! Returns the number of boxes.
  int Size() const override { return static_cast<int>(myBoxes.size()); }

  //! Swaps indices of two specified boxes.
  void Swap(const int theIndex1, const int theIndex2) override
  {
    std::swap(myElements[theIndex1], myElements[theIndex2]);
    std::swap(myBoxes[theIndex1], myBoxes[theIndex2]);
  }

  //! Returns the Element with the index theIndex.
  virtual DataType Element(const int theIndex) const { return myElements[theIndex]; }

protected:                                             //! @name Fields
  std::vector<DataType>                    myElements; //!< Elements
  std::vector<BVH_Box<NumType, Dimension>> myBoxes;    //!< Boxes for the elements
};

