

#include <StepKinematics_UnconstrainedPairValue.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_UnconstrainedPairValue, StepKinematics_PairValue)

StepKinematics_UnconstrainedPairValue::StepKinematics_UnconstrainedPairValue() = default;

void StepKinematics_UnconstrainedPairValue::Init(
  const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
  const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
  const occ::handle<StepGeom_Axis2Placement3d>&    theActualPlacement)
{
  StepKinematics_PairValue::Init(theRepresentationItem_Name, thePairValue_AppliesToPair);

  myActualPlacement = theActualPlacement;
}

occ::handle<StepGeom_Axis2Placement3d> StepKinematics_UnconstrainedPairValue::ActualPlacement()
  const
{
  return myActualPlacement;
}

void StepKinematics_UnconstrainedPairValue::SetActualPlacement(
  const occ::handle<StepGeom_Axis2Placement3d>& theActualPlacement)
{
  myActualPlacement = theActualPlacement;
}
