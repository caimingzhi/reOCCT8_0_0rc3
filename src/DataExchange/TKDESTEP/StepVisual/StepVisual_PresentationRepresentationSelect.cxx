

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepVisual_PresentationRepresentation.hpp>
#include <StepVisual_PresentationRepresentationSelect.hpp>
#include <StepVisual_PresentationSet.hpp>

StepVisual_PresentationRepresentationSelect::StepVisual_PresentationRepresentationSelect() =
  default;

int StepVisual_PresentationRepresentationSelect::CaseNum(
  const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_PresentationRepresentation)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_PresentationSet)))
    return 2;
  return 0;
}

occ::handle<StepVisual_PresentationRepresentation> StepVisual_PresentationRepresentationSelect::
  PresentationRepresentation() const
{
  return GetCasted(StepVisual_PresentationRepresentation, Value());
}

occ::handle<StepVisual_PresentationSet> StepVisual_PresentationRepresentationSelect::
  PresentationSet() const
{
  return GetCasted(StepVisual_PresentationSet, Value());
}
