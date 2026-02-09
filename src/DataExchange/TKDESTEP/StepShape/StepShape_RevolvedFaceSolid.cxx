

#include <StepGeom_Axis1Placement.hpp>
#include <StepShape_FaceSurface.hpp>
#include <StepShape_RevolvedFaceSolid.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_RevolvedFaceSolid, StepShape_SweptFaceSolid)

StepShape_RevolvedFaceSolid::StepShape_RevolvedFaceSolid() = default;

void StepShape_RevolvedFaceSolid::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                       const occ::handle<StepShape_FaceSurface>&    aSweptArea)
{

  StepShape_SweptFaceSolid::Init(aName, aSweptArea);
}

void StepShape_RevolvedFaceSolid::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                       const occ::handle<StepShape_FaceSurface>&    aSweptArea,
                                       const occ::handle<StepGeom_Axis1Placement>&  aAxis,
                                       const double                                 aAngle)
{

  axis  = aAxis;
  angle = aAngle;

  StepShape_SweptFaceSolid::Init(aName, aSweptArea);
}

void StepShape_RevolvedFaceSolid::SetAxis(const occ::handle<StepGeom_Axis1Placement>& aAxis)
{
  axis = aAxis;
}

occ::handle<StepGeom_Axis1Placement> StepShape_RevolvedFaceSolid::Axis() const
{
  return axis;
}

void StepShape_RevolvedFaceSolid::SetAngle(const double aAngle)
{
  angle = aAngle;
}

double StepShape_RevolvedFaceSolid::Angle() const
{
  return angle;
}
