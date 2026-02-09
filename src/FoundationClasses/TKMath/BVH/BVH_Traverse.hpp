#pragma once

#include <BVH_Box.hpp>
#include <BVH_Tree.hpp>

template <class MetricType>
class BVH_BaseTraverse
{
public:
  virtual bool IsMetricBetter(const MetricType&, const MetricType&) const { return true; }

public:
  virtual bool RejectMetric(const MetricType&) const { return false; }

public:
  virtual bool Stop() const { return false; }

protected:
  BVH_BaseTraverse() {}

  virtual ~BVH_BaseTraverse() = default;
};

template <class NumType, int Dimension, class BVHSetType = void, class MetricType = NumType>
class BVH_Traverse : public BVH_BaseTraverse<MetricType>
{
public:
  typedef typename BVH_Box<NumType, Dimension>::BVH_VecNt BVH_VecNt;

public:
  BVH_Traverse()
      : BVH_BaseTraverse<MetricType>(),
        myBVHSet(nullptr)
  {
  }

public:
  void SetBVHSet(BVHSetType* theBVHSet) { myBVHSet = theBVHSet; }

public:
  virtual bool AcceptMetric(const MetricType&) const { return false; }

  virtual bool RejectNode(const BVH_VecNt& theCornerMin,
                          const BVH_VecNt& theCornerMax,
                          MetricType&      theMetric) const = 0;

  virtual bool Accept(const int theIndex, const MetricType& theMetric) = 0;

public:
  int Select()
  {
    if (myBVHSet)
    {
      const opencascade::handle<BVH_Tree<NumType, Dimension>>& aBVH = myBVHSet->BVH();
      return Select(aBVH);
    }
    return 0;
  }

  int Select(const opencascade::handle<BVH_Tree<NumType, Dimension>>& theBVH);

protected:
  struct BVH_NodeInStack
  {

    constexpr BVH_NodeInStack(const int         theNodeID = 0,
                              const MetricType& theMetric = MetricType()) noexcept
        : NodeID(theNodeID),
          Metric(theMetric)
    {
    }

    int        NodeID;
    MetricType Metric;
  };

protected:
  BVHSetType* myBVHSet;
};

template <class NumType, int Dimension, class BVHSetType = void, class MetricType = NumType>
class BVH_PairTraverse : public BVH_BaseTraverse<MetricType>
{
public:
  typedef typename BVH_Box<NumType, Dimension>::BVH_VecNt BVH_VecNt;

public:
  BVH_PairTraverse()
      : BVH_BaseTraverse<MetricType>(),
        myBVHSet1(nullptr),
        myBVHSet2(nullptr)
  {
  }

public:
  void SetBVHSets(BVHSetType* theBVHSet1, BVHSetType* theBVHSet2)
  {
    myBVHSet1 = theBVHSet1;
    myBVHSet2 = theBVHSet2;
  }

public:
  virtual bool RejectNode(const BVH_VecNt& theCornerMin1,
                          const BVH_VecNt& theCornerMax1,
                          const BVH_VecNt& theCornerMin2,
                          const BVH_VecNt& theCornerMax2,
                          MetricType&      theMetric) const = 0;

  virtual bool Accept(const int theIndex1, const int theIndex2) = 0;

public:
  int Select()
  {
    if (myBVHSet1 && myBVHSet2)
    {
      const opencascade::handle<BVH_Tree<NumType, Dimension>>& aBVH1 = myBVHSet1->BVH();
      const opencascade::handle<BVH_Tree<NumType, Dimension>>& aBVH2 = myBVHSet2->BVH();
      return Select(aBVH1, aBVH2);
    }
    return 0;
  }

  int Select(const opencascade::handle<BVH_Tree<NumType, Dimension>>& theBVH1,
             const opencascade::handle<BVH_Tree<NumType, Dimension>>& theBVH2);

protected:
  struct BVH_PairNodesInStack
  {

    constexpr BVH_PairNodesInStack(const int         theNodeID1 = 0,
                                   const int         theNodeID2 = 0,
                                   const MetricType& theMetric  = MetricType()) noexcept
        : NodeID1(theNodeID1),
          NodeID2(theNodeID2),
          Metric(theMetric)
    {
    }

