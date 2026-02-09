

#include <Standard_Type.hpp>
#include <StepShape_PrecisionQualifier.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_PrecisionQualifier, Standard_Transient)

StepShape_PrecisionQualifier::StepShape_PrecisionQualifier() = default;

void StepShape_PrecisionQualifier::Init(const int precision_value)
{
  thePrecisionValue = precision_value;
}

int StepShape_PrecisionQualifier::PrecisionValue() const
{
  return thePrecisionValue;
}

void StepShape_PrecisionQualifier::SetPrecisionValue(const int precision_value)
{
  thePrecisionValue = precision_value;
}
