#include <StepDimTol_RunoutZoneOrientation.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepDimTol_RunoutZoneOrientation, Standard_Transient)

//=================================================================================================

StepDimTol_RunoutZoneOrientation::StepDimTol_RunoutZoneOrientation() = default;

//=================================================================================================

void StepDimTol_RunoutZoneOrientation::Init(
  const occ::handle<StepBasic_PlaneAngleMeasureWithUnit>& theAngle)
{
  // --- class own fields ---
  myAngle = theAngle;
}
