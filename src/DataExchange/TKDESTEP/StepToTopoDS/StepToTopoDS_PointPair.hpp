#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class StepGeom_CartesianPoint;

//! Stores a pair of Points from step
class StepToTopoDS_PointPair
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepToTopoDS_PointPair(const occ::handle<StepGeom_CartesianPoint>& P1,
                                         const occ::handle<StepGeom_CartesianPoint>& P2);

  const occ::handle<StepGeom_CartesianPoint>& GetPoint1() const { return myP1; }

  const occ::handle<StepGeom_CartesianPoint>& GetPoint2() const { return myP2; }

  bool operator==(const StepToTopoDS_PointPair& thePointPair) const
  {
    return (((myP1 == thePointPair.myP1) && (myP2 == thePointPair.myP2))
            || ((myP1 == thePointPair.myP2) && (myP2 == thePointPair.myP1)));
  }

private:
  occ::handle<StepGeom_CartesianPoint> myP1;
  occ::handle<StepGeom_CartesianPoint> myP2;
};

namespace std
{
template <>
struct hash<StepToTopoDS_PointPair>
{
  size_t operator()(const StepToTopoDS_PointPair& thePointPair) const noexcept
  {
    // Combine two int values into a single hash value.
    size_t aCombination[2];
    aCombination[0] = std::hash<occ::handle<StepGeom_CartesianPoint>>{}(thePointPair.GetPoint1());
    aCombination[1] = std::hash<occ::handle<StepGeom_CartesianPoint>>{}(thePointPair.GetPoint2());
    if (aCombination[0] > aCombination[1])
    {
      std::swap(aCombination[0], aCombination[1]);
    }
    return opencascade::hashBytes(aCombination, sizeof(aCombination));
  }
};
} // namespace std

