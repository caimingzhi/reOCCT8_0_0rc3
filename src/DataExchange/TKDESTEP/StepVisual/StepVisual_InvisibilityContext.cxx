

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepVisual_DraughtingModel.hpp>
#include <StepVisual_InvisibilityContext.hpp>
#include <StepVisual_PresentationRepresentation.hpp>
#include <StepVisual_PresentationSet.hpp>

StepVisual_InvisibilityContext::StepVisual_InvisibilityContext() = default;

int StepVisual_InvisibilityContext::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_PresentationRepresentation)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_PresentationSet)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_DraughtingModel)))
    return 3;
  return 0;
}

occ::handle<StepVisual_PresentationRepresentation> StepVisual_InvisibilityContext::
  PresentationRepresentation() const
{
  return GetCasted(StepVisual_PresentationRepresentation, Value());
}

occ::handle<StepVisual_PresentationSet> StepVisual_InvisibilityContext::PresentationSet() const
{
  return GetCasted(StepVisual_PresentationSet, Value());
}

occ::handle<StepVisual_DraughtingModel> StepVisual_InvisibilityContext::DraughtingModel() const
{
  return GetCasted(StepVisual_DraughtingModel, Value());
}
