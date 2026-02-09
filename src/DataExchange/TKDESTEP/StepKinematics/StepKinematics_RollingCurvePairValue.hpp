#pragma once

#include <Standard.hpp>
#include <StepKinematics_PairValue.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepKinematics_KinematicPair.hpp>
#include <StepGeom_PointOnCurve.hpp>

class StepKinematics_RollingCurvePairValue : public StepKinematics_PairValue
{
public:
  Standard_EXPORT StepKinematics_RollingCurvePairValue();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
    const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
    const occ::handle<StepGeom_PointOnCurve>&        theActualPointOnCurve1);

  Standard_EXPORT occ::handle<StepGeom_PointOnCurve> ActualPointOnCurve1() const;

  Standard_EXPORT void SetActualPointOnCurve1(
    const occ::handle<StepGeom_PointOnCurve>& theActualPointOnCurve1);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_RollingCurvePairValue, StepKinematics_PairValue)

private:
  occ::handle<StepGeom_PointOnCurve> myActualPointOnCurve1;
};
