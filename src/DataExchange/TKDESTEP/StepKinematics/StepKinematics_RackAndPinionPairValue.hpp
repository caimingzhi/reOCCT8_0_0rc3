#pragma once

#include <Standard.hpp>
#include <StepKinematics_PairValue.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepKinematics_KinematicPair.hpp>

//! Representation of STEP entity RackAndPinionPairValue
class StepKinematics_RackAndPinionPairValue : public StepKinematics_PairValue
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_RackAndPinionPairValue();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
    const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
    const double                                     theActualDisplacement);

  //! Returns field ActualDisplacement
  Standard_EXPORT double ActualDisplacement() const;
  //! Sets field ActualDisplacement
  Standard_EXPORT void SetActualDisplacement(const double theActualDisplacement);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_RackAndPinionPairValue, StepKinematics_PairValue)

private:
  double myActualDisplacement;
};
