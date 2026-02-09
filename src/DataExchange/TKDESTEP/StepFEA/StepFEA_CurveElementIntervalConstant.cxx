#include <Standard_Type.hpp>
#include <StepBasic_EulerAngles.hpp>
#include <StepElement_CurveElementSectionDefinition.hpp>
#include <StepFEA_CurveElementIntervalConstant.hpp>
#include <StepFEA_CurveElementLocation.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_CurveElementIntervalConstant, StepFEA_CurveElementInterval)

StepFEA_CurveElementIntervalConstant::StepFEA_CurveElementIntervalConstant() = default;

void StepFEA_CurveElementIntervalConstant::Init(
  const occ::handle<StepFEA_CurveElementLocation>& aCurveElementInterval_FinishPosition,
  const occ::handle<StepBasic_EulerAngles>&        aCurveElementInterval_EuAngles,
  const occ::handle<StepElement_CurveElementSectionDefinition>& aSection)
{
  StepFEA_CurveElementInterval::Init(aCurveElementInterval_FinishPosition,
                                     aCurveElementInterval_EuAngles);

  theSection = aSection;
}

occ::handle<StepElement_CurveElementSectionDefinition> StepFEA_CurveElementIntervalConstant::
  Section() const
{
  return theSection;
}

void StepFEA_CurveElementIntervalConstant::SetSection(
  const occ::handle<StepElement_CurveElementSectionDefinition>& aSection)
{
  theSection = aSection;
}
