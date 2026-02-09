#pragma once

#include <Standard.hpp>
#include <StepKinematics_PairValue.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepKinematics_KinematicPair.hpp>

class StepKinematics_GearPairValue : public StepKinematics_PairValue
{
public:
  Standard_EXPORT StepKinematics_GearPairValue();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
    const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
    const double                                     theActualRotation1);

  Standard_EXPORT double ActualRotation1() const;

  Standard_EXPORT void SetActualRotation1(const double theActualRotation1);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_GearPairValue, StepKinematics_PairValue)

private:
  double myActualRotation1;
};
