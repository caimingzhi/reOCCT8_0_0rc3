#pragma once

#include <Standard.hpp>
#include <StepKinematics_PairValue.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepKinematics_KinematicPair.hpp>

class StepKinematics_RackAndPinionPairValue : public StepKinematics_PairValue
{
public:
  Standard_EXPORT StepKinematics_RackAndPinionPairValue();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
    const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
    const double                                     theActualDisplacement);

  Standard_EXPORT double ActualDisplacement() const;

  Standard_EXPORT void SetActualDisplacement(const double theActualDisplacement);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_RackAndPinionPairValue, StepKinematics_PairValue)

private:
  double myActualDisplacement;
};
