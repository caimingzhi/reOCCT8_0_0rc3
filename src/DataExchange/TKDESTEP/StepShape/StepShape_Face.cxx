

#include <StepShape_Face.hpp>
#include <StepShape_FaceBound.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_Face, StepShape_TopologicalRepresentationItem)

StepShape_Face::StepShape_Face() = default;

void StepShape_Face::Init(
  const occ::handle<TCollection_HAsciiString>&                              aName,
  const occ::handle<NCollection_HArray1<occ::handle<StepShape_FaceBound>>>& aBounds)
{

  bounds = aBounds;

  StepRepr_RepresentationItem::Init(aName);
}

void StepShape_Face::SetBounds(
  const occ::handle<NCollection_HArray1<occ::handle<StepShape_FaceBound>>>& aBounds)
{
  bounds = aBounds;
}

occ::handle<NCollection_HArray1<occ::handle<StepShape_FaceBound>>> StepShape_Face::Bounds() const
{
  return bounds;
}

occ::handle<StepShape_FaceBound> StepShape_Face::BoundsValue(const int num) const
{
  return bounds->Value(num);
}

int StepShape_Face::NbBounds() const
{
  if (bounds.IsNull())
    return 0;
  return bounds->Length();
}
