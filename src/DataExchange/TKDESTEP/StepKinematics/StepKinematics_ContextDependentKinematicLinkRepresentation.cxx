

#include <StepKinematics_ContextDependentKinematicLinkRepresentation.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_ContextDependentKinematicLinkRepresentation,
                           Standard_Transient)

StepKinematics_ContextDependentKinematicLinkRepresentation::
  StepKinematics_ContextDependentKinematicLinkRepresentation() = default;

void StepKinematics_ContextDependentKinematicLinkRepresentation::Init(
  const occ::handle<StepKinematics_KinematicLinkRepresentationAssociation>&
    theRepresentationRelation,
  const occ::handle<StepKinematics_ProductDefinitionRelationshipKinematics>&
    theRepresentedProductRelation)
{

  myRepresentationRelation = theRepresentationRelation;

  myRepresentedProductRelation = theRepresentedProductRelation;
}

occ::handle<StepKinematics_KinematicLinkRepresentationAssociation>
  StepKinematics_ContextDependentKinematicLinkRepresentation::RepresentationRelation() const
{
  return myRepresentationRelation;
}

void StepKinematics_ContextDependentKinematicLinkRepresentation::SetRepresentationRelation(
  const occ::handle<StepKinematics_KinematicLinkRepresentationAssociation>&
    theRepresentationRelation)
{
  myRepresentationRelation = theRepresentationRelation;
}

occ::handle<StepKinematics_ProductDefinitionRelationshipKinematics>
  StepKinematics_ContextDependentKinematicLinkRepresentation::RepresentedProductRelation() const
{
  return myRepresentedProductRelation;
}

void StepKinematics_ContextDependentKinematicLinkRepresentation::SetRepresentedProductRelation(
  const occ::handle<StepKinematics_ProductDefinitionRelationshipKinematics>&
    theRepresentedProductRelation)
{
  myRepresentedProductRelation = theRepresentedProductRelation;
}
