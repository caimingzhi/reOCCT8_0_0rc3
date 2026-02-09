

#include <StepGeom_Direction.hpp>
#include <StepShape_ExtrudedFaceSolid.hpp>
#include <StepShape_FaceSurface.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_ExtrudedFaceSolid, StepShape_SweptFaceSolid)

StepShape_ExtrudedFaceSolid::StepShape_ExtrudedFaceSolid() = default;

void StepShape_ExtrudedFaceSolid::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                       const occ::handle<StepShape_FaceSurface>&    aSweptArea,
                                       const occ::handle<StepGeom_Direction>& aExtrudedDirection,
                                       const double                           aDepth)
{

  extrudedDirection = aExtrudedDirection;
  depth             = aDepth;

  StepShape_SweptFaceSolid::Init(aName, aSweptArea);
}

void StepShape_ExtrudedFaceSolid::SetExtrudedDirection(
  const occ::handle<StepGeom_Direction>& aExtrudedDirection)
{
  extrudedDirection = aExtrudedDirection;
}

occ::handle<StepGeom_Direction> StepShape_ExtrudedFaceSolid::ExtrudedDirection() const
{
  return extrudedDirection;
}

void StepShape_ExtrudedFaceSolid::SetDepth(const double aDepth)
{
  depth = aDepth;
}

double StepShape_ExtrudedFaceSolid::Depth() const
{
  return depth;
}
