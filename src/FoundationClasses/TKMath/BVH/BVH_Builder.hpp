#pragma once


#include <BVH_Set.hpp>
#include <BVH_BinaryTree.hpp>

//! A non-template class for using as base for BVH_Builder
//! (just to have a named base class).
class BVH_BuilderTransient : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(BVH_BuilderTransient, Standard_Transient)
public:
  //! Returns the maximum depth of constructed BVH.
  int MaxTreeDepth() const { return myMaxTreeDepth; }

  //! Returns the maximum number of sub-elements in the leaf.
  int LeafNodeSize() const { return myLeafNodeSize; }

  //! Returns parallel flag.
  inline bool IsParallel() const { return myIsParallel; }

  //! Set parallel flag controlling possibility of parallel execution.
  inline void SetParallel(const bool isParallel) { myIsParallel = isParallel; }

protected:
  //! Creates new abstract BVH builder.
  BVH_BuilderTransient(const int theLeafNodeSize, const int theMaxTreeDepth)
      : myMaxTreeDepth(theMaxTreeDepth),
        myLeafNodeSize(theLeafNodeSize),
        myIsParallel(false)
  {
  }

protected:
  int  myMaxTreeDepth; //!< Maximum depth of constructed BVH
  int  myLeafNodeSize; //!< Maximum number of objects per leaf
  bool myIsParallel;   //!< Parallel execution flag.
};

//! Performs construction of BVH tree using bounding
//! boxes (AABBs) of abstract objects.
//! \tparam T Numeric data type
//! \tparam N Vector dimension
template <class T, int N>
class BVH_Builder : public BVH_BuilderTransient
{
public:
  //! Builds BVH using specific algorithm.
  virtual void Build(BVH_Set<T, N>*       theSet,
                     BVH_Tree<T, N>*      theBVH,
                     const BVH_Box<T, N>& theBox) const = 0;

protected:
  //! Creates new abstract BVH builder.
  BVH_Builder(const int theLeafNodeSize, const int theMaxTreeDepth)
      : BVH_BuilderTransient(theLeafNodeSize, theMaxTreeDepth)
  {
  }

  //! Updates depth of constructed BVH tree.
  void updateDepth(BVH_Tree<T, N>* theBVH, const int theLevel) const
  {
    if (theLevel > theBVH->myDepth)
    {
      theBVH->myDepth = theLevel;
    }
  }
};

