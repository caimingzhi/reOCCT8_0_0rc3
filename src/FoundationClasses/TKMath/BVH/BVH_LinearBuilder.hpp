#pragma once

#include <BVH_RadixSorter.hpp>
#include <NCollection_Vector.hpp>
#include <Standard_Assert.hpp>

template <class T, int N>
class BVH_LinearBuilder : public BVH_Builder<T, N>
{
public:
  typedef typename BVH::VectorType<T, N>::Type BVH_VecNt;

public:
  BVH_LinearBuilder(const int theLeafNodeSize = BVH_Constants_LeafNodeSizeDefault,
                    const int theMaxTreeDepth = BVH_Constants_MaxTreeDepth);

  ~BVH_LinearBuilder() override;

  void Build(BVH_Set<T, N>*       theSet,
             BVH_Tree<T, N>*      theBVH,
             const BVH_Box<T, N>& theBox) const override;

protected:
  typedef NCollection_Array1<BVH_EncodedLink>::iterator LinkIterator;

protected:
  int emitHierachy(BVH_Tree<T, N>*                            theBVH,
                   const NCollection_Array1<BVH_EncodedLink>& theEncodedLinks,
                   const int                                  theBit,
                   const int                                  theShift,
                   const int                                  theStart,
                   const int                                  theFinal) const;

  int lowerBound(const NCollection_Array1<BVH_EncodedLink>& theEncodedLinks,
                 int                                        theStart,
                 int                                        theFinal,
                 int                                        theDigit) const;
};

template <class T, int N>
BVH_LinearBuilder<T, N>::BVH_LinearBuilder(const int theLeafNodeSize, const int theMaxTreeDepth)
    : BVH_Builder<T, N>(theLeafNodeSize, theMaxTreeDepth)
{
}

template <class T, int N>
BVH_LinearBuilder<T, N>::~BVH_LinearBuilder() = default;

template <class T, int N>
int BVH_LinearBuilder<T, N>::lowerBound(const NCollection_Array1<BVH_EncodedLink>& theEncodedLinks,
                                        int                                        theStart,
                                        int                                        theFinal,
                                        int                                        theDigit) const
{
  int          aNbPrims = theFinal - theStart;
  unsigned int aBit     = 1U << theDigit;
  while (aNbPrims > 0)
  {
    const int aStep = aNbPrims / 2;
    if (theEncodedLinks.Value(theStart + aStep).first & aBit)
    {
      aNbPrims = aStep;
    }
    else
    {
      theStart += aStep + 1;
      aNbPrims -= aStep + 1;
    }
  }

  return theStart;
}

template <class T, int N>
int BVH_LinearBuilder<T, N>::emitHierachy(
  BVH_Tree<T, N>*                            theBVH,
  const NCollection_Array1<BVH_EncodedLink>& theEncodedLinks,
  const int                                  theDigit,
  const int                                  theShift,
  const int                                  theStart,
  const int                                  theFinal) const
{
  if (theFinal - theStart > BVH_Builder<T, N>::myLeafNodeSize)
  {
    const int aPosition = theDigit < 0 ? (theStart + theFinal) / 2
                                       : lowerBound(theEncodedLinks, theStart, theFinal, theDigit);
    if (aPosition == theStart || aPosition == theFinal)
    {
      return emitHierachy(theBVH, theEncodedLinks, theDigit - 1, theShift, theStart, theFinal);
    }

    const int aNode    = theBVH->AddInnerNode(0, 0);
    const int aRghNode = theShift + aPosition - theStart;

    const int aLftChild =
      emitHierachy(theBVH, theEncodedLinks, theDigit - 1, theShift, theStart, aPosition);
    const int aRghChild =
      emitHierachy(theBVH, theEncodedLinks, theDigit - 1, aRghNode, aPosition, theFinal);

    theBVH->NodeInfoBuffer()[aNode].y() = aLftChild;
    theBVH->NodeInfoBuffer()[aNode].z() = aRghChild;
    return aNode;
  }
  else
  {

    return theBVH->AddLeafNode(theShift, theShift + theFinal - theStart - 1);
  }
}

namespace BVH
{

  template <class T, int N>
  int UpdateBounds(BVH_Set<T, N>* theSet, BVH_Tree<T, N>* theTree, const int theNode = 0)
  {
    const BVH_Vec4i aData = theTree->NodeInfoBuffer()[theNode];
    if (aData.x() == 0)
    {
      const int aLftChild = theTree->NodeInfoBuffer()[theNode].y();
      const int aRghChild = theTree->NodeInfoBuffer()[theNode].z();

      const int aLftDepth = UpdateBounds(theSet, theTree, aLftChild);
      const int aRghDepth = UpdateBounds(theSet, theTree, aRghChild);

      typename BVH_Box<T, N>::BVH_VecNt aLftMinPoint = theTree->MinPointBuffer()[aLftChild];
      typename BVH_Box<T, N>::BVH_VecNt aLftMaxPoint = theTree->MaxPointBuffer()[aLftChild];
      typename BVH_Box<T, N>::BVH_VecNt aRghMinPoint = theTree->MinPointBuffer()[aRghChild];
      typename BVH_Box<T, N>::BVH_VecNt aRghMaxPoint = theTree->MaxPointBuffer()[aRghChild];

      BVH::BoxMinMax<T, N>::CwiseMin(aLftMinPoint, aRghMinPoint);
      BVH::BoxMinMax<T, N>::CwiseMax(aLftMaxPoint, aRghMaxPoint);

      theTree->MinPointBuffer()[theNode] = aLftMinPoint;
      theTree->MaxPointBuffer()[theNode] = aLftMaxPoint;
      return (std::max)(aLftDepth, aRghDepth) + 1;
    }
    else
    {
      typename BVH_Box<T, N>::BVH_VecNt& aMinPoint = theTree->MinPointBuffer()[theNode];
      typename BVH_Box<T, N>::BVH_VecNt& aMaxPoint = theTree->MaxPointBuffer()[theNode];
      for (int aPrimIdx = aData.y(); aPrimIdx <= aData.z(); ++aPrimIdx)
      {
        const BVH_Box<T, N> aBox = theSet->Box(aPrimIdx);
        if (aPrimIdx == aData.y())
        {
          aMinPoint = aBox.CornerMin();
          aMaxPoint = aBox.CornerMax();
        }
        else
        {
          BVH::BoxMinMax<T, N>::CwiseMin(aMinPoint, aBox.CornerMin());
          BVH::BoxMinMax<T, N>::CwiseMax(aMaxPoint, aBox.CornerMax());
        }
      }
    }
    return 0;
  }

