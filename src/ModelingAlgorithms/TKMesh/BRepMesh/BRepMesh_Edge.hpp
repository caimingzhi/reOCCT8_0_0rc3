#pragma once

#include <Standard.hpp>
#include <BRepMesh_DegreeOfFreedom.hpp>

#include <Standard.hpp>
#include <Standard_HashUtils.hpp>
#include <Standard_DefineAlloc.hpp>

class BRepMesh_OrientedEdge
{
public:
  DEFINE_STANDARD_ALLOC

  BRepMesh_OrientedEdge()
      : myFirstNode(-1),
        myLastNode(-1)
  {
  }

  BRepMesh_OrientedEdge(const int theFirstNode, const int theLastNode)
      : myFirstNode(theFirstNode),
        myLastNode(theLastNode)
  {
  }

  int FirstNode() const { return myFirstNode; }

  int LastNode() const { return myLastNode; }

  bool IsEqual(const BRepMesh_OrientedEdge& theOther) const
  {
    return (myFirstNode == theOther.myFirstNode && myLastNode == theOther.myLastNode);
  }

  bool operator==(const BRepMesh_OrientedEdge& Other) const { return IsEqual(Other); }

private:
  int myFirstNode;
  int myLastNode;
};

namespace std
{
  template <>
  struct hash<BRepMesh_OrientedEdge>
  {
    size_t operator()(const BRepMesh_OrientedEdge& theOrientedEdge) const noexcept
    {
      union Combination
      {
        unsigned short Arr[2];
        uint32_t       Hash;

      } aCombination;

      aCombination.Arr[0] = static_cast<unsigned short>(theOrientedEdge.FirstNode());
      aCombination.Arr[1] = static_cast<unsigned short>(theOrientedEdge.LastNode());
      return static_cast<size_t>(aCombination.Hash);
    }
  };
} // namespace std

#include <Standard_HashUtils.hpp>

class BRepMesh_Edge : public BRepMesh_OrientedEdge
{
public:
  BRepMesh_Edge()
      : myMovability(BRepMesh_Deleted)
  {
  }

  BRepMesh_Edge(const int                      theFirstNode,
                const int                      theLastNode,
                const BRepMesh_DegreeOfFreedom theMovability)
      : BRepMesh_OrientedEdge(theFirstNode, theLastNode),
        myMovability(theMovability)
  {
  }

  BRepMesh_DegreeOfFreedom Movability() const { return myMovability; }

  void SetMovability(const BRepMesh_DegreeOfFreedom theMovability) { myMovability = theMovability; }

  bool IsSameOrientation(const BRepMesh_Edge& theOther) const
  {
    return BRepMesh_OrientedEdge::IsEqual(theOther);
  }

  bool IsEqual(const BRepMesh_Edge& theOther) const
  {
    if (myMovability == BRepMesh_Deleted || theOther.myMovability == BRepMesh_Deleted)
      return false;

    return IsSameOrientation(theOther)
           || (FirstNode() == theOther.LastNode() && LastNode() == theOther.FirstNode());
  }

  bool operator==(const BRepMesh_Edge& Other) const { return IsEqual(Other); }

private:
  BRepMesh_DegreeOfFreedom myMovability;
};

namespace std
{
  template <>
  struct hash<BRepMesh_Edge>
  {
    size_t operator()(const BRepMesh_Edge& theEdge) const noexcept
    {
      union Combination
      {
        unsigned short Arr[2];
        uint32_t       Hash;

      } aCombination;

      aCombination.Arr[0] = static_cast<unsigned short>(theEdge.FirstNode());
      aCombination.Arr[1] = static_cast<unsigned short>(theEdge.LastNode());
      if (aCombination.Arr[0] > aCombination.Arr[1])
      {
        std::swap(aCombination.Arr[0], aCombination.Arr[1]);
      }
      return static_cast<size_t>(aCombination.Hash);
    }
  };
} // namespace std
