#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_ElementarySurface.hpp>
class TCollection_HAsciiString;
class StepGeom_Axis2Placement3d;

class StepGeom_CylindricalSurface : public StepGeom_ElementarySurface
{

public:
  //! Returns a CylindricalSurface
  Standard_EXPORT StepGeom_CylindricalSurface();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&  aName,
                            const occ::handle<StepGeom_Axis2Placement3d>& aPosition,
                            const double                                  aRadius);

  Standard_EXPORT void SetRadius(const double aRadius);

  Standard_EXPORT double Radius() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_CylindricalSurface, StepGeom_ElementarySurface)

private:
  double radius;
};

