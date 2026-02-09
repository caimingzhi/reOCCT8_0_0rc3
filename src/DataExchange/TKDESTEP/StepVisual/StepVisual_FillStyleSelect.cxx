

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepVisual_FillAreaStyleColour.hpp>
#include <StepVisual_FillStyleSelect.hpp>

StepVisual_FillStyleSelect::StepVisual_FillStyleSelect() = default;

int StepVisual_FillStyleSelect::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_FillAreaStyleColour)))
    return 1;

  return 0;
}

occ::handle<StepVisual_FillAreaStyleColour> StepVisual_FillStyleSelect::FillAreaStyleColour() const
{
  return GetCasted(StepVisual_FillAreaStyleColour, Value());
}
