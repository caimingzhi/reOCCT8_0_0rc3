#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepFEA_CurveElementLocation;
class StepBasic_EulerAngles;

class StepFEA_CurveElementInterval : public Standard_Transient
{

public:
  Standard_EXPORT StepFEA_CurveElementInterval();

  Standard_EXPORT void Init(const occ::handle<StepFEA_CurveElementLocation>& aFinishPosition,
                            const occ::handle<StepBasic_EulerAngles>&        aEuAngles);

  Standard_EXPORT occ::handle<StepFEA_CurveElementLocation> FinishPosition() const;

  Standard_EXPORT void SetFinishPosition(
    const occ::handle<StepFEA_CurveElementLocation>& FinishPosition);

  Standard_EXPORT occ::handle<StepBasic_EulerAngles> EuAngles() const;

  Standard_EXPORT void SetEuAngles(const occ::handle<StepBasic_EulerAngles>& EuAngles);

  DEFINE_STANDARD_RTTIEXT(StepFEA_CurveElementInterval, Standard_Transient)

private:
  occ::handle<StepFEA_CurveElementLocation> theFinishPosition;
  occ::handle<StepBasic_EulerAngles>        theEuAngles;
};
