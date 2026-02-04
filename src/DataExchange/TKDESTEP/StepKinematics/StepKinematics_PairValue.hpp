#pragma once


#include <Standard.hpp>

#include <StepKinematics_KinematicPair.hpp>

//! Representation of STEP entity PairValue
class StepKinematics_PairValue : public StepGeom_GeometricRepresentationItem
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_PairValue();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& theRepresentationItem_Name,
                            const occ::handle<StepKinematics_KinematicPair>& theAppliesToPair);

  //! Returns field AppliesToPair
  Standard_EXPORT occ::handle<StepKinematics_KinematicPair> AppliesToPair() const;
  //! Sets field AppliesToPair
  Standard_EXPORT void SetAppliesToPair(
    const occ::handle<StepKinematics_KinematicPair>& theAppliesToPair);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_PairValue, StepGeom_GeometricRepresentationItem)

private:
  occ::handle<StepKinematics_KinematicPair> myAppliesToPair;
};
