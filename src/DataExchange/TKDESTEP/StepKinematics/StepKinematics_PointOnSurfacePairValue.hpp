#pragma once

#include <Standard.hpp>
#include <StepKinematics_PairValue.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepKinematics_KinematicPair.hpp>
#include <StepGeom_PointOnSurface.hpp>
#include <StepKinematics_SpatialRotation.hpp>

class StepKinematics_PointOnSurfacePairValue : public StepKinematics_PairValue
{
public:
  Standard_EXPORT StepKinematics_PointOnSurfacePairValue();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
    const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
    const occ::handle<StepGeom_PointOnSurface>&      theActualPointOnSurface,
    const StepKinematics_SpatialRotation&            theInputOrientation);

  Standard_EXPORT occ::handle<StepGeom_PointOnSurface> ActualPointOnSurface() const;

  Standard_EXPORT void SetActualPointOnSurface(
    const occ::handle<StepGeom_PointOnSurface>& theActualPointOnSurface);

  Standard_EXPORT StepKinematics_SpatialRotation InputOrientation() const;

  Standard_EXPORT void SetInputOrientation(
    const StepKinematics_SpatialRotation& theInputOrientation);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_PointOnSurfacePairValue, StepKinematics_PairValue)

private:
  occ::handle<StepGeom_PointOnSurface> myActualPointOnSurface;
  StepKinematics_SpatialRotation       myInputOrientation;
};
