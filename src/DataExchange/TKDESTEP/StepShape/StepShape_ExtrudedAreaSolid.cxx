

#include <StepGeom_CurveBoundedSurface.hpp>
#include <StepGeom_Direction.hpp>
#include <StepShape_ExtrudedAreaSolid.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_ExtrudedAreaSolid, StepShape_SweptAreaSolid)

StepShape_ExtrudedAreaSolid::StepShape_ExtrudedAreaSolid() = default;

void StepShape_ExtrudedAreaSolid::Init(const occ::handle<TCollection_HAsciiString>&     aName,
                                       const occ::handle<StepGeom_CurveBoundedSurface>& aSweptArea,
                                       const occ::handle<StepGeom_Direction>& aExtrudedDirection,
                                       const double                           aDepth)
{

  extrudedDirection = aExtrudedDirection;
  depth             = aDepth;

  StepShape_SweptAreaSolid::Init(aName, aSweptArea);
}

void StepShape_ExtrudedAreaSolid::SetExtrudedDirection(
  const occ::handle<StepGeom_Direction>& aExtrudedDirection)
{
  extrudedDirection = aExtrudedDirection;
}

occ::handle<StepGeom_Direction> StepShape_ExtrudedAreaSolid::ExtrudedDirection() const
{
  return extrudedDirection;
}

void StepShape_ExtrudedAreaSolid::SetDepth(const double aDepth)
{
  depth = aDepth;
}

double StepShape_ExtrudedAreaSolid::Depth() const
{
  return depth;
}
