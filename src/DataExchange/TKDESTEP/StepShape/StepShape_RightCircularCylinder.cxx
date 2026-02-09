

#include <StepGeom_Axis1Placement.hpp>
#include <StepShape_RightCircularCylinder.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_RightCircularCylinder, StepGeom_GeometricRepresentationItem)

StepShape_RightCircularCylinder::StepShape_RightCircularCylinder() = default;

void StepShape_RightCircularCylinder::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                           const occ::handle<StepGeom_Axis1Placement>&  aPosition,
                                           const double                                 aHeight,
                                           const double                                 aRadius)
{

  position = aPosition;
  height   = aHeight;
  radius   = aRadius;

  StepRepr_RepresentationItem::Init(aName);
}

void StepShape_RightCircularCylinder::SetPosition(
  const occ::handle<StepGeom_Axis1Placement>& aPosition)
{
  position = aPosition;
}

occ::handle<StepGeom_Axis1Placement> StepShape_RightCircularCylinder::Position() const
{
  return position;
}

void StepShape_RightCircularCylinder::SetHeight(const double aHeight)
{
  height = aHeight;
}

double StepShape_RightCircularCylinder::Height() const
{
  return height;
}

void StepShape_RightCircularCylinder::SetRadius(const double aRadius)
{
  radius = aRadius;
}

double StepShape_RightCircularCylinder::Radius() const
{
  return radius;
}
