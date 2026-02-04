#pragma once


#include <Standard.hpp>
#include <StepKinematics_PairValue.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepKinematics_KinematicPair.hpp>

//! Representation of STEP entity ScrewPairValue
class StepKinematics_ScrewPairValue : public StepKinematics_PairValue
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_ScrewPairValue();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
    const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
    const double                                     theActualRotation);

  //! Returns field ActualRotation
  Standard_EXPORT double ActualRotation() const;
  //! Sets field ActualRotation
  Standard_EXPORT void SetActualRotation(const double theActualRotation);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_ScrewPairValue, StepKinematics_PairValue)

private:
  double myActualRotation;
};
