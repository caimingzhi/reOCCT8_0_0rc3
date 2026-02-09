#pragma once

#include <Standard.hpp>
#include <StepKinematics_PairValue.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepKinematics_KinematicPair.hpp>
#include <StepGeom_PointOnSurface.hpp>

class StepKinematics_RollingSurfacePairValue : public StepKinematics_PairValue
{
public:
  Standard_EXPORT StepKinematics_RollingSurfacePairValue();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
    const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
    const occ::handle<StepGeom_PointOnSurface>&      theActualPointOnSurface,
    const double                                     theActualRotation);

  Standard_EXPORT occ::handle<StepGeom_PointOnSurface> ActualPointOnSurface() const;

  Standard_EXPORT void SetActualPointOnSurface(
    const occ::handle<StepGeom_PointOnSurface>& theActualPointOnSurface);

  Standard_EXPORT double ActualRotation() const;

  Standard_EXPORT void SetActualRotation(const double theActualRotation);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_RollingSurfacePairValue, StepKinematics_PairValue)

private:
  occ::handle<StepGeom_PointOnSurface> myActualPointOnSurface;
  double                               myActualRotation;
};
