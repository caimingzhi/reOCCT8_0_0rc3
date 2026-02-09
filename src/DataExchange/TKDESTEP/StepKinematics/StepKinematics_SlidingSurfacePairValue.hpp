#pragma once

#include <Standard.hpp>
#include <StepKinematics_PairValue.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepKinematics_KinematicPair.hpp>
#include <StepGeom_PointOnSurface.hpp>

class StepKinematics_SlidingSurfacePairValue : public StepKinematics_PairValue
{
public:
  Standard_EXPORT StepKinematics_SlidingSurfacePairValue();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
    const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
    const occ::handle<StepGeom_PointOnSurface>&      theActualPointOnSurface1,
    const occ::handle<StepGeom_PointOnSurface>&      theActualPointOnSurface2,
    const double                                     theActualRotation);

  Standard_EXPORT occ::handle<StepGeom_PointOnSurface> ActualPointOnSurface1() const;

  Standard_EXPORT void SetActualPointOnSurface1(
    const occ::handle<StepGeom_PointOnSurface>& theActualPointOnSurface1);

  Standard_EXPORT occ::handle<StepGeom_PointOnSurface> ActualPointOnSurface2() const;

  Standard_EXPORT void SetActualPointOnSurface2(
    const occ::handle<StepGeom_PointOnSurface>& theActualPointOnSurface2);

  Standard_EXPORT double ActualRotation() const;

  Standard_EXPORT void SetActualRotation(const double theActualRotation);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_SlidingSurfacePairValue, StepKinematics_PairValue)

private:
  occ::handle<StepGeom_PointOnSurface> myActualPointOnSurface1;
  occ::handle<StepGeom_PointOnSurface> myActualPointOnSurface2;
  double                               myActualRotation;
};
