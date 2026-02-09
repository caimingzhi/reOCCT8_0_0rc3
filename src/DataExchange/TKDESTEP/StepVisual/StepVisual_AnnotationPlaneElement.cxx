#include <StepVisual_AnnotationPlaneElement.hpp>
#include <MoniTool_Macros.hpp>
#include <StepVisual_DraughtingCallout.hpp>
#include <StepVisual_StyledItem.hpp>

StepVisual_AnnotationPlaneElement::StepVisual_AnnotationPlaneElement() = default;

int StepVisual_AnnotationPlaneElement::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_DraughtingCallout)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_StyledItem)))
    return 2;
  return 0;
}

occ::handle<StepVisual_DraughtingCallout> StepVisual_AnnotationPlaneElement::DraughtingCallout()
  const
{
  return GetCasted(StepVisual_DraughtingCallout, Value());
}

occ::handle<StepVisual_StyledItem> StepVisual_AnnotationPlaneElement::StyledItem() const
{
  return GetCasted(StepVisual_StyledItem, Value());
}
