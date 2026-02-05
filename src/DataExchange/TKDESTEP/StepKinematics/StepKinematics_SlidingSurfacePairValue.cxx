// Created on : Sat May 02 12:41:16 2020

#include <StepKinematics_SlidingSurfacePairValue.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_SlidingSurfacePairValue, StepKinematics_PairValue)

//=================================================================================================

StepKinematics_SlidingSurfacePairValue::StepKinematics_SlidingSurfacePairValue() = default;

//=================================================================================================

void StepKinematics_SlidingSurfacePairValue::Init(
  const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
  const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
  const occ::handle<StepGeom_PointOnSurface>&      theActualPointOnSurface1,
  const occ::handle<StepGeom_PointOnSurface>&      theActualPointOnSurface2,
  const double                                     theActualRotation)
{
  StepKinematics_PairValue::Init(theRepresentationItem_Name, thePairValue_AppliesToPair);

  myActualPointOnSurface1 = theActualPointOnSurface1;

  myActualPointOnSurface2 = theActualPointOnSurface2;

  myActualRotation = theActualRotation;
}

//=================================================================================================

occ::handle<StepGeom_PointOnSurface> StepKinematics_SlidingSurfacePairValue::ActualPointOnSurface1()
  const
{
  return myActualPointOnSurface1;
}

//=================================================================================================

void StepKinematics_SlidingSurfacePairValue::SetActualPointOnSurface1(
  const occ::handle<StepGeom_PointOnSurface>& theActualPointOnSurface1)
{
  myActualPointOnSurface1 = theActualPointOnSurface1;
}

//=================================================================================================

occ::handle<StepGeom_PointOnSurface> StepKinematics_SlidingSurfacePairValue::ActualPointOnSurface2()
  const
{
  return myActualPointOnSurface2;
}

//=================================================================================================

void StepKinematics_SlidingSurfacePairValue::SetActualPointOnSurface2(
  const occ::handle<StepGeom_PointOnSurface>& theActualPointOnSurface2)
{
  myActualPointOnSurface2 = theActualPointOnSurface2;
}

//=================================================================================================

double StepKinematics_SlidingSurfacePairValue::ActualRotation() const
{
  return myActualRotation;
}

//=================================================================================================

void StepKinematics_SlidingSurfacePairValue::SetActualRotation(const double theActualRotation)
{
  myActualRotation = theActualRotation;
}
