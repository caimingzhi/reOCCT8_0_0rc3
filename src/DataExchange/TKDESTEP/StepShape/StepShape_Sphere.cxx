

#include <StepGeom_Point.hpp>
#include <StepShape_Sphere.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_Sphere, StepGeom_GeometricRepresentationItem)

StepShape_Sphere::StepShape_Sphere() = default;

void StepShape_Sphere::Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const double                                 aRadius,
                            const occ::handle<StepGeom_Point>&           aCentre)
{

  radius = aRadius;
  centre = aCentre;

  StepRepr_RepresentationItem::Init(aName);
}

void StepShape_Sphere::SetRadius(const double aRadius)
{
  radius = aRadius;
}

double StepShape_Sphere::Radius() const
{
  return radius;
}

void StepShape_Sphere::SetCentre(const occ::handle<StepGeom_Point>& aCentre)
{
  centre = aCentre;
}

occ::handle<StepGeom_Point> StepShape_Sphere::Centre() const
{
  return centre;
}
