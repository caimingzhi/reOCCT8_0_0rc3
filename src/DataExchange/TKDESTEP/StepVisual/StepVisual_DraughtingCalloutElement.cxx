#include <StepVisual_DraughtingCalloutElement.hpp>
#include <MoniTool_Macros.hpp>
#include <StepVisual_AnnotationCurveOccurrence.hpp>
#include <StepVisual_AnnotationFillAreaOccurrence.hpp>
#include <StepVisual_AnnotationTextOccurrence.hpp>
#include <StepVisual_TessellatedAnnotationOccurrence.hpp>

StepVisual_DraughtingCalloutElement::StepVisual_DraughtingCalloutElement() = default;

int StepVisual_DraughtingCalloutElement::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_AnnotationCurveOccurrence)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_AnnotationTextOccurrence)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_TessellatedAnnotationOccurrence)))
    return 3;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_AnnotationFillAreaOccurrence)))
    return 4;
  return 0;
}

occ::handle<StepVisual_AnnotationCurveOccurrence> StepVisual_DraughtingCalloutElement::
  AnnotationCurveOccurrence() const
{
  return GetCasted(StepVisual_AnnotationCurveOccurrence, Value());
}

occ::handle<StepVisual_TessellatedAnnotationOccurrence> StepVisual_DraughtingCalloutElement::
  TessellatedAnnotationOccurrence() const
{
  return GetCasted(StepVisual_TessellatedAnnotationOccurrence, Value());
}

occ::handle<StepVisual_AnnotationTextOccurrence> StepVisual_DraughtingCalloutElement::
  AnnotationTextOccurrence() const
{
  return GetCasted(StepVisual_AnnotationTextOccurrence, Value());
}

occ::handle<StepVisual_AnnotationFillAreaOccurrence> StepVisual_DraughtingCalloutElement::
  AnnotationFillAreaOccurrence() const
{
  return GetCasted(StepVisual_AnnotationFillAreaOccurrence, Value());
}
