#include <StepFEA_FreedomAndCoefficient.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_FreedomAndCoefficient, Standard_Transient)

StepFEA_FreedomAndCoefficient::StepFEA_FreedomAndCoefficient() = default;

void StepFEA_FreedomAndCoefficient::Init(const StepFEA_DegreeOfFreedom&               aFreedom,
                                         const StepElement_MeasureOrUnspecifiedValue& aA)
{

  theFreedom = aFreedom;

  theA = aA;
}

StepFEA_DegreeOfFreedom StepFEA_FreedomAndCoefficient::Freedom() const
{
  return theFreedom;
}

void StepFEA_FreedomAndCoefficient::SetFreedom(const StepFEA_DegreeOfFreedom& aFreedom)
{
  theFreedom = aFreedom;
}

StepElement_MeasureOrUnspecifiedValue StepFEA_FreedomAndCoefficient::A() const
{
  return theA;
}

void StepFEA_FreedomAndCoefficient::SetA(const StepElement_MeasureOrUnspecifiedValue& aA)
{
  theA = aA;
}
