

#include "RWStepKinematics_RWKinematicPropertyMechanismRepresentation.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepKinematics_KinematicPropertyMechanismRepresentation.hpp>
#include <StepRepr_RepresentedDefinition.hpp>
#include <StepRepr_Representation.hpp>
#include <StepKinematics_KinematicLinkRepresentation.hpp>

RWStepKinematics_RWKinematicPropertyMechanismRepresentation::
  RWStepKinematics_RWKinematicPropertyMechanismRepresentation() = default;

void RWStepKinematics_RWKinematicPropertyMechanismRepresentation::ReadStep(
  const occ::handle<StepData_StepReaderData>&                                 theData,
  const int                                                                   theNum,
  occ::handle<Interface_Check>&                                               theArch,
  const occ::handle<StepKinematics_KinematicPropertyMechanismRepresentation>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 3, theArch, "kinematic_property_mechanism_representation"))
    return;

  StepRepr_RepresentedDefinition aPropertyDefinitionRepresentation_Definition;
  theData->ReadEntity(theNum,
                      1,
                      "property_definition_representation.definition",
                      theArch,
                      aPropertyDefinitionRepresentation_Definition);

  occ::handle<StepRepr_Representation> aPropertyDefinitionRepresentation_UsedRepresentation;
  theData->ReadEntity(theNum,
                      2,
                      "property_definition_representation.used_representation",
                      theArch,
                      STANDARD_TYPE(StepRepr_Representation),
                      aPropertyDefinitionRepresentation_UsedRepresentation);

  occ::handle<StepKinematics_KinematicLinkRepresentation> aBase;
  theData->ReadEntity(theNum,
                      3,
                      "base",
                      theArch,
                      STANDARD_TYPE(StepKinematics_KinematicLinkRepresentation),
                      aBase);

  theEnt->Init(aPropertyDefinitionRepresentation_Definition,
               aPropertyDefinitionRepresentation_UsedRepresentation,
               aBase);
}

void RWStepKinematics_RWKinematicPropertyMechanismRepresentation::WriteStep(
  StepData_StepWriter&                                                        theSW,
  const occ::handle<StepKinematics_KinematicPropertyMechanismRepresentation>& theEnt) const
{

  theSW.Send(theEnt->Definition().Value());

  theSW.Send(theEnt->UsedRepresentation());

  theSW.Send(theEnt->Base());
}

void RWStepKinematics_RWKinematicPropertyMechanismRepresentation::Share(
  const occ::handle<StepKinematics_KinematicPropertyMechanismRepresentation>& theEnt,
  Interface_EntityIterator&                                                   iter) const
{

  iter.AddItem(theEnt->StepRepr_PropertyDefinitionRepresentation::Definition().Value());

  iter.AddItem(theEnt->StepRepr_PropertyDefinitionRepresentation::UsedRepresentation());

  iter.AddItem(theEnt->Base());
}
