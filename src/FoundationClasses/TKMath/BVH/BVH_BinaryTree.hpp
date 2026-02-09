#pragma once

#ifndef _BVH_QuadTree_Header
  #define _BVH_QuadTree_Header

  #include <BVH_Tree.hpp>

template <class T, int N>
class BVH_Tree<T, N, BVH_QuadTree> : public BVH_TreeBase<T, N>
{
public:
  BVH_Tree()
      : BVH_TreeBase<T, N>()
  {
  }

  template <int K>
  int Child(const int theNodeIndex) const
  {
    return BVH::Array<int, 4>::Value(this->myNodeInfoBuffer, theNodeIndex).y() + K;
  }
};

#endif

#include <deque>
#include <tuple>

template <class T, int N>
class BVH_Tree<T, N, BVH_BinaryTree> : public BVH_TreeBase<T, N>
{
public:
  typedef typename BVH_TreeBase<T, N>::BVH_VecNt BVH_VecNt;

public:
  BVH_Tree()
      : BVH_TreeBase<T, N>()
  {
  }

  void SetOuter(const int theNodeIndex)
  {
    BVH::Array<int, 4>::ChangeValue(this->myNodeInfoBuffer, theNodeIndex).x() = 1;
  }

  void SetInner(const int theNodeIndex)
  {
    BVH::Array<int, 4>::ChangeValue(this->myNodeInfoBuffer, theNodeIndex).x() = 0;
  }

  template <int K>
  int Child(const int theNodeIndex) const
  {
    return BVH::Array<int, 4>::Value(this->myNodeInfoBuffer, theNodeIndex)[K + 1];
  }

  template <int K>
  int& ChangeChild(const int theNodeIndex)
  {
    return BVH::Array<int, 4>::ChangeValue(this->myNodeInfoBuffer, theNodeIndex)[K + 1];
  }

  template <int K>
  int& Child(const int theNodeIndex)
  {
    return BVH::Array<int, 4>::ChangeValue(this->myNodeInfoBuffer, theNodeIndex)[K + 1];
  }

public:
  void Clear()
  {
    this->myDepth = 0;
    BVH::Array<T, N>::Clear(this->myMinPointBuffer);
    BVH::Array<T, N>::Clear(this->myMaxPointBuffer);
    BVH::Array<int, 4>::Clear(this->myNodeInfoBuffer);
  }

  void Reserve(const int theNbNodes)
  {
    BVH::Array<T, N>::Reserve(this->myMinPointBuffer, theNbNodes);
    BVH::Array<T, N>::Reserve(this->myMaxPointBuffer, theNbNodes);
    BVH::Array<int, 4>::Reserve(this->myNodeInfoBuffer, theNbNodes);
  }

  int AddLeafNode(const BVH_VecNt& theMinPoint,
                  const BVH_VecNt& theMaxPoint,
                  const int        theBegElem,
                  const int        theEndElem)
  {
    BVH::Array<T, N>::Append(this->myMinPointBuffer, theMinPoint);
    BVH::Array<T, N>::Append(this->myMaxPointBuffer, theMaxPoint);
    BVH::Array<int, 4>::Append(this->myNodeInfoBuffer, BVH_Vec4i(1, theBegElem, theEndElem, 0));
    return BVH::Array<int, 4>::Size(this->myNodeInfoBuffer) - 1;
  }

  int AddInnerNode(const BVH_VecNt& theMinPoint,
                   const BVH_VecNt& theMaxPoint,
                   const int        theLftChild,
                   const int        theRghChild)
  {
    BVH::Array<T, N>::Append(this->myMinPointBuffer, theMinPoint);
    BVH::Array<T, N>::Append(this->myMaxPointBuffer, theMaxPoint);
    BVH::Array<int, 4>::Append(this->myNodeInfoBuffer, BVH_Vec4i(0, theLftChild, theRghChild, 0));
    return BVH::Array<int, 4>::Size(this->myNodeInfoBuffer) - 1;
  }

  int AddLeafNode(const BVH_Box<T, N>& theAABB, const int theBegElem, const int theEndElem)
  {
    return AddLeafNode(theAABB.CornerMin(), theAABB.CornerMax(), theBegElem, theEndElem);
  }

  int AddInnerNode(const BVH_Box<T, N>& theAABB, const int theLftChild, const int theRghChild)
  {
    return AddInnerNode(theAABB.CornerMin(), theAABB.CornerMax(), theLftChild, theRghChild);
  }

  int AddLeafNode(const int theBegElem, const int theEndElem)
  {
    BVH::Array<int, 4>::Append(this->myNodeInfoBuffer, BVH_Vec4i(1, theBegElem, theEndElem, 0));
    return BVH::Array<int, 4>::Size(this->myNodeInfoBuffer) - 1;
  }