  template <class T, int N>
  struct BoundData
  {
    BVH_Set<T, N>*  mySet;
    BVH_Tree<T, N>* myBVH;
    int             myNode;
    int             myLevel;
    int*            myHeight;
  };

  template <class T, int N>
  class UpdateBoundTask
  {
  public:
    UpdateBoundTask(const bool isParallel)
        : myIsParallel(isParallel)
    {
    }

    void operator()(const BoundData<T, N>& theData) const
    {
      if (theData.myBVH->IsOuter(theData.myNode) || theData.myLevel > 2)
      {
        *theData.myHeight = BVH::UpdateBounds(theData.mySet, theData.myBVH, theData.myNode);
      }
      else
      {
        int aLftHeight = 0;
        int aRghHeight = 0;

        const int aLftChild = theData.myBVH->NodeInfoBuffer()[theData.myNode].y();
        const int aRghChild = theData.myBVH->NodeInfoBuffer()[theData.myNode].z();

        NCollection_Vector<BoundData<T, N>> aList(2);
        if (!theData.myBVH->IsOuter(aLftChild))
        {
          BoundData<T, N> aBoundData = {theData.mySet,
                                        theData.myBVH,
                                        aLftChild,
                                        theData.myLevel + 1,
                                        &aLftHeight};
          aList.Append(aBoundData);
        }
        else
        {
          aLftHeight = BVH::UpdateBounds(theData.mySet, theData.myBVH, aLftChild);
        }

        if (!theData.myBVH->IsOuter(aRghChild))
        {
          BoundData<T, N> aBoundData = {theData.mySet,
                                        theData.myBVH,
                                        aRghChild,
                                        theData.myLevel + 1,
                                        &aRghHeight};
          aList.Append(aBoundData);
        }
        else
        {
          aRghHeight = BVH::UpdateBounds(theData.mySet, theData.myBVH, aRghChild);
        }

        if (aList.Size() > 0)
        {
          OSD_Parallel::ForEach(aList.begin(),
                                aList.end(),
                                UpdateBoundTask<T, N>(myIsParallel),
                                !myIsParallel);
        }

        typename BVH_Box<T, N>::BVH_VecNt aLftMinPoint = theData.myBVH->MinPointBuffer()[aLftChild];
        typename BVH_Box<T, N>::BVH_VecNt aLftMaxPoint = theData.myBVH->MaxPointBuffer()[aLftChild];
        typename BVH_Box<T, N>::BVH_VecNt aRghMinPoint = theData.myBVH->MinPointBuffer()[aRghChild];
        typename BVH_Box<T, N>::BVH_VecNt aRghMaxPoint = theData.myBVH->MaxPointBuffer()[aRghChild];

        BVH::BoxMinMax<T, N>::CwiseMin(aLftMinPoint, aRghMinPoint);
        BVH::BoxMinMax<T, N>::CwiseMax(aLftMaxPoint, aRghMaxPoint);

        theData.myBVH->MinPointBuffer()[theData.myNode] = aLftMinPoint;
        theData.myBVH->MaxPointBuffer()[theData.myNode] = aLftMaxPoint;

        *theData.myHeight = (std::max)(aLftHeight, aRghHeight) + 1;
      }
    }

  private:
    bool myIsParallel;
  };
} // namespace BVH

template <class T, int N>
void BVH_LinearBuilder<T, N>::Build(BVH_Set<T, N>*       theSet,
                                    BVH_Tree<T, N>*      theBVH,
                                    const BVH_Box<T, N>& theBox) const
{
  Standard_STATIC_ASSERT(N == 2 || N == 3 || N == 4);
  const int aSetSize = theSet->Size();
  if (theBVH == nullptr || aSetSize == 0)
  {
    return;
  }

  theBVH->Clear();

  BVH_RadixSorter<T, N> aRadixSorter(theBox);
  aRadixSorter.SetParallel(this->IsParallel());

  aRadixSorter.Perform(theSet);

  emitHierachy(theBVH, aRadixSorter.EncodedLinks(), 29, 0, 0, theSet->Size());

  theBVH->MinPointBuffer().resize(theBVH->NodeInfoBuffer().size());
  theBVH->MaxPointBuffer().resize(theBVH->NodeInfoBuffer().size());

  int                        aHeight    = 0;
  BVH::BoundData<T, N>       aBoundData = {theSet, theBVH, 0, 0, &aHeight};
  BVH::UpdateBoundTask<T, N> aBoundTask(this->IsParallel());
  aBoundTask(aBoundData);

  BVH_Builder<T, N>::updateDepth(theBVH, aHeight);
}
