

#include <StepGeom_Direction.hpp>
#include <StepGeom_OffsetCurve3d.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_OffsetCurve3d, StepGeom_Curve)

StepGeom_OffsetCurve3d::StepGeom_OffsetCurve3d() = default;

void StepGeom_OffsetCurve3d::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                  const occ::handle<StepGeom_Curve>&           aBasisCurve,
                                  const double                                 aDistance,
                                  const StepData_Logical                       aSelfIntersect,
                                  const occ::handle<StepGeom_Direction>&       aRefDirection)
{

  basisCurve    = aBasisCurve;
  distance      = aDistance;
  selfIntersect = aSelfIntersect;
  refDirection  = aRefDirection;

  StepRepr_RepresentationItem::Init(aName);
}

void StepGeom_OffsetCurve3d::SetBasisCurve(const occ::handle<StepGeom_Curve>& aBasisCurve)
{
  basisCurve = aBasisCurve;
}

occ::handle<StepGeom_Curve> StepGeom_OffsetCurve3d::BasisCurve() const
{
  return basisCurve;
}

void StepGeom_OffsetCurve3d::SetDistance(const double aDistance)
{
  distance = aDistance;
}

double StepGeom_OffsetCurve3d::Distance() const
{
  return distance;
}

void StepGeom_OffsetCurve3d::SetSelfIntersect(const StepData_Logical aSelfIntersect)
{
  selfIntersect = aSelfIntersect;
}

StepData_Logical StepGeom_OffsetCurve3d::SelfIntersect() const
{
  return selfIntersect;
}

void StepGeom_OffsetCurve3d::SetRefDirection(const occ::handle<StepGeom_Direction>& aRefDirection)
{
  refDirection = aRefDirection;
}

occ::handle<StepGeom_Direction> StepGeom_OffsetCurve3d::RefDirection() const
{
  return refDirection;
}
