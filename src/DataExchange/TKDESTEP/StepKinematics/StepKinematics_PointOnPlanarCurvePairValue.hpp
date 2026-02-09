#pragma once

#include <Standard.hpp>
#include <StepKinematics_PairValue.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepKinematics_KinematicPair.hpp>
#include <StepGeom_PointOnCurve.hpp>
#include <StepKinematics_SpatialRotation.hpp>

class StepKinematics_PointOnPlanarCurvePairValue : public StepKinematics_PairValue
{
public:
  Standard_EXPORT StepKinematics_PointOnPlanarCurvePairValue();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
    const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
    const occ::handle<StepGeom_PointOnCurve>&        theActualPointOnCurve,
    const StepKinematics_SpatialRotation&            theInputOrientation);

  Standard_EXPORT occ::handle<StepGeom_PointOnCurve> ActualPointOnCurve() const;

  Standard_EXPORT void SetActualPointOnCurve(
    const occ::handle<StepGeom_PointOnCurve>& theActualPointOnCurve);

  Standard_EXPORT StepKinematics_SpatialRotation InputOrientation() const;

  Standard_EXPORT void SetInputOrientation(
    const StepKinematics_SpatialRotation& theInputOrientation);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_PointOnPlanarCurvePairValue, StepKinematics_PairValue)

private:
  occ::handle<StepGeom_PointOnCurve> myActualPointOnCurve;
  StepKinematics_SpatialRotation     myInputOrientation;
};
