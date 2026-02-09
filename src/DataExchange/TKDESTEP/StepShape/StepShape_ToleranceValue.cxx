

#include <StepBasic_MeasureWithUnit.hpp>
#include <StepShape_ToleranceValue.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_ToleranceValue, Standard_Transient)

StepShape_ToleranceValue::StepShape_ToleranceValue() = default;

void StepShape_ToleranceValue::Init(const occ::handle<Standard_Transient>& lower_bound,
                                    const occ::handle<Standard_Transient>& upper_bound)
{
  theLowerBound = lower_bound;
  theUpperBound = upper_bound;
}

occ::handle<Standard_Transient> StepShape_ToleranceValue::LowerBound() const
{
  return theLowerBound;
}

void StepShape_ToleranceValue::SetLowerBound(const occ::handle<Standard_Transient>& lower_bound)
{
  theLowerBound = lower_bound;
}

occ::handle<Standard_Transient> StepShape_ToleranceValue::UpperBound() const
{
  return theUpperBound;
}

void StepShape_ToleranceValue::SetUpperBound(const occ::handle<Standard_Transient>& upper_bound)
{
  theUpperBound = upper_bound;
}
