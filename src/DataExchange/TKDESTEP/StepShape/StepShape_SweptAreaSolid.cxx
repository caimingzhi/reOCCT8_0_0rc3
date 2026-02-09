

#include <StepGeom_CurveBoundedSurface.hpp>
#include <StepShape_SweptAreaSolid.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_SweptAreaSolid, StepShape_SolidModel)

StepShape_SweptAreaSolid::StepShape_SweptAreaSolid() = default;

void StepShape_SweptAreaSolid::Init(const occ::handle<TCollection_HAsciiString>&     aName,
                                    const occ::handle<StepGeom_CurveBoundedSurface>& aSweptArea)
{

  sweptArea = aSweptArea;

  StepRepr_RepresentationItem::Init(aName);
}

void StepShape_SweptAreaSolid::SetSweptArea(
  const occ::handle<StepGeom_CurveBoundedSurface>& aSweptArea)
{
  sweptArea = aSweptArea;
}

occ::handle<StepGeom_CurveBoundedSurface> StepShape_SweptAreaSolid::SweptArea() const
{
  return sweptArea;
}
