

#include <Standard_Transient.hpp>
#include <StepShape_LimitsAndFits.hpp>
#include <StepShape_ToleranceMethodDefinition.hpp>
#include <StepShape_ToleranceValue.hpp>

StepShape_ToleranceMethodDefinition::StepShape_ToleranceMethodDefinition() = default;

int StepShape_ToleranceMethodDefinition::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepShape_ToleranceValue)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepShape_LimitsAndFits)))
    return 2;
  return 0;
}

occ::handle<StepShape_ToleranceValue> StepShape_ToleranceMethodDefinition::ToleranceValue() const
{
  return occ::down_cast<StepShape_ToleranceValue>(Value());
}

occ::handle<StepShape_LimitsAndFits> StepShape_ToleranceMethodDefinition::LimitsAndFits() const
{
  return occ::down_cast<StepShape_LimitsAndFits>(Value());
}
