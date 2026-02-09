#include <StepShape_Subface.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_Subface, StepShape_Face)

StepShape_Subface::StepShape_Subface() = default;

void StepShape_Subface::Init(
  const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
  const occ::handle<NCollection_HArray1<occ::handle<StepShape_FaceBound>>>& aFace_Bounds,
  const occ::handle<StepShape_Face>&                                        aParentFace)
{
  StepShape_Face::Init(aRepresentationItem_Name, aFace_Bounds);

  theParentFace = aParentFace;
}

occ::handle<StepShape_Face> StepShape_Subface::ParentFace() const
{
  return theParentFace;
}

void StepShape_Subface::SetParentFace(const occ::handle<StepShape_Face>& aParentFace)
{
  theParentFace = aParentFace;
}
