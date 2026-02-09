

#include <StepVisual_TessellatedGeometricSet.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_TessellatedGeometricSet, StepVisual_TessellatedItem)

StepVisual_TessellatedGeometricSet::StepVisual_TessellatedGeometricSet() = default;

void StepVisual_TessellatedGeometricSet::Init(
  const occ::handle<TCollection_HAsciiString>&                                           theName,
  const NCollection_Handle<NCollection_Array1<occ::handle<StepVisual_TessellatedItem>>>& theItems)
{
  StepRepr_RepresentationItem::Init(theName);
  myItems = theItems;
}

NCollection_Handle<NCollection_Array1<occ::handle<StepVisual_TessellatedItem>>>
  StepVisual_TessellatedGeometricSet::Items() const
{
  return myItems;
}
