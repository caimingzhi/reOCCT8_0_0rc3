#pragma once

#include <BVH_Box.hpp>
#include <BVH_Tree.hpp>

//! The classes implement the traverse of the BVH tree.
//!
//! There are two traverse methods implemented:
//! - Traverse of the single tree
//! - Parallel traverse of two trees
//!
//! To perform Selection of the elements from BVH_Tree using
//! the traverse methods implemented here it is
//! required to define Acceptance/Rejection rules in the
//! following methods:
//! - *RejectNode* - Node rejection by its bounding box.
//!   It is applied to both inner and outer nodes of the BVH tree.
//!   Optionally, the method should compute the metric for the node
//!   which will allow performing traverse faster by descending by the
//!   best branches.
//! - *Accept* - Element acceptance. It takes the index of the element
//!   of BVH tree. The access to the element itself should be performed
//!   through the set on which BVH is built.
//!   The *Accept* method implements the leaf node operation and usually
//!   defines the logic of the whole operation.
//! - *IsMetricBetter* - Compares the metrics of the nodes and returns
//!   true if the left metric is better than the right one.
//! - *RejectMetric* - Node rejection by the metric. It should compare
//!   the metric of the node with the global one and return true
//!   if the global metric is better than the given one.
//! - *Stop* - implements conditions to stop the tree descend if the necessary
//!   elements are already found.
//!
//! The selector of a single tree has an extra method which allows
//! accepting the whole branches without any further checks
//! (e.g. full inclusion test):
//! - *AcceptMetric* - basing on the metric of the node decides if the
//!   node may be accepted without any further checks.
//!
//! Two ways of selection are possible:
//! 1. Set the BVH set containing the tree and use the method Select()
//!    which allows using common interface for setting the BVH Set for accessing
//!    the BVH tree and elements in the Accept method.
//! 2. Keep the BVHSetType void, do not set the BVH set and use the
//!    method Select (const BVH_Tree<>&) which allows performing selection
//!    on the arbitrary BVH tree.
//!
//! Here is the example of usage of the traverse to find the point-triangulation
//! minimal distance.
//! ~~~~
//! // Structure to contain points of the triangle
//! struct Triangle
//! {
//!   Triangle() {}
//!   Triangle(const BVH_Vec3d& theNode1,
//!            const BVH_Vec3d& theNode2,
//!            const BVH_Vec3d& theNode3)
//!     : Node1 (theNode1), Node2 (theNode2), Node3 (theNode3)
//!   {}
//!
//!   BVH_Vec3d Node1;
//!   BVH_Vec3d Node2;
//!   BVH_Vec3d Node3;
//! };
//!
//! // Selector for min point-triangulation distance
//! class BVH_PointTriangulationSqDist :
//!   public BVH_Distance<double, 3, BVH_Vec3d, BVH_BoxSet<double, 3, Triangle>>
//! {
//! public:
//!
//!   // Computes the distance from the point to bounding box
//!   virtual bool RejectNode (const BVH_Vec3d& theCMin,
//!                                        const BVH_Vec3d& theCMax,
//!                                        double& theDistance) const override
//!   {
//!     theDistance = BVH_Tools<double, 3>::PointBoxSquareDistance (myObject, theCMin,
//!     theCMax); return RejectMetric (theDistance);
//!   }
//!
//!   // Computes the distance from the point to triangle
//!   virtual bool Accept (const int theIndex,
//!                                    const double&) override
//!   {
//!     const Triangle& aTri = myBVHSet->Element (theIndex);
//!     double aDist = BVH_Tools<double, 3>::PointTriangleSquareDistance (myObject,
//!     aTri.Node1, aTri.Node2, aTri.Node3); if (aDist < myDistance)
//!     {
//!       myDistance = aDist;
//!       return true;
//!     }
//!     return false;
//!   }
//! };
//!
//! // Point to which the distance is required
//! BVH_Vec3d aPoint = ...;
//! // BVH Set containing triangulation
//! opencascade::handle<BVH_BoxSet<double, 3, Triangle>> aTriangulationSet = ...;
//!
//! BVH_PointTriangulationSqDist aDistTool;
//! aDistTool.SetObject (aPoint);
//! aDistTool.SetBVHSet (aTriangulationSet.get());
//! aDistTool.ComputeDistance();
//! if (aDistTool.IsDone())
//! {
//!   double aPointTriSqDist = aDistTool.Distance();
//! }
//!
//! ~~~~
//!

