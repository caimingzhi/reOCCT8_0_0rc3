#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_Representation.hpp>

class StepKinematics_MechanismRepresentation;

class StepKinematics_MechanismStateRepresentation : public StepRepr_Representation
{
public:
  Standard_EXPORT StepKinematics_MechanismStateRepresentation();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                                      theName,
    const occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>& theItems,
    const occ::handle<StepRepr_RepresentationContext>&         theContextOfItems,
    const occ::handle<StepKinematics_MechanismRepresentation>& theMechanism);

  Standard_EXPORT void SetMechanism(
    const occ::handle<StepKinematics_MechanismRepresentation>& theMechanism);

  Standard_EXPORT occ::handle<StepKinematics_MechanismRepresentation> Mechanism() const;

private:
  occ::handle<StepKinematics_MechanismRepresentation> myRepresentedMechanism;

  DEFINE_STANDARD_RTTIEXT(StepKinematics_MechanismStateRepresentation, StepRepr_Representation)
};
