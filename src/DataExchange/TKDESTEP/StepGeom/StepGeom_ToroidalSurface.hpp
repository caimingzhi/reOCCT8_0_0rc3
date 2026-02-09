#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_ElementarySurface.hpp>
class TCollection_HAsciiString;
class StepGeom_Axis2Placement3d;

class StepGeom_ToroidalSurface : public StepGeom_ElementarySurface
{

public:
  Standard_EXPORT StepGeom_ToroidalSurface();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&  aName,
                            const occ::handle<StepGeom_Axis2Placement3d>& aPosition,
                            const double                                  aMajorRadius,
                            const double                                  aMinorRadius);

  Standard_EXPORT void SetMajorRadius(const double aMajorRadius);

  Standard_EXPORT double MajorRadius() const;

  Standard_EXPORT void SetMinorRadius(const double aMinorRadius);

  Standard_EXPORT double MinorRadius() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_ToroidalSurface, StepGeom_ElementarySurface)

private:
  double majorRadius;
  double minorRadius;
};
