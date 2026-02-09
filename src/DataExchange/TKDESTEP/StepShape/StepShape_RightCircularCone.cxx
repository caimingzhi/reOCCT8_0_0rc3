

#include <StepGeom_Axis1Placement.hpp>
#include <StepShape_RightCircularCone.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_RightCircularCone, StepGeom_GeometricRepresentationItem)

StepShape_RightCircularCone::StepShape_RightCircularCone() = default;

void StepShape_RightCircularCone::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                       const occ::handle<StepGeom_Axis1Placement>&  aPosition,
                                       const double                                 aHeight,
                                       const double                                 aRadius,
                                       const double                                 aSemiAngle)
{

  position  = aPosition;
  height    = aHeight;
  radius    = aRadius;
  semiAngle = aSemiAngle;

  StepRepr_RepresentationItem::Init(aName);
}

void StepShape_RightCircularCone::SetPosition(const occ::handle<StepGeom_Axis1Placement>& aPosition)
{
  position = aPosition;
}

occ::handle<StepGeom_Axis1Placement> StepShape_RightCircularCone::Position() const
{
  return position;
}

void StepShape_RightCircularCone::SetHeight(const double aHeight)
{
  height = aHeight;
}

double StepShape_RightCircularCone::Height() const
{
  return height;
}

void StepShape_RightCircularCone::SetRadius(const double aRadius)
{
  radius = aRadius;
}

double StepShape_RightCircularCone::Radius() const
{
  return radius;
}

void StepShape_RightCircularCone::SetSemiAngle(const double aSemiAngle)
{
  semiAngle = aSemiAngle;
}

double StepShape_RightCircularCone::SemiAngle() const
{
  return semiAngle;
}
