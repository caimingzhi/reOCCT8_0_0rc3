

#include <StepKinematics_KinematicPropertyMechanismRepresentation.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_KinematicPropertyMechanismRepresentation,
                           StepKinematics_KinematicPropertyDefinitionRepresentation)

StepKinematics_KinematicPropertyMechanismRepresentation::
  StepKinematics_KinematicPropertyMechanismRepresentation() = default;

void StepKinematics_KinematicPropertyMechanismRepresentation::Init(
  const StepRepr_RepresentedDefinition& thePropertyDefinitionRepresentation_Definition,
  const occ::handle<StepRepr_Representation>&
    thePropertyDefinitionRepresentation_UsedRepresentation,
  const occ::handle<StepKinematics_KinematicLinkRepresentation>& theBase)
{
  StepKinematics_KinematicPropertyDefinitionRepresentation::Init(
    thePropertyDefinitionRepresentation_Definition,
    thePropertyDefinitionRepresentation_UsedRepresentation);

  myBase = theBase;
}

occ::handle<StepKinematics_KinematicLinkRepresentation>
  StepKinematics_KinematicPropertyMechanismRepresentation::Base() const
{
  return myBase;
}

void StepKinematics_KinematicPropertyMechanismRepresentation::SetBase(
  const occ::handle<StepKinematics_KinematicLinkRepresentation>& theBase)
{
  myBase = theBase;
}