//! Abstract class implementing the base Traverse interface
//! required for selection of the elements from BVH tree.
//!
//! \tparam MetricType Type of metric to perform more optimal tree descend
template <class MetricType>
class BVH_BaseTraverse
{
public: //! @name Metrics comparison for choosing the best branch
  //! Compares the two metrics and chooses the best one.
  //! Returns true if the first metric is better than the second,
  //! false otherwise.
  virtual bool IsMetricBetter(const MetricType&, const MetricType&) const
  {
    // Keep the left to right tree descend by default
    return true;
  }

public: //! @name Rejection of the node by metric
  //! Rejects the node by the metric
  virtual bool RejectMetric(const MetricType&) const
  {
    // Do not reject any nodes by metric by default
    return false;
  }

public: //! @name Condition to stop the descend
  //! Returns the flag controlling the tree descend.
  //! Returns true if the tree descend should be stopped.
  virtual bool Stop() const
  {
    // Do not stop tree descend by default
    return false;
  }

protected: //! @name Constructors
  //! Constructor
  BVH_BaseTraverse() {}

  //! Destructor
  virtual ~BVH_BaseTraverse() = default;
};

//! Abstract class implementing the traverse of the single binary tree.
//! Selection of the data from the tree is performed by the
//! rules defined in the Accept/Reject methods.
//! See description of the required methods in the comments above.
//!
//! \tparam NumType Numeric data type
//! \tparam Dimension Vector dimension
//! \tparam BVHSetType Type of set containing the BVH tree (required to access the elements by the
//! index) \tparam MetricType Type of metric to perform more optimal tree descend
template <class NumType, int Dimension, class BVHSetType = void, class MetricType = NumType>
class BVH_Traverse : public BVH_BaseTraverse<MetricType>
{
public: //! @name public types
  typedef typename BVH_Box<NumType, Dimension>::BVH_VecNt BVH_VecNt;

public: //! @name Constructor
  //! Constructor
  BVH_Traverse()
      : BVH_BaseTraverse<MetricType>(),
        myBVHSet(nullptr)
  {
  }

public: //! @name Setting the set to access the elements and BVH tree
  //! Sets the BVH Set containing the BVH tree
  void SetBVHSet(BVHSetType* theBVHSet) { myBVHSet = theBVHSet; }

public: //! @name Rules for Accept/Reject
  //! Basing on the given metric, checks if the whole branch may be
  //! accepted without any further checks.
  //! Returns true if the metric is accepted, false otherwise.
  virtual bool AcceptMetric(const MetricType&) const
  {
    // Do not accept the whole branch by default
    return false;
  }

  //! Rejection of the node by bounding box.
  //! Metric is computed to choose the best branch.
  //! Returns true if the node should be rejected, false otherwise.
  virtual bool RejectNode(const BVH_VecNt& theCornerMin,
                          const BVH_VecNt& theCornerMax,
                          MetricType&      theMetric) const = 0;

  //! Leaf element acceptance.
  //! Metric of the parent leaf-node is passed to avoid the check on the
  //! element and accept it unconditionally.
  //! Returns true if the element has been accepted, false otherwise.
  virtual bool Accept(const int theIndex, const MetricType& theMetric) = 0;

public: //! @name Selection
  //! Selection of the elements from the BVH tree by the
  //! rules defined in Accept/Reject methods.
  //! The method requires the BVHSet containing BVH tree to be set.
  //! Returns the number of accepted elements.
  int Select()
  {
    if (myBVHSet)
    {
      const opencascade::handle<BVH_Tree<NumType, Dimension>>& aBVH = myBVHSet->BVH();
      return Select(aBVH);
    }
    return 0;
  }

  //! Performs selection of the elements from the BVH tree by the
  //! rules defined in Accept/Reject methods.
  //! Returns the number of accepted elements.
  int Select(const opencascade::handle<BVH_Tree<NumType, Dimension>>& theBVH);

protected: //! @name Internal structures
  //! Auxiliary structure for keeping the nodes to process
  struct BVH_NodeInStack
  {
    //! Constructor
    constexpr BVH_NodeInStack(const int         theNodeID = 0,
                              const MetricType& theMetric = MetricType()) noexcept
        : NodeID(theNodeID),
          Metric(theMetric)
    {
    }

    // Fields
    int        NodeID; //!< Id of the node in the BVH tree
    MetricType Metric; //!< Metric computed for the node
  };

protected: //! @name Fields
  BVHSetType* myBVHSet;
};

