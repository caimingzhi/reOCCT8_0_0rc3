#pragma once

#include <Standard.hpp>

#include <StepKinematics_KinematicPair.hpp>

class StepKinematics_PairValue : public StepGeom_GeometricRepresentationItem
{
public:
  Standard_EXPORT StepKinematics_PairValue();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& theRepresentationItem_Name,
                            const occ::handle<StepKinematics_KinematicPair>& theAppliesToPair);

  Standard_EXPORT occ::handle<StepKinematics_KinematicPair> AppliesToPair() const;

  Standard_EXPORT void SetAppliesToPair(
    const occ::handle<StepKinematics_KinematicPair>& theAppliesToPair);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_PairValue, StepGeom_GeometricRepresentationItem)

private:
  occ::handle<StepKinematics_KinematicPair> myAppliesToPair;
};
