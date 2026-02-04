#pragma once


#include <Standard.hpp>
#include <StepKinematics_PairValue.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepKinematics_KinematicPair.hpp>
#include <StepGeom_PointOnSurface.hpp>

//! Representation of STEP entity RollingSurfacePairValue
class StepKinematics_RollingSurfacePairValue : public StepKinematics_PairValue
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_RollingSurfacePairValue();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
    const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
    const occ::handle<StepGeom_PointOnSurface>&      theActualPointOnSurface,
    const double                                     theActualRotation);

  //! Returns field ActualPointOnSurface
  Standard_EXPORT occ::handle<StepGeom_PointOnSurface> ActualPointOnSurface() const;
  //! Sets field ActualPointOnSurface
  Standard_EXPORT void SetActualPointOnSurface(
    const occ::handle<StepGeom_PointOnSurface>& theActualPointOnSurface);

  //! Returns field ActualRotation
  Standard_EXPORT double ActualRotation() const;
  //! Sets field ActualRotation
  Standard_EXPORT void SetActualRotation(const double theActualRotation);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_RollingSurfacePairValue, StepKinematics_PairValue)

private:
  occ::handle<StepGeom_PointOnSurface> myActualPointOnSurface;
  double                               myActualRotation;
};
