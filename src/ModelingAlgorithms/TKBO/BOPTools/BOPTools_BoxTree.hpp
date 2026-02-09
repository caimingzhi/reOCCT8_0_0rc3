#pragma once

#include <BOPTools_BoxSelector.hpp>

#include <BVH_Traverse.hpp>
#include <BVH_BoxSet.hpp>

#include <Standard_Integer.hpp>
#include <algorithm>

template <int Dimension>
class BOPTools_PairSelector
    : public BVH_PairTraverse<double, Dimension, BVH_BoxSet<double, Dimension, int>>
{
public:
  struct PairIDs
  {
    PairIDs(const int theId1 = -1, const int theId2 = -1)
        : ID1(theId1),
          ID2(theId2)
    {
    }

    bool operator<(const PairIDs& theOther) const
    {
      return ID1 < theOther.ID1 || (ID1 == theOther.ID1 && ID2 < theOther.ID2);
    }

    int ID1;
    int ID2;
  };

  typedef typename BVH::VectorType<double, Dimension>::Type BVH_VecNd;

public:
  BOPTools_PairSelector()
      : mySameBVHs(false)
  {
  }

public:
  void Clear() { myPairs.clear(); }

  void Sort() { std::sort(myPairs.begin(), myPairs.end()); }

  void SetSame(const bool theIsSame) { mySameBVHs = theIsSame; }

  const std::vector<PairIDs>& Pairs() const { return myPairs; }

public:
  bool RejectNode(const BVH_VecNd& theCMin1,
                  const BVH_VecNd& theCMax1,
                  const BVH_VecNd& theCMin2,
                  const BVH_VecNd& theCMax2,
                  double&) const override
  {
    return BVH_Box<double, 3>(theCMin1, theCMax1).IsOut(theCMin2, theCMax2);
  }

  bool RejectElement(const int theID1, const int theID2)
  {
    return (mySameBVHs && theID1 >= theID2)
           || this->myBVHSet1->Box(theID1).IsOut(this->myBVHSet2->Box(theID2));
  }

  bool Accept(const int theID1, const int theID2) override
  {
    if (!RejectElement(theID1, theID2))
    {
      myPairs.push_back(
        PairIDs(this->myBVHSet1->Element(theID1), this->myBVHSet2->Element(theID2)));
      return true;
    }
    return false;
  }

protected:
  std::vector<PairIDs> myPairs;
  bool                 mySameBVHs;
};

#include <Standard_Integer.hpp>
#include <BVH_LinearBuilder.hpp>

template <class NumType, int Dimension, class DataType>
class BOPTools_BoxSet : public BVH_BoxSet<NumType, Dimension, DataType>
{
public:
  BOPTools_BoxSet(const opencascade::handle<BVH_Builder<NumType, Dimension>>& theBuilder = nullptr)
      : BVH_BoxSet<NumType, Dimension, DataType>(
          theBuilder.IsNull() ? new BVH_LinearBuilder<NumType, Dimension>() : theBuilder)
  {
  }
};

typedef BOPTools_BoxSet<double, 2, int> BOPTools_Box2dTree;
typedef BOPTools_BoxSelector<2>         BOPTools_Box2dTreeSelector;
typedef BOPTools_PairSelector<2>        BOPTools_Box2dPairSelector;

typedef BOPTools_BoxSet<double, 3, int> BOPTools_BoxTree;
typedef BOPTools_BoxSelector<3>         BOPTools_BoxTreeSelector;
typedef BOPTools_PairSelector<3>        BOPTools_BoxPairSelector;
