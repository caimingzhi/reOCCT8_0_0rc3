

#include "RWStepKinematics_RWContextDependentKinematicLinkRepresentation.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepKinematics_ContextDependentKinematicLinkRepresentation.hpp>
#include <StepKinematics_KinematicLinkRepresentationAssociation.hpp>
#include <StepKinematics_ProductDefinitionRelationshipKinematics.hpp>

RWStepKinematics_RWContextDependentKinematicLinkRepresentation::
  RWStepKinematics_RWContextDependentKinematicLinkRepresentation() = default;

void RWStepKinematics_RWContextDependentKinematicLinkRepresentation::ReadStep(
  const occ::handle<StepData_StepReaderData>&                                    theData,
  const int                                                                      theNum,
  occ::handle<Interface_Check>&                                                  theArch,
  const occ::handle<StepKinematics_ContextDependentKinematicLinkRepresentation>& theEnt) const
{

  if (!theData->CheckNbParams(theNum,
                              2,
                              theArch,
                              "context_dependent_kinematic_link_representation"))
    return;

  occ::handle<StepKinematics_KinematicLinkRepresentationAssociation> aRepresentationRelation;
  theData->ReadEntity(theNum,
                      1,
                      "representation_relation",
                      theArch,
                      STANDARD_TYPE(StepKinematics_KinematicLinkRepresentationAssociation),
                      aRepresentationRelation);

  occ::handle<StepKinematics_ProductDefinitionRelationshipKinematics> aRepresentedProductRelation;
  theData->ReadEntity(theNum,
                      2,
                      "represented_product_relation",
                      theArch,
                      STANDARD_TYPE(StepKinematics_ProductDefinitionRelationshipKinematics),
                      aRepresentedProductRelation);

  theEnt->Init(aRepresentationRelation, aRepresentedProductRelation);
}

void RWStepKinematics_RWContextDependentKinematicLinkRepresentation::WriteStep(
  StepData_StepWriter&                                                           theSW,
  const occ::handle<StepKinematics_ContextDependentKinematicLinkRepresentation>& theEnt) const
{

  theSW.Send(theEnt->RepresentationRelation());

  theSW.Send(theEnt->RepresentedProductRelation());
}

void RWStepKinematics_RWContextDependentKinematicLinkRepresentation::Share(
  const occ::handle<StepKinematics_ContextDependentKinematicLinkRepresentation>& theEnt,
  Interface_EntityIterator&                                                      iter) const
{

  iter.AddItem(theEnt->RepresentationRelation());

  iter.AddItem(theEnt->RepresentedProductRelation());
}
