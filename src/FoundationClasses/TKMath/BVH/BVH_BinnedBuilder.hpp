#pragma once

#include <BVH_QueueBuilder.hpp>

#include <algorithm>

#if defined(_WIN32) && defined(max)
  #undef max
#endif

#include <limits>

template <class T, int N>
struct BVH_Bin
{

  BVH_Bin()
      : Count(0)
  {
  }

  int           Count;
  BVH_Box<T, N> Box;
};

template <class T, int N, int Bins = BVH_Constants_NbBinsOptimal>
class BVH_BinnedBuilder : public BVH_QueueBuilder<T, N>
{
public:
  typedef BVH_Bin<T, N> BVH_BinVector[Bins];

  struct BVH_SplitPlane
  {
    BVH_Bin<T, N> LftVoxel;
    BVH_Bin<T, N> RghVoxel;
  };

  typedef BVH_SplitPlane BVH_SplitPlanes[Bins + 1];

public:
  BVH_BinnedBuilder(const int  theLeafNodeSize = BVH_Constants_LeafNodeSizeDefault,
                    const int  theMaxTreeDepth = BVH_Constants_MaxTreeDepth,
                    const bool theDoMainSplits = false,
                    const int  theNumOfThreads = 1)
      : BVH_QueueBuilder<T, N>(theLeafNodeSize, theMaxTreeDepth, theNumOfThreads),
        myUseMainAxis(theDoMainSplits)
  {
  }

  ~BVH_BinnedBuilder() override = default;

protected:
  typename BVH_QueueBuilder<T, N>::BVH_ChildNodes buildNode(BVH_Set<T, N>*  theSet,
                                                            BVH_Tree<T, N>* theBVH,
                                                            const int       theNode) const override;

  virtual void getSubVolumes(BVH_Set<T, N>*  theSet,
                             BVH_Tree<T, N>* theBVH,
                             const int       theNode,
                             BVH_BinVector&  theBins,
                             const int       theAxis) const;

private:
  bool myUseMainAxis;
};

template <class T, int N, int Bins>
void BVH_BinnedBuilder<T, N, Bins>::getSubVolumes(BVH_Set<T, N>*  theSet,
                                                  BVH_Tree<T, N>* theBVH,
                                                  const int       theNode,
                                                  BVH_BinVector&  theBins,
                                                  const int       theAxis) const
{
  const T aMin          = BVH::VecComp<T, N>::Get(theBVH->MinPoint(theNode), theAxis);
  const T aMax          = BVH::VecComp<T, N>::Get(theBVH->MaxPoint(theNode), theAxis);
  const T anInverseStep = static_cast<T>(Bins) / (aMax - aMin);
  for (int anIdx = theBVH->BegPrimitive(theNode); anIdx <= theBVH->EndPrimitive(theNode); ++anIdx)
  {
    typename BVH_Set<T, N>::BVH_BoxNt aBox = theSet->Box(anIdx);
    int aBinIndex = BVH::IntFloor<T>((theSet->Center(anIdx, theAxis) - aMin) * anInverseStep);
    if (aBinIndex < 0)
    {
      aBinIndex = 0;
    }
    else if (aBinIndex >= Bins)
    {
      aBinIndex = Bins - 1;
    }

    theBins[aBinIndex].Count++;
    theBins[aBinIndex].Box.Combine(aBox);
  }
}

namespace BVH
{
  template <class T, int N>
  int SplitPrimitives(BVH_Set<T, N>*       theSet,
                      const BVH_Box<T, N>& theBox,
                      const int            theBeg,
                      const int            theEnd,
                      const int            theBin,
                      const int            theAxis,
                      const int            theBins)
  {
    const T aMin = BVH::VecComp<T, N>::Get(theBox.CornerMin(), theAxis);
    const T aMax = BVH::VecComp<T, N>::Get(theBox.CornerMax(), theAxis);

    const T anInverseStep = static_cast<T>(theBins) / (aMax - aMin);

    int aLftIdx(theBeg);
    int aRghIdx(theEnd);

    do
    {
      while (BVH::IntFloor<T>((theSet->Center(aLftIdx, theAxis) - aMin) * anInverseStep) <= theBin
             && aLftIdx < theEnd)
      {
        ++aLftIdx;
      }
      while (BVH::IntFloor<T>((theSet->Center(aRghIdx, theAxis) - aMin) * anInverseStep) > theBin
             && aRghIdx > theBeg)
      {
        --aRghIdx;
      }

      if (aLftIdx <= aRghIdx)
      {
        if (aLftIdx != aRghIdx)
        {
          theSet->Swap(aLftIdx, aRghIdx);
        }

        ++aLftIdx;
        --aRghIdx;
      }
    } while (aLftIdx <= aRghIdx);

    return aLftIdx;
  }

  template <class T, int N>
  struct BVH_AxisSelector
  {
    typedef typename BVH::VectorType<T, N>::Type BVH_VecNt;

    static int MainAxis(const BVH_VecNt& theSize)
    {
      if (theSize.y() > theSize.x())
      {
        return theSize.y() > theSize.z() ? 1 : 2;
      }
      else
      {
        return theSize.z() > theSize.x() ? 2 : 0;
      }
    }
  };

  template <class T>
  struct BVH_AxisSelector<T, 2>
  {
    typedef typename BVH::VectorType<T, 2>::Type BVH_VecNt;

    static int MainAxis(const BVH_VecNt& theSize) { return theSize.x() > theSize.y() ? 0 : 1; }
  };
} // namespace BVH

