#pragma once

#include <BVH_Traverse.hpp>

template <class NumType, int Dimension, class ObjectType, class BVHSetType>
class BVH_Distance : public BVH_Traverse<NumType, Dimension, BVHSetType, NumType>
{
public:
  BVH_Distance()
      : BVH_Traverse<NumType, Dimension, BVHSetType, NumType>(),
        myDistance(std::numeric_limits<NumType>::max()),
        myIsDone(false)
  {
  }

public:
  void SetObject(const ObjectType& theObject) { myObject = theObject; }

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

  bool RejectMetric(const NumType& theMetric) const override { return theMetric > myDistance; }

  bool Stop() const override { return myDistance == static_cast<NumType>(0); }

protected:
  NumType    myDistance;
  bool       myIsDone;
  ObjectType myObject;
};
