#pragma once

#include <Standard.hpp>
#include <StepKinematics_PairValue.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepKinematics_KinematicPair.hpp>

class StepKinematics_PrismaticPairValue : public StepKinematics_PairValue
{
public:
  Standard_EXPORT StepKinematics_PrismaticPairValue();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
    const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
    const double                                     theActualTranslation);

  Standard_EXPORT double ActualTranslation() const;

  Standard_EXPORT void SetActualTranslation(const double theActualTranslation);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_PrismaticPairValue, StepKinematics_PairValue)

private:
  double myActualTranslation;
};
