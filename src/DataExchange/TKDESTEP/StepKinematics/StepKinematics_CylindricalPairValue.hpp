#pragma once

#include <Standard.hpp>
#include <StepKinematics_PairValue.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepKinematics_KinematicPair.hpp>

//! Representation of STEP entity CylindricalPairValue
class StepKinematics_CylindricalPairValue : public StepKinematics_PairValue
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_CylindricalPairValue();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
    const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
    const double                                     theActualTranslation,
    const double                                     theActualRotation);

  //! Returns field ActualTranslation
  Standard_EXPORT double ActualTranslation() const;
  //! Sets field ActualTranslation
  Standard_EXPORT void SetActualTranslation(const double theActualTranslation);

  //! Returns field ActualRotation
  Standard_EXPORT double ActualRotation() const;
  //! Sets field ActualRotation
  Standard_EXPORT void SetActualRotation(const double theActualRotation);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_CylindricalPairValue, StepKinematics_PairValue)

private:
  double myActualTranslation;
  double myActualRotation;
};
