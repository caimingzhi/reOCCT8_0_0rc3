#pragma once

#include <Standard_OutOfRange.hpp>

//! This class represents a pair of integer indices to store
//! element indices connected to link. It is restricted to
//! store more than two indices in it.
class BRepMesh_PairOfIndex
{
public:
  //! Default constructor
  BRepMesh_PairOfIndex() { Clear(); }

  //! Clears indices.
  void Clear() { myIndex[0] = myIndex[1] = -1; }

  //! Appends index to the pair.
  void Append(const int theIndex)
  {
    if (myIndex[0] < 0)
      myIndex[0] = theIndex;
    else
    {
      if (myIndex[1] >= 0)
        throw Standard_OutOfRange("BRepMesh_PairOfIndex::Append, more than two index to store");

      myIndex[1] = theIndex;
    }
  }

  //! Prepends index to the pair.
  void Prepend(const int theIndex)
  {
    if (myIndex[1] >= 0)
      throw Standard_OutOfRange("BRepMesh_PairOfIndex::Prepend, more than two index to store");

    myIndex[1] = myIndex[0];
    myIndex[0] = theIndex;
  }

  //! Returns is pair is empty.
  bool IsEmpty() const
  {
    // Check only first index. It is impossible to update
    // second index if the first one is empty.
    return (myIndex[0] < 0);
  }

  //! Returns number of initialized indices.
  int Extent() const { return (myIndex[0] < 0 ? 0 : (myIndex[1] < 0 ? 1 : 2)); }

  //! Returns first index of pair.
  int FirstIndex() const { return myIndex[0]; }

  //! Returns last index of pair
  int LastIndex() const { return (myIndex[1] < 0 ? myIndex[0] : myIndex[1]); }

  //! Returns index corresponding to the given position in the pair.
  //! @param thePairPos position of index in the pair (1 or 2).
  int Index(const int thePairPos) const
  {
    if (thePairPos != 1 && thePairPos != 2)
      throw Standard_OutOfRange("BRepMesh_PairOfIndex::Index, requested index is out of range");

    return myIndex[thePairPos - 1];
  }

  //! Sets index corresponding to the given position in the pair.
  //! @param thePairPos position of index in the pair (1 or 2).
  //! @param theIndex index to be stored.
  void SetIndex(const int thePairPos, const int theIndex)
  {
    if (thePairPos != 1 && thePairPos != 2)
      throw Standard_OutOfRange("BRepMesh_PairOfIndex::SetIndex, requested index is out of range");

    myIndex[thePairPos - 1] = theIndex;
  }

  //! Remove index from the given position.
  //! @param thePairPos position of index in the pair (1 or 2).
  void RemoveIndex(const int thePairPos)
  {
    if (thePairPos != 1 && thePairPos != 2)
      throw Standard_OutOfRange(
        "BRepMesh_PairOfIndex::RemoveIndex, requested index is out of range");

    if (thePairPos == 1)
      myIndex[0] = myIndex[1];

    myIndex[1] = -1;
  }

private:
  int myIndex[2];
};
