#pragma once

#include <Standard.hpp>
#include <StepKinematics_PairValue.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepKinematics_KinematicPair.hpp>

//! Representation of STEP entity LowOrderKinematicPairValue
class StepKinematics_LowOrderKinematicPairValue : public StepKinematics_PairValue
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_LowOrderKinematicPairValue();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
    const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
    const double                                     theActualTranslationX,
    const double                                     theActualTranslationY,
    const double                                     theActualTranslationZ,
    const double                                     theActualRotationX,
    const double                                     theActualRotationY,
    const double                                     theActualRotationZ);

  //! Returns field ActualTranslationX
  Standard_EXPORT double ActualTranslationX() const;
  //! Sets field ActualTranslationX
  Standard_EXPORT void SetActualTranslationX(const double theActualTranslationX);

  //! Returns field ActualTranslationY
  Standard_EXPORT double ActualTranslationY() const;
  //! Sets field ActualTranslationY
  Standard_EXPORT void SetActualTranslationY(const double theActualTranslationY);

  //! Returns field ActualTranslationZ
  Standard_EXPORT double ActualTranslationZ() const;
  //! Sets field ActualTranslationZ
  Standard_EXPORT void SetActualTranslationZ(const double theActualTranslationZ);

  //! Returns field ActualRotationX
  Standard_EXPORT double ActualRotationX() const;
  //! Sets field ActualRotationX
  Standard_EXPORT void SetActualRotationX(const double theActualRotationX);

  //! Returns field ActualRotationY
  Standard_EXPORT double ActualRotationY() const;
  //! Sets field ActualRotationY
  Standard_EXPORT void SetActualRotationY(const double theActualRotationY);

  //! Returns field ActualRotationZ
  Standard_EXPORT double ActualRotationZ() const;
  //! Sets field ActualRotationZ
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
