#pragma once


#include <Standard.hpp>
#include <StepKinematics_PairValue.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepKinematics_KinematicPair.hpp>

//! Representation of STEP entity PrismaticPairValue
class StepKinematics_PrismaticPairValue : public StepKinematics_PairValue
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_PrismaticPairValue();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
    const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
    const double                                     theActualTranslation);

  //! Returns field ActualTranslation
  Standard_EXPORT double ActualTranslation() const;
  //! Sets field ActualTranslation
  Standard_EXPORT void SetActualTranslation(const double theActualTranslation);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_PrismaticPairValue, StepKinematics_PairValue)

private:
  double myActualTranslation;
};
