

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepVisual_InvisibleItem.hpp>
#include <StepVisual_PresentationLayerAssignment.hpp>
#include <StepVisual_PresentationRepresentation.hpp>
#include <StepVisual_StyledItem.hpp>

StepVisual_InvisibleItem::StepVisual_InvisibleItem() = default;

int StepVisual_InvisibleItem::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_StyledItem)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_PresentationLayerAssignment)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_PresentationRepresentation)))
    return 3;
  return 0;
}

occ::handle<StepVisual_StyledItem> StepVisual_InvisibleItem::StyledItem() const
{
  return GetCasted(StepVisual_StyledItem, Value());
}

occ::handle<StepVisual_PresentationLayerAssignment> StepVisual_InvisibleItem::
  PresentationLayerAssignment() const
{
  return GetCasted(StepVisual_PresentationLayerAssignment, Value());
}

occ::handle<StepVisual_PresentationRepresentation> StepVisual_InvisibleItem::
  PresentationRepresentation() const
{
  return GetCasted(StepVisual_PresentationRepresentation, Value());
}
