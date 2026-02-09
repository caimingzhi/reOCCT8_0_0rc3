

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepRepr_Representation.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepVisual_PresentationSet.hpp>
#include <StepVisual_StyleContextSelect.hpp>

StepVisual_StyleContextSelect::StepVisual_StyleContextSelect() = default;

int StepVisual_StyleContextSelect::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_Representation)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_RepresentationItem)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_PresentationSet)))
    return 3;
  return 0;
}

occ::handle<StepRepr_Representation> StepVisual_StyleContextSelect::Representation() const
{
  return GetCasted(StepRepr_Representation, Value());
}

occ::handle<StepRepr_RepresentationItem> StepVisual_StyleContextSelect::RepresentationItem() const
{
  return GetCasted(StepRepr_RepresentationItem, Value());
}

occ::handle<StepVisual_PresentationSet> StepVisual_StyleContextSelect::PresentationSet() const
{
  return GetCasted(StepVisual_PresentationSet, Value());
}
