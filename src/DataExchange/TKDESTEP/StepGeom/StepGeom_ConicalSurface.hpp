#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_ElementarySurface.hpp>
class TCollection_HAsciiString;
class StepGeom_Axis2Placement3d;

class StepGeom_ConicalSurface : public StepGeom_ElementarySurface
{

public:
  Standard_EXPORT StepGeom_ConicalSurface();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&  aName,
                            const occ::handle<StepGeom_Axis2Placement3d>& aPosition,
                            const double                                  aRadius,
                            const double                                  aSemiAngle);

  Standard_EXPORT void SetRadius(const double aRadius);

  Standard_EXPORT double Radius() const;

  Standard_EXPORT void SetSemiAngle(const double aSemiAngle);

  Standard_EXPORT double SemiAngle() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_ConicalSurface, StepGeom_ElementarySurface)

private:
  double radius;
  double semiAngle;
};