//! Abstract class implementing the parallel traverse of two binary trees.
//! Selection of the data from the trees is performed by the
//! rules defined in the Accept/Reject methods.
//! See description of the required methods in the comments above.
//!
//! \tparam NumType Numeric data type
//! \tparam Dimension Vector dimension
//! \tparam BVHSetType Type of set containing the BVH tree (required to access the elements by the
//! index) \tparam MetricType Type of metric to perform more optimal tree descend
template <class NumType, int Dimension, class BVHSetType = void, class MetricType = NumType>
class BVH_PairTraverse : public BVH_BaseTraverse<MetricType>
{
public: //! @name public types
  typedef typename BVH_Box<NumType, Dimension>::BVH_VecNt BVH_VecNt;

public: //! @name Constructor
  //! Constructor
  BVH_PairTraverse()
      : BVH_BaseTraverse<MetricType>(),
        myBVHSet1(nullptr),
        myBVHSet2(nullptr)
  {
  }

public: //! @name Setting the sets to access the elements and BVH trees
  //! Sets the BVH Sets containing the BVH trees
  void SetBVHSets(BVHSetType* theBVHSet1, BVHSetType* theBVHSet2)
  {
    myBVHSet1 = theBVHSet1;
    myBVHSet2 = theBVHSet2;
  }

public: //! @name Rules for Accept/Reject
  //! Rejection of the pair of nodes by bounding boxes.
  //! Metric is computed to choose the best branch.
  //! Returns true if the pair of nodes should be rejected, false otherwise.
  virtual bool RejectNode(const BVH_VecNt& theCornerMin1,
                          const BVH_VecNt& theCornerMax1,
                          const BVH_VecNt& theCornerMin2,
                          const BVH_VecNt& theCornerMax2,
                          MetricType&      theMetric) const = 0;

  //! Leaf element acceptance.
  //! Returns true if the pair of elements is accepted, false otherwise.
  virtual bool Accept(const int theIndex1, const int theIndex2) = 0;

public: //! @name Selection
  //! Selection of the pairs of elements of two BVH trees by the
  //! rules defined in Accept/Reject methods.
  //! The method requires the BVHSets containing BVH trees to be set.
  //! Returns the number of accepted pairs of elements.
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

  //! Performs selection of the elements from two BVH trees by the
  //! rules defined in Accept/Reject methods.
  //! Returns the number of accepted pairs of elements.
  int Select(const opencascade::handle<BVH_Tree<NumType, Dimension>>& theBVH1,
             const opencascade::handle<BVH_Tree<NumType, Dimension>>& theBVH2);

protected: //! @name Internal structures
  //! Auxiliary structure for keeping the pair of nodes to process
  struct BVH_PairNodesInStack
  {
    //! Constructor
    constexpr BVH_PairNodesInStack(const int         theNodeID1 = 0,
                                   const int         theNodeID2 = 0,
                                   const MetricType& theMetric  = MetricType()) noexcept
        : NodeID1(theNodeID1),
          NodeID2(theNodeID2),
          Metric(theMetric)
    {
    }

    // Fields
    int        NodeID1; //!< Id of the node in the first BVH tree
    int        NodeID2; //!< Id of the node in the second BVH tree
    MetricType Metric;  //!< Metric computed for the pair of nodes
  };

protected: //! @name Fields
  BVHSetType* myBVHSet1;
  BVHSetType* myBVHSet2;
};

#include <Standard_Assert.hpp>

//=================================================================================================

