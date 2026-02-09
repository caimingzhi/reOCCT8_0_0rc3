#pragma once

#include <BVH_QueueBuilder.hpp>
#include <BVH_QuickSorter.hpp>
#include <NCollection_Array1.hpp>

template <class T, int N>
class BVH_SweepPlaneBuilder : public BVH_QueueBuilder<T, N>
{
public:
  BVH_SweepPlaneBuilder(const int theLeafNodeSize = BVH_Constants_LeafNodeSizeDefault,
                        const int theMaxTreeDepth = BVH_Constants_MaxTreeDepth,
                        const int theNumOfThreads = 1)
      : BVH_QueueBuilder<T, N>(theLeafNodeSize, theMaxTreeDepth, theNumOfThreads)
  {
  }

  ~BVH_SweepPlaneBuilder() override = default;

protected:
  typename BVH_QueueBuilder<T, N>::BVH_ChildNodes buildNode(BVH_Set<T, N>*  theSet,
                                                            BVH_Tree<T, N>* theBVH,
                                                            const int       theNode) const override
  {
    const int aNodeBegPrimitive = theBVH->BegPrimitive(theNode);
    const int aNodeEndPrimitive = theBVH->EndPrimitive(theNode);
    const int aNodeNbPrimitives = theBVH->NbPrimitives(theNode);
    if (aNodeNbPrimitives <= BVH_Builder<T, N>::myLeafNodeSize)
    {

      return typename BVH_QueueBuilder<T, N>::BVH_ChildNodes();
    }

    int aMinSplitAxis  = -1;
    int aMinSplitIndex = 0;

    NCollection_Array1<double> aLftSet(1, aNodeNbPrimitives - 1);
    NCollection_Array1<double> aRghSet(1, aNodeNbPrimitives - 1);
    double                     aMinSplitCost = std::numeric_limits<double>::max();

    for (int anAxis = 0; anAxis < (N < 4 ? N : 3); ++anAxis)
    {
      const T aNodeSize = BVH::VecComp<T, N>::Get(theBVH->MaxPoint(theNode), anAxis)
                          - BVH::VecComp<T, N>::Get(theBVH->MinPoint(theNode), anAxis);
      if (aNodeSize <= BVH::THE_NODE_MIN_SIZE)
      {
        continue;
      }

      BVH_QuickSorter<T, N>(anAxis).Perform(theSet, aNodeBegPrimitive, aNodeEndPrimitive);
      BVH_Box<T, N> aLftBox;
      BVH_Box<T, N> aRghBox;

      for (int anIndex = 1; anIndex < aNodeNbPrimitives; ++anIndex)
      {
        aLftBox.Combine(theSet->Box(anIndex + aNodeBegPrimitive - 1));
        aLftSet(anIndex) = static_cast<double>(aLftBox.Area());
      }

      for (int anIndex = 1; anIndex < aNodeNbPrimitives; ++anIndex)
      {
        aRghBox.Combine(theSet->Box(aNodeEndPrimitive - anIndex + 1));
        aRghSet(anIndex) = static_cast<double>(aRghBox.Area());
      }

      for (int aNbLft = 1, aNbRgh = aNodeNbPrimitives - 1; aNbLft < aNodeNbPrimitives;
           ++aNbLft, --aNbRgh)
      {
        double aCost = (aLftSet(aNbLft))*aNbLft + (aRghSet(aNbRgh))*aNbRgh;
        if (aCost < aMinSplitCost)
        {
          aMinSplitCost  = aCost;
          aMinSplitAxis  = anAxis;
          aMinSplitIndex = aNbLft;
        }
      }
    }

    if (aMinSplitAxis == -1)
    {
      return typename BVH_QueueBuilder<T, N>::BVH_ChildNodes();
    }

    theBVH->SetInner(theNode);
    if (aMinSplitAxis != (N < 4 ? N - 1 : 2))
    {
      BVH_QuickSorter<T, N>(aMinSplitAxis).Perform(theSet, aNodeBegPrimitive, aNodeEndPrimitive);
    }

    BVH_Box<T, N> aMinSplitBoxLft;
    BVH_Box<T, N> aMinSplitBoxRgh;

    for (int anIndex = aNodeBegPrimitive; anIndex < aMinSplitIndex + aNodeBegPrimitive; ++anIndex)
    {
      aMinSplitBoxLft.Combine(theSet->Box(anIndex));
    }

    for (int anIndex = aNodeEndPrimitive; anIndex >= aMinSplitIndex + aNodeBegPrimitive; --anIndex)
    {
      aMinSplitBoxRgh.Combine(theSet->Box(anIndex));
    }

    const int aMiddle = aNodeBegPrimitive + aMinSplitIndex;
    typedef typename BVH_QueueBuilder<T, N>::BVH_PrimitiveRange Range;
    return typename BVH_QueueBuilder<T, N>::BVH_ChildNodes(aMinSplitBoxLft,
                                                           aMinSplitBoxRgh,
                                                           Range(aNodeBegPrimitive, aMiddle - 1),
                                                           Range(aMiddle, aNodeEndPrimitive));
  }
};
