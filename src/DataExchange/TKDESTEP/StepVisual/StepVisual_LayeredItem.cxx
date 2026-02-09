

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepVisual_LayeredItem.hpp>
#include <StepVisual_PresentationRepresentation.hpp>

StepVisual_LayeredItem::StepVisual_LayeredItem() = default;

int StepVisual_LayeredItem::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_PresentationRepresentation)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_RepresentationItem)))
    return 2;
  return 0;
}

occ::handle<StepVisual_PresentationRepresentation> StepVisual_LayeredItem::
  PresentationRepresentation() const
{
  return GetCasted(StepVisual_PresentationRepresentation, Value());
}

occ::handle<StepRepr_RepresentationItem> StepVisual_LayeredItem::RepresentationItem() const
{
  return GetCasted(StepRepr_RepresentationItem, Value());
}
