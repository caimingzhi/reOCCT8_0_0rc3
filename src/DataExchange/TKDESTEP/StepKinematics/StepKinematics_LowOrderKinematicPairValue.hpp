#pragma once

#include <Standard.hpp>
#include <StepKinematics_PairValue.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepKinematics_KinematicPair.hpp>

class StepKinematics_LowOrderKinematicPairValue : public StepKinematics_PairValue
{
public:
  Standard_EXPORT StepKinematics_LowOrderKinematicPairValue();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
    const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
    const double                                     theActualTranslationX,
    const double                                     theActualTranslationY,
    const double                                     theActualTranslationZ,
    const double                                     theActualRotationX,
    const double                                     theActualRotationY,
    const double                                     theActualRotationZ);

  Standard_EXPORT double ActualTranslationX() const;

  Standard_EXPORT void SetActualTranslationX(const double theActualTranslationX);

  Standard_EXPORT double ActualTranslationY() const;

  Standard_EXPORT void SetActualTranslationY(const double theActualTranslationY);

  Standard_EXPORT double ActualTranslationZ() const;

  Standard_EXPORT void SetActualTranslationZ(const double theActualTranslationZ);

  Standard_EXPORT double ActualRotationX() const;

  Standard_EXPORT void SetActualRotationX(const double theActualRotationX);

  Standard_EXPORT double ActualRotationY() const;

  Standard_EXPORT void SetActualRotationY(const double theActualRotationY);

  Standard_EXPORT double ActualRotationZ() const;

  Standard_EXPORT void SetActualRotationZ(const double theActualRotationZ);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_LowOrderKinematicPairValue, StepKinematics_PairValue)

private:
  double myActualTranslationX;
  double myActualTranslationY;
  double myActualTranslationZ;
  double myActualRotationX;
  double myActualRotationY;
  double myActualRotationZ;
};
