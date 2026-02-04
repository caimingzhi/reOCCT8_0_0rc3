#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepFEA_CurveElementLocation;
class StepBasic_EulerAngles;

//! Representation of STEP entity CurveElementInterval
class StepFEA_CurveElementInterval : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepFEA_CurveElementInterval();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<StepFEA_CurveElementLocation>& aFinishPosition,
                            const occ::handle<StepBasic_EulerAngles>&        aEuAngles);

  //! Returns field FinishPosition
  Standard_EXPORT occ::handle<StepFEA_CurveElementLocation> FinishPosition() const;

  //! Set field FinishPosition
  Standard_EXPORT void SetFinishPosition(
    const occ::handle<StepFEA_CurveElementLocation>& FinishPosition);

  //! Returns field EuAngles
  Standard_EXPORT occ::handle<StepBasic_EulerAngles> EuAngles() const;

  //! Set field EuAngles
  Standard_EXPORT void SetEuAngles(const occ::handle<StepBasic_EulerAngles>& EuAngles);

  DEFINE_STANDARD_RTTIEXT(StepFEA_CurveElementInterval, Standard_Transient)

private:
  occ::handle<StepFEA_CurveElementLocation> theFinishPosition;
  occ::handle<StepBasic_EulerAngles>        theEuAngles;
};

