

#include <StepGeom_Axis1Placement.hpp>
#include <StepGeom_Curve.hpp>
#include <StepGeom_SurfaceOfRevolution.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_SurfaceOfRevolution, StepGeom_SweptSurface)

StepGeom_SurfaceOfRevolution::StepGeom_SurfaceOfRevolution() = default;

void StepGeom_SurfaceOfRevolution::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                        const occ::handle<StepGeom_Curve>&           aSweptCurve,
                                        const occ::handle<StepGeom_Axis1Placement>&  aAxisPosition)
{

  axisPosition = aAxisPosition;

  StepGeom_SweptSurface::Init(aName, aSweptCurve);
}

void StepGeom_SurfaceOfRevolution::SetAxisPosition(
  const occ::handle<StepGeom_Axis1Placement>& aAxisPosition)
{
  axisPosition = aAxisPosition;
}

occ::handle<StepGeom_Axis1Placement> StepGeom_SurfaceOfRevolution::AxisPosition() const
{
  return axisPosition;
}
