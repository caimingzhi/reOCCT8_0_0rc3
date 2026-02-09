#pragma once

#include <Standard_OutOfRange.hpp>

class BRepMesh_PairOfIndex
{
public:
  BRepMesh_PairOfIndex() { Clear(); }

  void Clear() { myIndex[0] = myIndex[1] = -1; }

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

  void Prepend(const int theIndex)
  {
    if (myIndex[1] >= 0)
      throw Standard_OutOfRange("BRepMesh_PairOfIndex::Prepend, more than two index to store");

    myIndex[1] = myIndex[0];
    myIndex[0] = theIndex;
  }

  bool IsEmpty() const { return (myIndex[0] < 0); }

  int Extent() const { return (myIndex[0] < 0 ? 0 : (myIndex[1] < 0 ? 1 : 2)); }

  int FirstIndex() const { return myIndex[0]; }

  int LastIndex() const { return (myIndex[1] < 0 ? myIndex[0] : myIndex[1]); }

  int Index(const int thePairPos) const
  {
    if (thePairPos != 1 && thePairPos != 2)
      throw Standard_OutOfRange("BRepMesh_PairOfIndex::Index, requested index is out of range");

    return myIndex[thePairPos - 1];
  }

  void SetIndex(const int thePairPos, const int theIndex)
  {
    if (thePairPos != 1 && thePairPos != 2)
      throw Standard_OutOfRange("BRepMesh_PairOfIndex::SetIndex, requested index is out of range");

    myIndex[thePairPos - 1] = theIndex;
  }

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
