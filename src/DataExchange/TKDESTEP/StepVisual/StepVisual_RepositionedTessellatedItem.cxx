

#include <StepVisual_RepositionedTessellatedItem.hpp>

#include <StepGeom_Axis2Placement3d.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_RepositionedTessellatedItem, StepVisual_TessellatedItem)

void StepVisual_RepositionedTessellatedItem::Init(
  const occ::handle<TCollection_HAsciiString>&  theName,
  const occ::handle<StepGeom_Axis2Placement3d>& theLocation)
{
  StepVisual_TessellatedItem::Init(theName);
  myLocation = theLocation;
}
