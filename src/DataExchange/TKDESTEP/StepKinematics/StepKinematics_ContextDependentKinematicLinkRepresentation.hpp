#pragma once

#include <Standard.hpp>
#include <Standard_Transient.hpp>

#include <StepKinematics_KinematicLinkRepresentationAssociation.hpp>
#include <StepKinematics_ProductDefinitionRelationshipKinematics.hpp>

class StepKinematics_ContextDependentKinematicLinkRepresentation : public Standard_Transient
{
public:
  Standard_EXPORT StepKinematics_ContextDependentKinematicLinkRepresentation();

  Standard_EXPORT void Init(
    const occ::handle<StepKinematics_KinematicLinkRepresentationAssociation>&
      theRepresentationRelation,
    const occ::handle<StepKinematics_ProductDefinitionRelationshipKinematics>&
      theRepresentedProductRelation);

  Standard_EXPORT occ::handle<StepKinematics_KinematicLinkRepresentationAssociation>
                  RepresentationRelation() const;

  Standard_EXPORT void SetRepresentationRelation(
    const occ::handle<StepKinematics_KinematicLinkRepresentationAssociation>&
      theRepresentationRelation);

  Standard_EXPORT occ::handle<StepKinematics_ProductDefinitionRelationshipKinematics>
                  RepresentedProductRelation() const;

  Standard_EXPORT void SetRepresentedProductRelation(
    const occ::handle<StepKinematics_ProductDefinitionRelationshipKinematics>&
      theRepresentedProductRelation);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_ContextDependentKinematicLinkRepresentation,
                          Standard_Transient)

private:
  occ::handle<StepKinematics_KinematicLinkRepresentationAssociation>  myRepresentationRelation;
  occ::handle<StepKinematics_ProductDefinitionRelationshipKinematics> myRepresentedProductRelation;
};
