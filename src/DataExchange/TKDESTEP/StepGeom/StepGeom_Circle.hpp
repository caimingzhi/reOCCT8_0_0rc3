#pragma once

#include <Standard.hpp>

#include <Standard_Real.hpp>
#include <StepGeom_Conic.hpp>
class TCollection_HAsciiString;
class StepGeom_Axis2Placement;

class StepGeom_Circle : public StepGeom_Conic
{

public:
  //! Returns a Circle
  Standard_EXPORT StepGeom_Circle();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const StepGeom_Axis2Placement&               aPosition,
                            const double                                 aRadius);

  Standard_EXPORT void SetRadius(const double aRadius);

  Standard_EXPORT double Radius() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_Circle, StepGeom_Conic)

private:
  double radius;
};
