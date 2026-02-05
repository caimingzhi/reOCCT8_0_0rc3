// Created on : Sat May 02 12:41:15 2020

#include <StepKinematics_PointOnPlanarCurvePairValue.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_PointOnPlanarCurvePairValue, StepKinematics_PairValue)

//=================================================================================================

StepKinematics_PointOnPlanarCurvePairValue::StepKinematics_PointOnPlanarCurvePairValue() = default;

//=================================================================================================

void StepKinematics_PointOnPlanarCurvePairValue::Init(
  const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
  const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
  const occ::handle<StepGeom_PointOnCurve>&        theActualPointOnCurve,
  const StepKinematics_SpatialRotation&            theInputOrientation)
{
  StepKinematics_PairValue::Init(theRepresentationItem_Name, thePairValue_AppliesToPair);

  myActualPointOnCurve = theActualPointOnCurve;

  myInputOrientation = theInputOrientation;
}

//=================================================================================================

occ::handle<StepGeom_PointOnCurve> StepKinematics_PointOnPlanarCurvePairValue::ActualPointOnCurve()
  const
{
  return myActualPointOnCurve;
}

//=================================================================================================

void StepKinematics_PointOnPlanarCurvePairValue::SetActualPointOnCurve(
  const occ::handle<StepGeom_PointOnCurve>& theActualPointOnCurve)
{
  myActualPointOnCurve = theActualPointOnCurve;
}

//=================================================================================================

StepKinematics_SpatialRotation StepKinematics_PointOnPlanarCurvePairValue::InputOrientation() const
{
  return myInputOrientation;
}

//=================================================================================================

void StepKinematics_PointOnPlanarCurvePairValue::SetInputOrientation(
  const StepKinematics_SpatialRotation& theInputOrientation)
{
  myInputOrientation = theInputOrientation;
}
