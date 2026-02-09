

#include <StepShape_FaceSurface.hpp>
#include <StepShape_SweptFaceSolid.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_SweptFaceSolid, StepShape_SolidModel)

StepShape_SweptFaceSolid::StepShape_SweptFaceSolid() = default;

void StepShape_SweptFaceSolid::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                    const occ::handle<StepShape_FaceSurface>&    aSweptArea)
{

  sweptArea = aSweptArea;

  StepRepr_RepresentationItem::Init(aName);
}

void StepShape_SweptFaceSolid::SetSweptFace(const occ::handle<StepShape_FaceSurface>& aSweptArea)
{
  sweptArea = aSweptArea;
}

occ::handle<StepShape_FaceSurface> StepShape_SweptFaceSolid::SweptFace() const
{
  return sweptArea;
}
