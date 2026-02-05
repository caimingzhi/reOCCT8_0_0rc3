// Created on : Sat May 02 12:41:16 2020

#include <StepKinematics_RollingCurvePairValue.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_RollingCurvePairValue, StepKinematics_PairValue)

//=================================================================================================

StepKinematics_RollingCurvePairValue::StepKinematics_RollingCurvePairValue() = default;

//=================================================================================================

void StepKinematics_RollingCurvePairValue::Init(
  const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
  const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
  const occ::handle<StepGeom_PointOnCurve>&        theActualPointOnCurve1)
{
  StepKinematics_PairValue::Init(theRepresentationItem_Name, thePairValue_AppliesToPair);

  myActualPointOnCurve1 = theActualPointOnCurve1;
}

//=================================================================================================

occ::handle<StepGeom_PointOnCurve> StepKinematics_RollingCurvePairValue::ActualPointOnCurve1() const
{
  return myActualPointOnCurve1;
}

//=================================================================================================

void StepKinematics_RollingCurvePairValue::SetActualPointOnCurve1(
  const occ::handle<StepGeom_PointOnCurve>& theActualPointOnCurve1)
{
  myActualPointOnCurve1 = theActualPointOnCurve1;
}
