#pragma once

#include <Standard.hpp>
#include <StepKinematics_PairValue.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepKinematics_KinematicPair.hpp>

//! Representation of STEP entity PlanarPairValue
class StepKinematics_PlanarPairValue : public StepKinematics_PairValue
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_PlanarPairValue();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
    const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
    const double                                     theActualRotation,
    const double                                     theActualTranslationX,
    const double                                     theActualTranslationY);

  //! Returns field ActualRotation
  Standard_EXPORT double ActualRotation() const;
  //! Sets field ActualRotation
  Standard_EXPORT void SetActualRotation(const double theActualRotation);

  //! Returns field ActualTranslationX
  Standard_EXPORT double ActualTranslationX() const;
  //! Sets field ActualTranslationX
  Standard_EXPORT void SetActualTranslationX(const double theActualTranslationX);

  //! Returns field ActualTranslationY
  Standard_EXPORT double ActualTranslationY() const;
  //! Sets field ActualTranslationY
  Standard_EXPORT void SetActualTranslationY(const double theActualTranslationY);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_PlanarPairValue, StepKinematics_PairValue)

private:
  double myActualRotation;
  double myActualTranslationX;
  double myActualTranslationY;
};