    int        NodeID1;
    int        NodeID2;
    MetricType Metric;
  };

protected:
  BVHSetType* myBVHSet1;
  BVHSetType* myBVHSet2;
};

#include <Standard_Assert.hpp>

template <class NumType, int Dimension, class BVHSetType, class MetricType>
int BVH_Traverse<NumType, Dimension, BVHSetType, MetricType>::Select(
  const opencascade::handle<BVH_Tree<NumType, Dimension>>& theBVH)
{
  if (theBVH.IsNull())
    return 0;

  const BVH_Array4i& aBVHNodes = theBVH->NodeInfoBuffer();
  if (aBVHNodes.empty())
    return 0;

  BVH_NodeInStack aStack[BVH_Constants_MaxTreeDepth];

  BVH_NodeInStack aNode(0);

  BVH_NodeInStack aPrevNode = aNode;

  int aHead       = -1;
  int aNbAccepted = 0;

  for (;;)
  {
    const BVH_Vec4i& aData = aBVHNodes[aNode.NodeID];

    if (aData.x() == 0)
    {

      if (!this->AcceptMetric(aNode.Metric))
      {

        MetricType aMetricLft;
        bool       isGoodLft =
          !RejectNode(theBVH->MinPoint(aData.y()), theBVH->MaxPoint(aData.y()), aMetricLft);
        if (this->Stop())
          return aNbAccepted;

        MetricType aMetricRgh;
        bool       isGoodRgh =
          !RejectNode(theBVH->MinPoint(aData.z()), theBVH->MaxPoint(aData.z()), aMetricRgh);
        if (this->Stop())
          return aNbAccepted;

        if (isGoodLft && isGoodRgh)
        {

          Standard_ASSERT_RAISE(aHead < BVH_Constants_MaxTreeDepth - 1,
                                "Error! BVH stack overflow");
          if (this->IsMetricBetter(aMetricLft, aMetricRgh))
          {
            aNode           = BVH_NodeInStack(aData.y(), aMetricLft);
            aStack[++aHead] = BVH_NodeInStack(aData.z(), aMetricRgh);
          }
          else
          {
            aNode           = BVH_NodeInStack(aData.z(), aMetricRgh);
            aStack[++aHead] = BVH_NodeInStack(aData.y(), aMetricLft);
          }
        }
        else if (isGoodLft || isGoodRgh)
        {
          aNode = isGoodLft ? BVH_NodeInStack(aData.y(), aMetricLft)
                            : BVH_NodeInStack(aData.z(), aMetricRgh);
        }
      }
      else
      {

        Standard_ASSERT_RAISE(aHead < BVH_Constants_MaxTreeDepth - 1, "Error! BVH stack overflow");
        aNode           = BVH_NodeInStack(aData.y(), aNode.Metric);
        aStack[++aHead] = BVH_NodeInStack(aData.z(), aNode.Metric);
      }
    }
    else
    {

      for (int iN = aData.y(); iN <= aData.z(); ++iN)
      {
        if (Accept(iN, aNode.Metric))
          ++aNbAccepted;

        if (this->Stop())
          return aNbAccepted;
      }
    }

    if (aNode.NodeID == aPrevNode.NodeID)
    {
      if (aHead < 0)
        return aNbAccepted;

      aNode = aStack[aHead--];
      while (this->RejectMetric(aNode.Metric))
      {
        if (aHead < 0)
          return aNbAccepted;
        aNode = aStack[aHead--];
      }
    }

    aPrevNode = aNode;
  }
}

