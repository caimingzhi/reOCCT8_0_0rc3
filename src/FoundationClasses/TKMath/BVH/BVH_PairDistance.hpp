#pragma once

#include <BVH_Traverse.hpp>
#include <BVH_Tools.hpp>

template <class NumType, int Dimension, class BVHSetType>
class BVH_PairDistance : public BVH_PairTraverse<NumType, Dimension, BVHSetType, NumType>
{
public:
  typedef typename BVH_Tools<NumType, Dimension>::BVH_VecNt BVH_VecNt;

public:
  BVH_PairDistance()
      : BVH_PairTraverse<NumType, Dimension, BVHSetType, NumType>(),
        myDistance(std::numeric_limits<NumType>::max()),
        myIsDone(false)
  {
  }

public:
  NumType ComputeDistance()
  {
    myIsDone = this->Select() > 0;
    return myDistance;
  }

public:
  bool IsDone() const { return myIsDone; }

  NumType Distance() const { return myDistance; }

public:
  bool IsMetricBetter(const NumType& theLeft, const NumType& theRight) const override
  {
    return theLeft < theRight;
  }

  bool RejectNode(const BVH_VecNt& theCornerMin1,
                  const BVH_VecNt& theCornerMax1,
                  const BVH_VecNt& theCornerMin2,
                  const BVH_VecNt& theCornerMax2,
                  NumType&         theMetric) const override
  {
    theMetric = BVH_Tools<NumType, Dimension>::BoxBoxSquareDistance(theCornerMin1,
                                                                    theCornerMax1,
                                                                    theCornerMin2,
                                                                    theCornerMax2);
    return theMetric > myDistance;
  }

  bool RejectMetric(const NumType& theMetric) const override { return theMetric > myDistance; }

  bool Stop() const override { return myDistance == static_cast<NumType>(0); }

protected:
  NumType myDistance;
  bool    myIsDone;
};
