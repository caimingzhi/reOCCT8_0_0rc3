

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepVisual_AreaInSet.hpp>
#include <StepVisual_PresentationArea.hpp>
#include <StepVisual_PresentationSizeAssignmentSelect.hpp>
#include <StepVisual_PresentationView.hpp>

StepVisual_PresentationSizeAssignmentSelect::StepVisual_PresentationSizeAssignmentSelect() =
  default;

int StepVisual_PresentationSizeAssignmentSelect::CaseNum(
  const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_PresentationView)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_PresentationArea)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_AreaInSet)))
    return 3;
  return 0;
}

occ::handle<StepVisual_PresentationView> StepVisual_PresentationSizeAssignmentSelect::
  PresentationView() const
{
  return GetCasted(StepVisual_PresentationView, Value());
}

occ::handle<StepVisual_PresentationArea> StepVisual_PresentationSizeAssignmentSelect::
  PresentationArea() const
{
  return GetCasted(StepVisual_PresentationArea, Value());
}

occ::handle<StepVisual_AreaInSet> StepVisual_PresentationSizeAssignmentSelect::AreaInSet() const
{
  return GetCasted(StepVisual_AreaInSet, Value());
}