template <class NumType, int Dimension, class BVHSetType, class MetricType>
int BVH_PairTraverse<NumType, Dimension, BVHSetType, MetricType>::Select(
  const opencascade::handle<BVH_Tree<NumType, Dimension>>& theBVH1,
  const opencascade::handle<BVH_Tree<NumType, Dimension>>& theBVH2)
{
  if (theBVH1.IsNull() || theBVH2.IsNull())
    return 0;

  const BVH_Array4i& aBVHNodes1 = theBVH1->NodeInfoBuffer();
  const BVH_Array4i& aBVHNodes2 = theBVH2->NodeInfoBuffer();
  if (aBVHNodes1.empty() || aBVHNodes2.empty())
    return 0;

  const int aMaxNbPairsInStack = 3 * BVH_Constants_MaxTreeDepth;

  BVH_PairNodesInStack aStack[aMaxNbPairsInStack];

  BVH_PairNodesInStack aNode(0, 0);

  BVH_PairNodesInStack aPrevNode = aNode;

  int aHead = -1;

  int aNbAccepted = 0;

  for (;;)
  {
    const BVH_Vec4i& aData1 = aBVHNodes1[aNode.NodeID1];
    const BVH_Vec4i& aData2 = aBVHNodes2[aNode.NodeID2];

    if (aData1.x() != 0 && aData2.x() != 0)
    {

      MetricType aMetric;
      bool       isRejected = RejectNode(theBVH1->MinPoint(aNode.NodeID1),
                                   theBVH1->MaxPoint(aNode.NodeID1),
                                   theBVH2->MinPoint(aNode.NodeID2),
                                   theBVH2->MaxPoint(aNode.NodeID2),
                                   aMetric);

      if (!isRejected)
      {

        for (int iN1 = aData1.y(); iN1 <= aData1.z(); ++iN1)
        {
          for (int iN2 = aData2.y(); iN2 <= aData2.z(); ++iN2)
          {
            if (Accept(iN1, iN2))
              ++aNbAccepted;

            if (this->Stop())
              return aNbAccepted;
          }
        }
      }
    }
    else
    {
      BVH_PairNodesInStack aPairs[4];
      int                  aNbPairs = 0;

      if (aData1.x() == 0 && aData2.x() == 0)
      {

        aPairs[aNbPairs++] = BVH_PairNodesInStack(aData1.y(), aData2.y());
        aPairs[aNbPairs++] = BVH_PairNodesInStack(aData1.y(), aData2.z());
        aPairs[aNbPairs++] = BVH_PairNodesInStack(aData1.z(), aData2.y());
        aPairs[aNbPairs++] = BVH_PairNodesInStack(aData1.z(), aData2.z());
      }
      else if (aData1.x() == 0)
      {

        aPairs[aNbPairs++] = BVH_PairNodesInStack(aData1.y(), aNode.NodeID2);
        aPairs[aNbPairs++] = BVH_PairNodesInStack(aData1.z(), aNode.NodeID2);
      }
      else if (aData2.x() == 0)
      {

        aPairs[aNbPairs++] = BVH_PairNodesInStack(aNode.NodeID1, aData2.y());
        aPairs[aNbPairs++] = BVH_PairNodesInStack(aNode.NodeID1, aData2.z());
      }

      BVH_PairNodesInStack aKeptPairs[4];
      int                  aNbKept = 0;

      for (int iPair = 0; iPair < aNbPairs; ++iPair)
      {
        const bool isPairRejected = RejectNode(theBVH1->MinPoint(aPairs[iPair].NodeID1),
                                               theBVH1->MaxPoint(aPairs[iPair].NodeID1),
                                               theBVH2->MinPoint(aPairs[iPair].NodeID2),
                                               theBVH2->MaxPoint(aPairs[iPair].NodeID2),
                                               aPairs[iPair].Metric);
        if (!isPairRejected)
        {

          int iSort = aNbKept;
          while (iSort > 0
                 && this->IsMetricBetter(aPairs[iPair].Metric, aKeptPairs[iSort - 1].Metric))
          {
            aKeptPairs[iSort] = aKeptPairs[iSort - 1];
            --iSort;
          }
          aKeptPairs[iSort] = aPairs[iPair];
          ++aNbKept;
        }
      }

      if (aNbKept > 0)
      {
        aNode = aKeptPairs[0];

        for (int iPair = 1; iPair < aNbKept; ++iPair)
        {
          Standard_ASSERT_RAISE(aHead < aMaxNbPairsInStack - 1, "Error! BVH pair stack overflow");
          aStack[++aHead] = aKeptPairs[iPair];
        }
      }
    }

    if (aNode.NodeID1 == aPrevNode.NodeID1 && aNode.NodeID2 == aPrevNode.NodeID2)
    {

      if (aHead < 0)
        return aNbAccepted;

      aNode = aStack[aHead--];
      while (this->RejectMetric(aNode.Metric))
      {
        if (aHead < 0)
          return aNbAccepted;
        aNode = aStack[aHead--];
      }
    }

    aPrevNode = aNode;
  }
}
