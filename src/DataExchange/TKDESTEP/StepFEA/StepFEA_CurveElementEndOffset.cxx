#include <StepFEA_CurveElementEndOffset.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_CurveElementEndOffset, Standard_Transient)

StepFEA_CurveElementEndOffset::StepFEA_CurveElementEndOffset() = default;

void StepFEA_CurveElementEndOffset::Init(
  const StepFEA_CurveElementEndCoordinateSystem&  aCoordinateSystem,
  const occ::handle<NCollection_HArray1<double>>& aOffsetVector)
{

  theCoordinateSystem = aCoordinateSystem;

  theOffsetVector = aOffsetVector;
}

StepFEA_CurveElementEndCoordinateSystem StepFEA_CurveElementEndOffset::CoordinateSystem() const
{
  return theCoordinateSystem;
}

void StepFEA_CurveElementEndOffset::SetCoordinateSystem(
  const StepFEA_CurveElementEndCoordinateSystem& aCoordinateSystem)
{
  theCoordinateSystem = aCoordinateSystem;
}

occ::handle<NCollection_HArray1<double>> StepFEA_CurveElementEndOffset::OffsetVector() const
{
  return theOffsetVector;
}

void StepFEA_CurveElementEndOffset::SetOffsetVector(
  const occ::handle<NCollection_HArray1<double>>& aOffsetVector)
{
  theOffsetVector = aOffsetVector;
}
