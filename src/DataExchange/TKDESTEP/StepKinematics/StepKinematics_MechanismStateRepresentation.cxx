#include <StepKinematics_MechanismStateRepresentation.hpp>
#include <StepKinematics_MechanismRepresentation.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_MechanismStateRepresentation, StepRepr_Representation)

StepKinematics_MechanismStateRepresentation::StepKinematics_MechanismStateRepresentation() =
  default;

void StepKinematics_MechanismStateRepresentation::Init(
  const occ::handle<TCollection_HAsciiString>&                                      theName,
  const occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>& theItems,
  const occ::handle<StepRepr_RepresentationContext>&         theContextOfItems,
  const occ::handle<StepKinematics_MechanismRepresentation>& theMechanism)
{
  StepRepr_Representation::Init(theName, theItems, theContextOfItems);
  myRepresentedMechanism = theMechanism;
}

void StepKinematics_MechanismStateRepresentation::SetMechanism(
  const occ::handle<StepKinematics_MechanismRepresentation>& theMechanism)
{
  myRepresentedMechanism = theMechanism;
}

occ::handle<StepKinematics_MechanismRepresentation> StepKinematics_MechanismStateRepresentation::
  Mechanism() const
{
  return myRepresentedMechanism;
}
