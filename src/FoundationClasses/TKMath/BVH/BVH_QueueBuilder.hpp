#pragma once

#include <BVH_Builder.hpp>
#include <BVH_BuildThread.hpp>
#include <NCollection_Vector.hpp>

#include <mutex>

template <class T, int N>
class BVH_QueueBuilder : public BVH_Builder<T, N>
{
public:
  BVH_QueueBuilder(const int theLeafNodeSize,
                   const int theMaxTreeDepth,
                   const int theNumOfThreads = 1)
      : BVH_Builder<T, N>(theLeafNodeSize, theMaxTreeDepth),
        myNumOfThreads(theNumOfThreads)
  {
  }

  ~BVH_QueueBuilder() override = default;

public:
  void Build(BVH_Set<T, N>*       theSet,
             BVH_Tree<T, N>*      theBVH,
             const BVH_Box<T, N>& theBox) const override;

protected:
  struct BVH_PrimitiveRange
  {
    int Start;
    int Final;

    BVH_PrimitiveRange(int theStart = -1, int theFinal = -1)
        : Start(theStart),
          Final(theFinal)
    {
    }

    int Size() const { return Final - Start + 1; }

    bool IsValid() const { return Start != -1; }
  };

  struct BVH_ChildNodes
  {

    BVH_Box<T, N> Boxes[2];

    BVH_PrimitiveRange Ranges[2];

    BVH_ChildNodes() = default;

    BVH_ChildNodes(const BVH_Box<T, N>&      theLftBox,
                   const BVH_Box<T, N>&      theRghBox,
                   const BVH_PrimitiveRange& theLftRange,
                   const BVH_PrimitiveRange& theRghRange)
    {
      Boxes[0]  = theLftBox;
      Boxes[1]  = theRghBox;
      Ranges[0] = theLftRange;
      Ranges[1] = theRghRange;
    }

    int NbPrims(const int theChild) const { return Ranges[theChild].Size(); }

    bool IsValid() const { return Ranges[0].IsValid() && Ranges[1].IsValid(); }
  };

  class BVH_TypedBuildTool : public BVH_BuildTool
  {
  public:
    BVH_TypedBuildTool(BVH_Set<T, N>*                theSet,
                       BVH_Tree<T, N>*               theBVH,
                       BVH_BuildQueue&               theBuildQueue,
                       const BVH_QueueBuilder<T, N>* theAlgo)
        : mySet(theSet),
          myBVH(theBVH),
          myBuildQueue(&theBuildQueue),
          myAlgo(theAlgo)
    {
      Standard_ASSERT_RAISE(myAlgo != nullptr, "Error! BVH builder should be queue based");
    }

    void Perform(const int theNode) override
    {
      const typename BVH_QueueBuilder<T, N>::BVH_ChildNodes aChildren =
        myAlgo->buildNode(mySet, myBVH, theNode);
      myAlgo->addChildren(myBVH, *myBuildQueue, theNode, aChildren);
    }

  protected:
    BVH_Set<T, N>*                mySet;
    BVH_Tree<T, N>*               myBVH;
    BVH_BuildQueue*               myBuildQueue;
    const BVH_QueueBuilder<T, N>* myAlgo;
  };

protected:
  virtual typename BVH_QueueBuilder<T, N>::BVH_ChildNodes buildNode(BVH_Set<T, N>*  theSet,
                                                                    BVH_Tree<T, N>* theBVH,
                                                                    const int theNode) const = 0;

  virtual void addChildren(BVH_Tree<T, N>*       theBVH,
                           BVH_BuildQueue&       theBuildQueue,
                           const int             theNode,
                           const BVH_ChildNodes& theSubNodes) const;

protected:
  int myNumOfThreads;
};

template <class T, int N>
void BVH_QueueBuilder<T, N>::addChildren(
  BVH_Tree<T, N>*                                        theBVH,
  BVH_BuildQueue&                                        theBuildQueue,
  const int                                              theNode,
  const typename BVH_QueueBuilder<T, N>::BVH_ChildNodes& theSubNodes) const
{
  int aChildren[] = {-1, -1};
  if (!theSubNodes.IsValid())
  {
    return;
  }

  {
    std::lock_guard<std::mutex> aLock(theBuildQueue.myMutex);

    for (int anIdx = 0; anIdx < 2; ++anIdx)
    {
      aChildren[anIdx] = theBVH->AddLeafNode(theSubNodes.Boxes[anIdx],
                                             theSubNodes.Ranges[anIdx].Start,
                                             theSubNodes.Ranges[anIdx].Final);
    }

    BVH_Builder<T, N>::updateDepth(theBVH, theBVH->Level(theNode) + 1);
  }

  for (int anIdx = 0; anIdx < 2; ++anIdx)
  {
    const int aChildIndex = aChildren[anIdx];

    theBVH->Level(aChildIndex) = theBVH->Level(theNode) + 1;

    (anIdx == 0 ? theBVH->template Child<0>(theNode) : theBVH->template Child<1>(theNode)) =
      aChildIndex;

    const bool isLeaf = theSubNodes.NbPrims(anIdx) <= BVH_Builder<T, N>::myLeafNodeSize
                        || theBVH->Level(aChildIndex) >= BVH_Builder<T, N>::myMaxTreeDepth;

    if (!isLeaf)
    {
      theBuildQueue.Enqueue(aChildIndex);
    }
  }
}

template <class T, int N>
void BVH_QueueBuilder<T, N>::Build(BVH_Set<T, N>*       theSet,
                                   BVH_Tree<T, N>*      theBVH,
                                   const BVH_Box<T, N>& theBox) const
{
  Standard_ASSERT_RETURN(theBVH != nullptr,
                         "Error! BVH tree to construct is NULL",
                         Standard_VOID_RETURN);

  theBVH->Clear();
  const int aSetSize = theSet->Size();
  if (aSetSize == 0)
  {
    return;
  }

  const int aRoot = theBVH->AddLeafNode(theBox, 0, aSetSize - 1);
  if (theSet->Size() == 1)
  {
    return;
  }

  BVH_BuildQueue aBuildQueue;
  aBuildQueue.Enqueue(aRoot);

  BVH_TypedBuildTool aBuildTool(theSet, theBVH, aBuildQueue, this);
  if (myNumOfThreads > 1)
  {

    theBVH->Reserve(2 * aSetSize - 1);

    NCollection_Vector<occ::handle<BVH_BuildThread>> aThreads;

    for (int aThreadIndex = 0; aThreadIndex < myNumOfThreads; ++aThreadIndex)
    {
      aThreads.Append(new BVH_BuildThread(aBuildTool, aBuildQueue));
      aThreads.Last()->Run();
    }

    for (int aThreadIndex = 0; aThreadIndex < myNumOfThreads; ++aThreadIndex)
    {
      aThreads.ChangeValue(aThreadIndex)->Wait();
    }

    theBVH->Reserve(theBVH->Length());
  }
  else
  {
    BVH_BuildThread aThread(aBuildTool, aBuildQueue);

    aThread.execute();
  }
}
