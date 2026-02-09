#pragma once

#include <Standard.hpp>

#include <StepFEA_DegreeOfFreedom.hpp>
#include <StepElement_MeasureOrUnspecifiedValue.hpp>
#include <Standard_Transient.hpp>

class StepFEA_FreedomAndCoefficient : public Standard_Transient
{

public:
  Standard_EXPORT StepFEA_FreedomAndCoefficient();

  Standard_EXPORT void Init(const StepFEA_DegreeOfFreedom&               aFreedom,
                            const StepElement_MeasureOrUnspecifiedValue& aA);

  Standard_EXPORT StepFEA_DegreeOfFreedom Freedom() const;

  Standard_EXPORT void SetFreedom(const StepFEA_DegreeOfFreedom& Freedom);

  Standard_EXPORT StepElement_MeasureOrUnspecifiedValue A() const;

  Standard_EXPORT void SetA(const StepElement_MeasureOrUnspecifiedValue& A);

  DEFINE_STANDARD_RTTIEXT(StepFEA_FreedomAndCoefficient, Standard_Transient)

private:
  StepFEA_DegreeOfFreedom               theFreedom;
  StepElement_MeasureOrUnspecifiedValue theA;
};
