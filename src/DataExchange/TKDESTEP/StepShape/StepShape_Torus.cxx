

#include <StepGeom_Axis1Placement.hpp>
#include <StepShape_Torus.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_Torus, StepGeom_GeometricRepresentationItem)

StepShape_Torus::StepShape_Torus() = default;

void StepShape_Torus::Init(const occ::handle<TCollection_HAsciiString>& aName,
                           const occ::handle<StepGeom_Axis1Placement>&  aPosition,
                           const double                                 aMajorRadius,
                           const double                                 aMinorRadius)
{

  position    = aPosition;
  majorRadius = aMajorRadius;
  minorRadius = aMinorRadius;

  StepRepr_RepresentationItem::Init(aName);
}

void StepShape_Torus::SetPosition(const occ::handle<StepGeom_Axis1Placement>& aPosition)
{
  position = aPosition;
}

occ::handle<StepGeom_Axis1Placement> StepShape_Torus::Position() const
{
  return position;
}

void StepShape_Torus::SetMajorRadius(const double aMajorRadius)
{
  majorRadius = aMajorRadius;
}

double StepShape_Torus::MajorRadius() const
{
  return majorRadius;
}

void StepShape_Torus::SetMinorRadius(const double aMinorRadius)
{
  minorRadius = aMinorRadius;
}

double StepShape_Torus::MinorRadius() const
{
  return minorRadius;
}
