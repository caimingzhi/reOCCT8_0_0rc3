#pragma once

#include <Standard.hpp>
#include <StepKinematics_PairValue.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepKinematics_KinematicPair.hpp>

class StepKinematics_RevolutePairValue : public StepKinematics_PairValue
{
public:
  Standard_EXPORT StepKinematics_RevolutePairValue();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
    const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
    const double                                     theActualRotation);

  Standard_EXPORT double ActualRotation() const;

  Standard_EXPORT void SetActualRotation(const double theActualRotation);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_RevolutePairValue, StepKinematics_PairValue)

private:
  double myActualRotation;
};
