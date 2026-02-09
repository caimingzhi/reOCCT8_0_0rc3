#include <Standard_Type.hpp>
#include <StepBasic_EulerAngles.hpp>
#include <StepFEA_CurveElementIntervalLinearlyVarying.hpp>
#include <StepFEA_CurveElementLocation.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_CurveElementIntervalLinearlyVarying,
                           StepFEA_CurveElementInterval)

StepFEA_CurveElementIntervalLinearlyVarying::StepFEA_CurveElementIntervalLinearlyVarying() =
  default;

void StepFEA_CurveElementIntervalLinearlyVarying::Init(
  const occ::handle<StepFEA_CurveElementLocation>& aCurveElementInterval_FinishPosition,
  const occ::handle<StepBasic_EulerAngles>&        aCurveElementInterval_EuAngles,
  const occ::handle<NCollection_HArray1<occ::handle<StepElement_CurveElementSectionDefinition>>>&
    aSections)
{
  StepFEA_CurveElementInterval::Init(aCurveElementInterval_FinishPosition,
                                     aCurveElementInterval_EuAngles);

  theSections = aSections;
}

occ::handle<NCollection_HArray1<occ::handle<StepElement_CurveElementSectionDefinition>>>
  StepFEA_CurveElementIntervalLinearlyVarying::Sections() const
{
  return theSections;
}

void StepFEA_CurveElementIntervalLinearlyVarying::SetSections(
  const occ::handle<NCollection_HArray1<occ::handle<StepElement_CurveElementSectionDefinition>>>&
    aSections)
{
  theSections = aSections;
}
