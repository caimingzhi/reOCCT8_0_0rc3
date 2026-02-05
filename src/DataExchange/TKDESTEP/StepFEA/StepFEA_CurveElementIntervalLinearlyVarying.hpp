#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepElement_CurveElementSectionDefinition.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepFEA_CurveElementInterval.hpp>
class StepFEA_CurveElementLocation;
class StepBasic_EulerAngles;

//! Representation of STEP entity CurveElementIntervalLinearlyVarying
class StepFEA_CurveElementIntervalLinearlyVarying : public StepFEA_CurveElementInterval
{

public:
  //! Empty constructor
  Standard_EXPORT StepFEA_CurveElementIntervalLinearlyVarying();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<StepFEA_CurveElementLocation>& aCurveElementInterval_FinishPosition,
    const occ::handle<StepBasic_EulerAngles>&        aCurveElementInterval_EuAngles,
    const occ::handle<NCollection_HArray1<occ::handle<StepElement_CurveElementSectionDefinition>>>&
      aSections);

  //! Returns field Sections
  Standard_EXPORT occ::handle<
    NCollection_HArray1<occ::handle<StepElement_CurveElementSectionDefinition>>>
    Sections() const;

  //! Set field Sections
  Standard_EXPORT void SetSections(
    const occ::handle<NCollection_HArray1<occ::handle<StepElement_CurveElementSectionDefinition>>>&
      Sections);

  DEFINE_STANDARD_RTTIEXT(StepFEA_CurveElementIntervalLinearlyVarying, StepFEA_CurveElementInterval)

private:
  occ::handle<NCollection_HArray1<occ::handle<StepElement_CurveElementSectionDefinition>>>
    theSections;
};
