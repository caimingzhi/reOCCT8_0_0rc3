#pragma once

#include <Standard.hpp>

#include <StepFEA_DegreeOfFreedom.hpp>
#include <StepElement_MeasureOrUnspecifiedValue.hpp>
#include <Standard_Transient.hpp>

//! Representation of STEP entity FreedomAndCoefficient
class StepFEA_FreedomAndCoefficient : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepFEA_FreedomAndCoefficient();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const StepFEA_DegreeOfFreedom&               aFreedom,
                            const StepElement_MeasureOrUnspecifiedValue& aA);

  //! Returns field Freedom
  Standard_EXPORT StepFEA_DegreeOfFreedom Freedom() const;

  //! Set field Freedom
  Standard_EXPORT void SetFreedom(const StepFEA_DegreeOfFreedom& Freedom);

  //! Returns field A
  Standard_EXPORT StepElement_MeasureOrUnspecifiedValue A() const;

  //! Set field A
  Standard_EXPORT void SetA(const StepElement_MeasureOrUnspecifiedValue& A);

  DEFINE_STANDARD_RTTIEXT(StepFEA_FreedomAndCoefficient, Standard_Transient)

private:
  StepFEA_DegreeOfFreedom               theFreedom;
  StepElement_MeasureOrUnspecifiedValue theA;
};
