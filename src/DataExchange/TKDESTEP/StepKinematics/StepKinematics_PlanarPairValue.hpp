#pragma once

#include <Standard.hpp>
#include <StepKinematics_PairValue.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepKinematics_KinematicPair.hpp>

class StepKinematics_PlanarPairValue : public StepKinematics_PairValue
{
public:
  Standard_EXPORT StepKinematics_PlanarPairValue();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
    const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
    const double                                     theActualRotation,
    const double                                     theActualTranslationX,
    const double                                     theActualTranslationY);

  Standard_EXPORT double ActualRotation() const;

  Standard_EXPORT void SetActualRotation(const double theActualRotation);

  Standard_EXPORT double ActualTranslationX() const;

  Standard_EXPORT void SetActualTranslationX(const double theActualTranslationX);

  Standard_EXPORT double ActualTranslationY() const;

  Standard_EXPORT void SetActualTranslationY(const double theActualTranslationY);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_PlanarPairValue, StepKinematics_PairValue)

private:
  double myActualRotation;
  double myActualTranslationX;
  double myActualTranslationY;
};
