// Created on : Sat May 02 12:41:16 2020

#include <StepKinematics_SlidingCurvePairValue.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_SlidingCurvePairValue, StepKinematics_PairValue)

//=================================================================================================

StepKinematics_SlidingCurvePairValue::StepKinematics_SlidingCurvePairValue() = default;

//=================================================================================================

void StepKinematics_SlidingCurvePairValue::Init(
  const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
  const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
  const occ::handle<StepGeom_PointOnCurve>&        theActualPointOnCurve1,
  const occ::handle<StepGeom_PointOnCurve>&        theActualPointOnCurve2)
{
  StepKinematics_PairValue::Init(theRepresentationItem_Name, thePairValue_AppliesToPair);

  myActualPointOnCurve1 = theActualPointOnCurve1;

  myActualPointOnCurve2 = theActualPointOnCurve2;
}

//=================================================================================================

occ::handle<StepGeom_PointOnCurve> StepKinematics_SlidingCurvePairValue::ActualPointOnCurve1() const
{
  return myActualPointOnCurve1;
}

//=================================================================================================

void StepKinematics_SlidingCurvePairValue::SetActualPointOnCurve1(
  const occ::handle<StepGeom_PointOnCurve>& theActualPointOnCurve1)
{
  myActualPointOnCurve1 = theActualPointOnCurve1;
}

//=================================================================================================

occ::handle<StepGeom_PointOnCurve> StepKinematics_SlidingCurvePairValue::ActualPointOnCurve2() const
{
  return myActualPointOnCurve2;
}

//=================================================================================================

void StepKinematics_SlidingCurvePairValue::SetActualPointOnCurve2(
  const occ::handle<StepGeom_PointOnCurve>& theActualPointOnCurve2)
{
  myActualPointOnCurve2 = theActualPointOnCurve2;
}
