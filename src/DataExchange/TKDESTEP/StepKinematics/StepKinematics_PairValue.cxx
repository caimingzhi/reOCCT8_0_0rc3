// Created on : Sat May 02 12:41:15 2020

#include <StepKinematics_PairValue.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_PairValue, StepGeom_GeometricRepresentationItem)

//=================================================================================================

StepKinematics_PairValue::StepKinematics_PairValue() = default;

//=================================================================================================

void StepKinematics_PairValue::Init(
  const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
  const occ::handle<StepKinematics_KinematicPair>& theAppliesToPair)
{
  StepGeom_GeometricRepresentationItem::Init(theRepresentationItem_Name);

  myAppliesToPair = theAppliesToPair;
}

//=================================================================================================

occ::handle<StepKinematics_KinematicPair> StepKinematics_PairValue::AppliesToPair() const
{
  return myAppliesToPair;
}

//=================================================================================================

void StepKinematics_PairValue::SetAppliesToPair(
  const occ::handle<StepKinematics_KinematicPair>& theAppliesToPair)
{
  myAppliesToPair = theAppliesToPair;
}
