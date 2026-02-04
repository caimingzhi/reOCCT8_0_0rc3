#pragma once


#include <Standard.hpp>
#include <StepKinematics_PairValue.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepKinematics_KinematicPair.hpp>
#include <StepGeom_PointOnSurface.hpp>

//! Representation of STEP entity SlidingSurfacePairValue
class StepKinematics_SlidingSurfacePairValue : public StepKinematics_PairValue
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_SlidingSurfacePairValue();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
    const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
    const occ::handle<StepGeom_PointOnSurface>&      theActualPointOnSurface1,
    const occ::handle<StepGeom_PointOnSurface>&      theActualPointOnSurface2,
    const double                                     theActualRotation);

  //! Returns field ActualPointOnSurface1
  Standard_EXPORT occ::handle<StepGeom_PointOnSurface> ActualPointOnSurface1() const;
  //! Sets field ActualPointOnSurface1
  Standard_EXPORT void SetActualPointOnSurface1(
    const occ::handle<StepGeom_PointOnSurface>& theActualPointOnSurface1);

  //! Returns field ActualPointOnSurface2
  Standard_EXPORT occ::handle<StepGeom_PointOnSurface> ActualPointOnSurface2() const;
  //! Sets field ActualPointOnSurface2
  Standard_EXPORT void SetActualPointOnSurface2(
    const occ::handle<StepGeom_PointOnSurface>& theActualPointOnSurface2);

  //! Returns field ActualRotation
  Standard_EXPORT double ActualRotation() const;
  //! Sets field ActualRotation
  Standard_EXPORT void SetActualRotation(const double theActualRotation);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_SlidingSurfacePairValue, StepKinematics_PairValue)

private:
  occ::handle<StepGeom_PointOnSurface> myActualPointOnSurface1;
  occ::handle<StepGeom_PointOnSurface> myActualPointOnSurface2;
  double                               myActualRotation;
};