template <class T, int N, int Bins>
typename BVH_QueueBuilder<T, N>::BVH_ChildNodes BVH_BinnedBuilder<T, N, Bins>::buildNode(
  BVH_Set<T, N>*  theSet,
  BVH_Tree<T, N>* theBVH,
  const int       theNode) const
{
  const int aNodeBegPrimitive = theBVH->BegPrimitive(theNode);
  const int aNodeEndPrimitive = theBVH->EndPrimitive(theNode);
  const int aNodeNbPrimitives = theBVH->NbPrimitives(theNode);
  if (aNodeNbPrimitives <= BVH_Builder<T, N>::myLeafNodeSize)
  {

    return typename BVH_QueueBuilder<T, N>::BVH_ChildNodes();
  }

  const BVH_Box<T, N> anAABB(theBVH->MinPoint(theNode), theBVH->MaxPoint(theNode));
  const typename BVH_Box<T, N>::BVH_VecNt aSize = anAABB.Size();

  int aMinSplitAxis   = -1;
  int aMinSplitIndex  = 0;
  int aMinSplitNumLft = 0;
  int aMinSplitNumRgh = 0;

  BVH_Box<T, N> aMinSplitBoxLft;
  BVH_Box<T, N> aMinSplitBoxRgh;

  double    aMinSplitCost = std::numeric_limits<double>::max();
  const int aMainAxis     = BVH::BVH_AxisSelector<T, N>::MainAxis(aSize);

  for (int anAxis = myUseMainAxis ? aMainAxis : 0;
       anAxis <= (myUseMainAxis ? aMainAxis : (std::min)(N - 1, 2));
       ++anAxis)
  {
    if (BVH::VecComp<T, N>::Get(aSize, anAxis) <= BVH::THE_NODE_MIN_SIZE)
    {
      continue;
    }

    BVH_BinVector aBinVector;
    getSubVolumes(theSet, theBVH, theNode, aBinVector, anAxis);

    BVH_SplitPlanes aSplitPlanes;
    for (int aLftSplit = 1, aRghSplit = Bins - 1; aLftSplit < Bins; ++aLftSplit, --aRghSplit)
    {
      aSplitPlanes[aLftSplit].LftVoxel.Count =
        aSplitPlanes[aLftSplit - 1].LftVoxel.Count + aBinVector[aLftSplit - 1].Count;
      aSplitPlanes[aRghSplit].RghVoxel.Count =
        aSplitPlanes[aRghSplit + 1].RghVoxel.Count + aBinVector[aRghSplit + 0].Count;

      aSplitPlanes[aLftSplit].LftVoxel.Box = aSplitPlanes[aLftSplit - 1].LftVoxel.Box;
      aSplitPlanes[aRghSplit].RghVoxel.Box = aSplitPlanes[aRghSplit + 1].RghVoxel.Box;

      aSplitPlanes[aLftSplit].LftVoxel.Box.Combine(aBinVector[aLftSplit - 1].Box);
      aSplitPlanes[aRghSplit].RghVoxel.Box.Combine(aBinVector[aRghSplit + 0].Box);
    }

    const double aParentArea = static_cast<double>(anAABB.Area());
    for (int aSplit = 1; aSplit < Bins; ++aSplit)
    {

      const double aLftArea = static_cast<double>(aSplitPlanes[aSplit].LftVoxel.Box.Area());
      const double aRghArea = static_cast<double>(aSplitPlanes[aSplit].RghVoxel.Box.Area());
      double       aCost    = (aLftArea / aParentArea) * aSplitPlanes[aSplit].LftVoxel.Count
                     + (aRghArea / aParentArea) * aSplitPlanes[aSplit].RghVoxel.Count;

      if (aCost <= aMinSplitCost)
      {
        aMinSplitCost   = aCost;
        aMinSplitAxis   = anAxis;
        aMinSplitIndex  = aSplit;
        aMinSplitBoxLft = aSplitPlanes[aSplit].LftVoxel.Box;
        aMinSplitBoxRgh = aSplitPlanes[aSplit].RghVoxel.Box;
        aMinSplitNumLft = aSplitPlanes[aSplit].LftVoxel.Count;
        aMinSplitNumRgh = aSplitPlanes[aSplit].RghVoxel.Count;
      }
    }
  }

  theBVH->SetInner(theNode);
  int aMiddle = -1;
  if (aMinSplitNumLft == 0 || aMinSplitNumRgh == 0 || aMinSplitAxis == -1)
  {
    aMinSplitBoxLft.Clear();
    aMinSplitBoxRgh.Clear();

    aMiddle = (std::max)(aNodeBegPrimitive + 1,
                         static_cast<int>((aNodeBegPrimitive + aNodeEndPrimitive) / 2.f));

    aMinSplitNumLft = aMiddle - aNodeBegPrimitive;
    for (int anIndex = aNodeBegPrimitive; anIndex < aMiddle; ++anIndex)
    {
      aMinSplitBoxLft.Combine(theSet->Box(anIndex));
    }

    aMinSplitNumRgh = aNodeEndPrimitive - aMiddle + 1;
    for (int anIndex = aNodeEndPrimitive; anIndex >= aMiddle; --anIndex)
    {
      aMinSplitBoxRgh.Combine(theSet->Box(anIndex));
    }
  }
  else
  {
    aMiddle = BVH::SplitPrimitives<T, N>(theSet,
                                         anAABB,
                                         aNodeBegPrimitive,
                                         aNodeEndPrimitive,
                                         aMinSplitIndex - 1,
                                         aMinSplitAxis,
                                         Bins);
  }

  typedef typename BVH_QueueBuilder<T, N>::BVH_PrimitiveRange Range;
  return typename BVH_QueueBuilder<T, N>::BVH_ChildNodes(aMinSplitBoxLft,
                                                         aMinSplitBoxRgh,
                                                         Range(aNodeBegPrimitive, aMiddle - 1),
                                                         Range(aMiddle, aNodeEndPrimitive));
}
