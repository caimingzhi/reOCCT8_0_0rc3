#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepFEA_CurveElementInterval.hpp>
class StepElement_CurveElementSectionDefinition;
class StepFEA_CurveElementLocation;
class StepBasic_EulerAngles;

//! Representation of STEP entity CurveElementIntervalConstant
class StepFEA_CurveElementIntervalConstant : public StepFEA_CurveElementInterval
{

public:
  //! Empty constructor
  Standard_EXPORT StepFEA_CurveElementIntervalConstant();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<StepFEA_CurveElementLocation>& aCurveElementInterval_FinishPosition,
    const occ::handle<StepBasic_EulerAngles>&        aCurveElementInterval_EuAngles,
    const occ::handle<StepElement_CurveElementSectionDefinition>& aSection);

  //! Returns field Section
  Standard_EXPORT occ::handle<StepElement_CurveElementSectionDefinition> Section() const;

  //! Set field Section
  Standard_EXPORT void SetSection(
    const occ::handle<StepElement_CurveElementSectionDefinition>& Section);

  DEFINE_STANDARD_RTTIEXT(StepFEA_CurveElementIntervalConstant, StepFEA_CurveElementInterval)

private:
  occ::handle<StepElement_CurveElementSectionDefinition> theSection;
};
