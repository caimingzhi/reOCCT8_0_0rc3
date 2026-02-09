

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepVisual_AreaOrView.hpp>
#include <StepVisual_PresentationArea.hpp>
#include <StepVisual_PresentationView.hpp>

StepVisual_AreaOrView::StepVisual_AreaOrView() = default;

int StepVisual_AreaOrView::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_PresentationArea)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_PresentationView)))
    return 2;
  return 0;
}

occ::handle<StepVisual_PresentationArea> StepVisual_AreaOrView::PresentationArea() const
{
  return GetCasted(StepVisual_PresentationArea, Value());
}

occ::handle<StepVisual_PresentationView> StepVisual_AreaOrView::PresentationView() const
{
  return GetCasted(StepVisual_PresentationView, Value());
}
