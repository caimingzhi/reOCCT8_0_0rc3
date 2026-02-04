#pragma once


#include <Standard.hpp>
#include <StepKinematics_PairValue.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepKinematics_KinematicPair.hpp>
#include <StepKinematics_SpatialRotation.hpp>

//! Representation of STEP entity SphericalPairValue
class StepKinematics_SphericalPairValue : public StepKinematics_PairValue
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_SphericalPairValue();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
    const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
    const StepKinematics_SpatialRotation&            theInputOrientation);

  //! Returns field InputOrientation
  Standard_EXPORT StepKinematics_SpatialRotation InputOrientation() const;
  //! Sets field InputOrientation
  Standard_EXPORT void SetInputOrientation(
    const StepKinematics_SpatialRotation& theInputOrientation);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_SphericalPairValue, StepKinematics_PairValue)

private:
  StepKinematics_SpatialRotation myInputOrientation;
};
