#pragma once

#include <Standard.hpp>

#include <Standard_Real.hpp>
#include <StepGeom_Conic.hpp>
class TCollection_HAsciiString;
class StepGeom_Axis2Placement;

class StepGeom_Parabola : public StepGeom_Conic
{

public:
  //! Returns a Parabola
  Standard_EXPORT StepGeom_Parabola();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const StepGeom_Axis2Placement&               aPosition,
                            const double                                 aFocalDist);

  Standard_EXPORT void SetFocalDist(const double aFocalDist);

  Standard_EXPORT double FocalDist() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_Parabola, StepGeom_Conic)

private:
  double focalDist;
};
