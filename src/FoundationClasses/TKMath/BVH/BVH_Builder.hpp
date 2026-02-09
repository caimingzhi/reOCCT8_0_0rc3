#pragma once

#include <BVH_Set.hpp>
#include <BVH_BinaryTree.hpp>

class BVH_BuilderTransient : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(BVH_BuilderTransient, Standard_Transient)
public:
  int MaxTreeDepth() const { return myMaxTreeDepth; }

  int LeafNodeSize() const { return myLeafNodeSize; }

  inline bool IsParallel() const { return myIsParallel; }

  inline void SetParallel(const bool isParallel) { myIsParallel = isParallel; }

protected:
  BVH_BuilderTransient(const int theLeafNodeSize, const int theMaxTreeDepth)
      : myMaxTreeDepth(theMaxTreeDepth),
        myLeafNodeSize(theLeafNodeSize),
        myIsParallel(false)
  {
  }

protected:
  int  myMaxTreeDepth;
  int  myLeafNodeSize;
  bool myIsParallel;
};

template <class T, int N>
class BVH_Builder : public BVH_BuilderTransient
{
public:
  virtual void Build(BVH_Set<T, N>*       theSet,
                     BVH_Tree<T, N>*      theBVH,
                     const BVH_Box<T, N>& theBox) const = 0;

protected:
  BVH_Builder(const int theLeafNodeSize, const int theMaxTreeDepth)
      : BVH_BuilderTransient(theLeafNodeSize, theMaxTreeDepth)
  {
  }

  void updateDepth(BVH_Tree<T, N>* theBVH, const int theLevel) const
  {
    if (theLevel > theBVH->myDepth)
    {
      theBVH->myDepth = theLevel;
    }
  }
};
