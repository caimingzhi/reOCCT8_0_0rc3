

#include <StepGeom_Axis1Placement.hpp>
#include <StepGeom_CurveBoundedSurface.hpp>
#include <StepShape_RevolvedAreaSolid.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_RevolvedAreaSolid, StepShape_SweptAreaSolid)

StepShape_RevolvedAreaSolid::StepShape_RevolvedAreaSolid() = default;

void StepShape_RevolvedAreaSolid::Init(const occ::handle<TCollection_HAsciiString>&     aName,
                                       const occ::handle<StepGeom_CurveBoundedSurface>& aSweptArea,
                                       const occ::handle<StepGeom_Axis1Placement>&      aAxis,
                                       const double                                     aAngle)
{

  axis  = aAxis;
  angle = aAngle;

  StepShape_SweptAreaSolid::Init(aName, aSweptArea);
}

void StepShape_RevolvedAreaSolid::SetAxis(const occ::handle<StepGeom_Axis1Placement>& aAxis)
{
  axis = aAxis;
}

occ::handle<StepGeom_Axis1Placement> StepShape_RevolvedAreaSolid::Axis() const
{
  return axis;
}

void StepShape_RevolvedAreaSolid::SetAngle(const double aAngle)
{
  angle = aAngle;
}

double StepShape_RevolvedAreaSolid::Angle() const
{
  return angle;
}