template <class NumType, int Dimension, class BVHSetType, class MetricType>
int BVH_Traverse<NumType, Dimension, BVHSetType, MetricType>::Select(
  const opencascade::handle<BVH_Tree<NumType, Dimension>>& theBVH)
{
  if (theBVH.IsNull())
    return 0;

  const BVH_Array4i& aBVHNodes = theBVH->NodeInfoBuffer();
  if (aBVHNodes.empty())
    return 0;

  // Create stack
  BVH_NodeInStack aStack[BVH_Constants_MaxTreeDepth];

  // clang-format off
  BVH_NodeInStack aNode (0);         // Currently processed node, starting with the root node
  // clang-format on
  BVH_NodeInStack aPrevNode = aNode; // Previously processed node

  int aHead       = -1; // End of the stack
  int aNbAccepted = 0;  // Counter for accepted elements

  for (;;)
  {
    const BVH_Vec4i& aData = aBVHNodes[aNode.NodeID];

    if (aData.x() == 0)
    {
      // Inner node:
      // - check the metric of the node
      // - test the children of the node

      if (!this->AcceptMetric(aNode.Metric))
      {
        // Test the left branch
        MetricType aMetricLft;
        bool       isGoodLft =
          !RejectNode(theBVH->MinPoint(aData.y()), theBVH->MaxPoint(aData.y()), aMetricLft);
        if (this->Stop())
          return aNbAccepted;

        // Test the right branch
        MetricType aMetricRgh;
        bool       isGoodRgh =
          !RejectNode(theBVH->MinPoint(aData.z()), theBVH->MaxPoint(aData.z()), aMetricRgh);
        if (this->Stop())
          return aNbAccepted;

        if (isGoodLft && isGoodRgh)
        {
          // Chose the branch with the best metric to be processed next,
          // put the other branch in the stack
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
        // Both children will be accepted
        // Take one for processing, put the other into stack
        Standard_ASSERT_RAISE(aHead < BVH_Constants_MaxTreeDepth - 1, "Error! BVH stack overflow");
        aNode           = BVH_NodeInStack(aData.y(), aNode.Metric);
        aStack[++aHead] = BVH_NodeInStack(aData.z(), aNode.Metric);
      }
    }
    else
    {
      // Leaf node - apply the leaf node operation to each element
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

      // Remove the nodes with bad metric from the stack
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

//=================================================================================================

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

  // On each iteration we can add max four new pairs of nodes to process.
  // One of these pairs goes directly to processing, while others
  // are put in the stack. So the max number of pairs in the stack is
  // the max tree depth multiplied by 3.
  const int aMaxNbPairsInStack = 3 * BVH_Constants_MaxTreeDepth;

  // Stack of pairs of nodes to process
  BVH_PairNodesInStack aStack[aMaxNbPairsInStack];

  // Currently processed pair, starting with the root nodes
  BVH_PairNodesInStack aNode(0, 0);
  // Previously processed pair
  BVH_PairNodesInStack aPrevNode = aNode;
  // End of the stack
  int aHead = -1;
  // Counter for accepted elements
  int aNbAccepted = 0;

  for (;;)
  {
    const BVH_Vec4i& aData1 = aBVHNodes1[aNode.NodeID1];
    const BVH_Vec4i& aData2 = aBVHNodes2[aNode.NodeID2];

    if (aData1.x() != 0 && aData2.x() != 0)
    {
      // Outer/Outer - both nodes are leaves
      // Check if the leaf node bounding boxes overlap before testing elements
      MetricType aMetric;
      bool       isRejected = RejectNode(theBVH1->MinPoint(aNode.NodeID1),
                                   theBVH1->MaxPoint(aNode.NodeID1),
                                   theBVH2->MinPoint(aNode.NodeID2),
                                   theBVH2->MaxPoint(aNode.NodeID2),
                                   aMetric);

      if (!isRejected)
      {
        // Bounding boxes overlap, test all element pairs
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
        // Inner/Inner
        aPairs[aNbPairs++] = BVH_PairNodesInStack(aData1.y(), aData2.y());
        aPairs[aNbPairs++] = BVH_PairNodesInStack(aData1.y(), aData2.z());
        aPairs[aNbPairs++] = BVH_PairNodesInStack(aData1.z(), aData2.y());
        aPairs[aNbPairs++] = BVH_PairNodesInStack(aData1.z(), aData2.z());
      }
      else if (aData1.x() == 0)
      {
        // Inner/Outer
        aPairs[aNbPairs++] = BVH_PairNodesInStack(aData1.y(), aNode.NodeID2);
        aPairs[aNbPairs++] = BVH_PairNodesInStack(aData1.z(), aNode.NodeID2);
      }
      else if (aData2.x() == 0)
      {
        // Outer/Inner
        aPairs[aNbPairs++] = BVH_PairNodesInStack(aNode.NodeID1, aData2.y());
        aPairs[aNbPairs++] = BVH_PairNodesInStack(aNode.NodeID1, aData2.z());
      }

      BVH_PairNodesInStack aKeptPairs[4];
      int                  aNbKept = 0;
      // Compute metrics for the nodes
      for (int iPair = 0; iPair < aNbPairs; ++iPair)
      {
        const bool isPairRejected = RejectNode(theBVH1->MinPoint(aPairs[iPair].NodeID1),
                                               theBVH1->MaxPoint(aPairs[iPair].NodeID1),
                                               theBVH2->MinPoint(aPairs[iPair].NodeID2),
                                               theBVH2->MaxPoint(aPairs[iPair].NodeID2),
                                               aPairs[iPair].Metric);
        if (!isPairRejected)
        {
          // Put the item into the sorted array of pairs
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
      // No pairs to add
      if (aHead < 0)
        return aNbAccepted;

      // Remove the pairs of nodes with bad metric from the stack
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