  int AddInnerNode(const int theLftChild, const int theRghChild)
  {
    BVH::Array<int, 4>::Append(this->myNodeInfoBuffer, BVH_Vec4i(0, theLftChild, theRghChild, 0));
    return BVH::Array<int, 4>::Size(this->myNodeInfoBuffer) - 1;
  }

public:
  T EstimateSAH() const;

  BVH_Tree<T, N, BVH_QuadTree>* CollapseToQuadTree() const;
};

namespace BVH
{

  template <class T, int N>
  void EstimateSAH(const BVH_Tree<T, N, BVH_BinaryTree>* theTree,
                   const int                             theNode,
                   T                                     theProb,
                   T&                                    theSAH)
  {
    BVH_Box<T, N> aBox(theTree->MinPoint(theNode), theTree->MaxPoint(theNode));

    if (theTree->IsOuter(theNode))
    {
      theSAH += theProb * (theTree->EndPrimitive(theNode) - theTree->BegPrimitive(theNode) + 1);
    }
    else
    {
      theSAH += theProb * static_cast<T>(2.0);

      BVH_Box<T, N> aLftBox(theTree->MinPoint(theTree->template Child<0>(theNode)),
                            theTree->MaxPoint(theTree->template Child<0>(theNode)));

      if (theProb > 0.0)
      {
        EstimateSAH(theTree,
                    theTree->template Child<0>(theNode),
                    theProb * aLftBox.Area() / aBox.Area(),
                    theSAH);
      }

      BVH_Box<T, N> aRghBox(theTree->MinPoint(theTree->template Child<1>(theNode)),
                            theTree->MaxPoint(theTree->template Child<1>(theNode)));

      if (theProb > 0.0)
      {
        EstimateSAH(theTree,
                    theTree->template Child<1>(theNode),
                    theProb * aRghBox.Area() / aBox.Area(),
                    theSAH);
      }
    }
  }
} // namespace BVH

template <class T, int N>
T BVH_Tree<T, N, BVH_BinaryTree>::EstimateSAH() const
{
  T aSAH = static_cast<T>(0.0);
  BVH::EstimateSAH<T, N>(this, 0, static_cast<T>(1.0), aSAH);
  return aSAH;
}

template <class T, int N>
BVH_Tree<T, N, BVH_QuadTree>* BVH_Tree<T, N, BVH_BinaryTree>::CollapseToQuadTree() const
{
  BVH_Tree<T, N, BVH_QuadTree>* aQBVH = new BVH_Tree<T, N, BVH_QuadTree>;

  if (this->Length() == 0)
  {
    return aQBVH;
  }

  std::deque<std::pair<int, int>> aQueue(1, std::make_pair(0, 0));

  for (int aNbNodes = 1; !aQueue.empty();)
  {
    const std::pair<int, int> aNode = aQueue.front();

    BVH::Array<T, N>::Append(aQBVH->myMinPointBuffer,
                             BVH::Array<T, N>::Value(this->myMinPointBuffer, std::get<0>(aNode)));
    BVH::Array<T, N>::Append(aQBVH->myMaxPointBuffer,
                             BVH::Array<T, N>::Value(this->myMaxPointBuffer, std::get<0>(aNode)));

    BVH_Vec4i aNodeInfo;
    if (this->IsOuter(std::get<0>(aNode)))
    {
      aNodeInfo = BVH_Vec4i(1,
                            this->BegPrimitive(std::get<0>(aNode)),
                            this->EndPrimitive(std::get<0>(aNode)),
                            std::get<1>(aNode));
    }
    else
    {
      NCollection_Vector<int> aGrandChildNodes;

      const int aLftChild = Child<0>(std::get<0>(aNode));
      const int aRghChild = Child<1>(std::get<0>(aNode));
      if (this->IsOuter(aLftChild))
      {
        aGrandChildNodes.Append(aLftChild);
      }
      else
      {
        aGrandChildNodes.Append(Child<0>(aLftChild));
        aGrandChildNodes.Append(Child<1>(aLftChild));
      }

      if (this->IsOuter(aRghChild))
      {
        aGrandChildNodes.Append(aRghChild);
      }
      else
      {
        aGrandChildNodes.Append(Child<0>(aRghChild));
        aGrandChildNodes.Append(Child<1>(aRghChild));
      }

      for (int aNodeIdx = 0; aNodeIdx < aGrandChildNodes.Size(); ++aNodeIdx)
      {
        aQueue.push_back(std::make_pair(aGrandChildNodes(aNodeIdx), std::get<1>(aNode) + 1));
      }

      aNodeInfo = BVH_Vec4i(0, aNbNodes, aGrandChildNodes.Size() - 1, std::get<1>(aNode));

      aQBVH->myDepth = (std::max)(aQBVH->myDepth, std::get<1>(aNode) + 1);

      aNbNodes += aGrandChildNodes.Size();
    }

    BVH::Array<int, 4>::Append(aQBVH->myNodeInfoBuffer, aNodeInfo);
    aQueue.pop_front();
  }

  return aQBVH;
}
