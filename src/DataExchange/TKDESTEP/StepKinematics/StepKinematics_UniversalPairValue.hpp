#pragma once


#include <Standard.hpp>
#include <StepKinematics_PairValue.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepKinematics_KinematicPair.hpp>

//! Representation of STEP entity UniversalPairValue
class StepKinematics_UniversalPairValue : public StepKinematics_PairValue
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_UniversalPairValue();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
    const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
    const double                                     theFirstRotationAngle,
    const double                                     theSecondRotationAngle);

  //! Returns field FirstRotationAngle
  Standard_EXPORT double FirstRotationAngle() const;
  //! Sets field FirstRotationAngle
  Standard_EXPORT void SetFirstRotationAngle(const double theFirstRotationAngle);

  //! Returns field SecondRotationAngle
  Standard_EXPORT double SecondRotationAngle() const;
  //! Sets field SecondRotationAngle
  Standard_EXPORT void SetSecondRotationAngle(const double theSecondRotationAngle);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_UniversalPairValue, StepKinematics_PairValue)

private:
  double myFirstRotationAngle;
  double mySecondRotationAngle;
};
