#include <Standard_Type.hpp>
#include <StepFEA_CurveElementLocation.hpp>
#include <StepFEA_FeaParametricPoint.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_CurveElementLocation, Standard_Transient)

//=================================================================================================

StepFEA_CurveElementLocation::StepFEA_CurveElementLocation() = default;

//=================================================================================================

void StepFEA_CurveElementLocation::Init(const occ::handle<StepFEA_FeaParametricPoint>& aCoordinate)
{

  theCoordinate = aCoordinate;
}

//=================================================================================================

occ::handle<StepFEA_FeaParametricPoint> StepFEA_CurveElementLocation::Coordinate() const
{
  return theCoordinate;
}

//=================================================================================================

void StepFEA_CurveElementLocation::SetCoordinate(
  const occ::handle<StepFEA_FeaParametricPoint>& aCoordinate)
{
  theCoordinate = aCoordinate;
}
