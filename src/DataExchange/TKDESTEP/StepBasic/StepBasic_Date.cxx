

#include <Standard_Type.hpp>
#include <StepBasic_Date.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_Date, Standard_Transient)

StepBasic_Date::StepBasic_Date() = default;

void StepBasic_Date::Init(const int aYearComponent)
{

  yearComponent = aYearComponent;
}

void StepBasic_Date::SetYearComponent(const int aYearComponent)
{
  yearComponent = aYearComponent;
}

int StepBasic_Date::YearComponent() const
{
  return yearComponent;
}
