#include <Standard_Type.hpp>
#include <StepBasic_EulerAngles.hpp>
#include <StepFEA_CurveElementInterval.hpp>
#include <StepFEA_CurveElementLocation.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_CurveElementInterval, Standard_Transient)

//=================================================================================================

StepFEA_CurveElementInterval::StepFEA_CurveElementInterval() = default;

//=================================================================================================

void StepFEA_CurveElementInterval::Init(
  const occ::handle<StepFEA_CurveElementLocation>& aFinishPosition,
  const occ::handle<StepBasic_EulerAngles>&        aEuAngles)
{

  theFinishPosition = aFinishPosition;

  theEuAngles = aEuAngles;
}

//=================================================================================================

occ::handle<StepFEA_CurveElementLocation> StepFEA_CurveElementInterval::FinishPosition() const
{
  return theFinishPosition;
}

//=================================================================================================

void StepFEA_CurveElementInterval::SetFinishPosition(
  const occ::handle<StepFEA_CurveElementLocation>& aFinishPosition)
{
  theFinishPosition = aFinishPosition;
}

//=================================================================================================

occ::handle<StepBasic_EulerAngles> StepFEA_CurveElementInterval::EuAngles() const
{
  return theEuAngles;
}

//=================================================================================================

void StepFEA_CurveElementInterval::SetEuAngles(const occ::handle<StepBasic_EulerAngles>& aEuAngles)
{
  theEuAngles = aEuAngles;
}
