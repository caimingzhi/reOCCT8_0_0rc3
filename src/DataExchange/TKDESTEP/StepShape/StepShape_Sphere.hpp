#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_GeometricRepresentationItem.hpp>
class StepGeom_Point;
class TCollection_HAsciiString;

class StepShape_Sphere : public StepGeom_GeometricRepresentationItem
{

public:
  //! Returns a Sphere
  Standard_EXPORT StepShape_Sphere();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const double                                 aRadius,
                            const occ::handle<StepGeom_Point>&           aCentre);

  Standard_EXPORT void SetRadius(const double aRadius);

  Standard_EXPORT double Radius() const;

  Standard_EXPORT void SetCentre(const occ::handle<StepGeom_Point>& aCentre);

  Standard_EXPORT occ::handle<StepGeom_Point> Centre() const;

  DEFINE_STANDARD_RTTIEXT(StepShape_Sphere, StepGeom_GeometricRepresentationItem)

private:
  double                      radius;
  occ::handle<StepGeom_Point> centre;
};
