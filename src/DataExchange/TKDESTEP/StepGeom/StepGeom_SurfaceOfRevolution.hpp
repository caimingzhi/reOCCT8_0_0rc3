#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_SweptSurface.hpp>
class StepGeom_Axis1Placement;
class TCollection_HAsciiString;
class StepGeom_Curve;

class StepGeom_SurfaceOfRevolution : public StepGeom_SweptSurface
{

public:
  //! Returns a SurfaceOfRevolution
  Standard_EXPORT StepGeom_SurfaceOfRevolution();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepGeom_Curve>&           aSweptCurve,
                            const occ::handle<StepGeom_Axis1Placement>&  aAxisPosition);

  Standard_EXPORT void SetAxisPosition(const occ::handle<StepGeom_Axis1Placement>& aAxisPosition);

  Standard_EXPORT occ::handle<StepGeom_Axis1Placement> AxisPosition() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_SurfaceOfRevolution, StepGeom_SweptSurface)

private:
  occ::handle<StepGeom_Axis1Placement> axisPosition;
};

