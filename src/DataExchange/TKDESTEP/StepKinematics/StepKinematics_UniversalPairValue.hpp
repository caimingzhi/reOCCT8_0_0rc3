#pragma once

#include <Standard.hpp>
#include <StepKinematics_PairValue.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepKinematics_KinematicPair.hpp>

class StepKinematics_UniversalPairValue : public StepKinematics_PairValue
{
public:
  Standard_EXPORT StepKinematics_UniversalPairValue();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
    const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
    const double                                     theFirstRotationAngle,
    const double                                     theSecondRotationAngle);

  Standard_EXPORT double FirstRotationAngle() const;

  Standard_EXPORT void SetFirstRotationAngle(const double theFirstRotationAngle);

  Standard_EXPORT double SecondRotationAngle() const;

  Standard_EXPORT void SetSecondRotationAngle(const double theSecondRotationAngle);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_UniversalPairValue, StepKinematics_PairValue)

private:
  double myFirstRotationAngle;
  double mySecondRotationAngle;
};
