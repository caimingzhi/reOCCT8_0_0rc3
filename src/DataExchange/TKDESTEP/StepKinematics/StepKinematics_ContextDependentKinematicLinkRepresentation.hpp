#pragma once

#include <Standard.hpp>
#include <Standard_Transient.hpp>

#include <StepKinematics_KinematicLinkRepresentationAssociation.hpp>
#include <StepKinematics_ProductDefinitionRelationshipKinematics.hpp>

//! Representation of STEP entity ContextDependentKinematicLinkRepresentation
class StepKinematics_ContextDependentKinematicLinkRepresentation : public Standard_Transient
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_ContextDependentKinematicLinkRepresentation();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<StepKinematics_KinematicLinkRepresentationAssociation>&
      theRepresentationRelation,
    const occ::handle<StepKinematics_ProductDefinitionRelationshipKinematics>&
      theRepresentedProductRelation);

  //! Returns field RepresentationRelation
  Standard_EXPORT occ::handle<StepKinematics_KinematicLinkRepresentationAssociation>
                  RepresentationRelation() const;
  //! Sets field RepresentationRelation
  Standard_EXPORT void SetRepresentationRelation(
    const occ::handle<StepKinematics_KinematicLinkRepresentationAssociation>&
      theRepresentationRelation);

  //! Returns field RepresentedProductRelation
  Standard_EXPORT occ::handle<StepKinematics_ProductDefinitionRelationshipKinematics>
                  RepresentedProductRelation() const;
  //! Sets field RepresentedProductRelation
  Standard_EXPORT void SetRepresentedProductRelation(
    const occ::handle<StepKinematics_ProductDefinitionRelationshipKinematics>&
      theRepresentedProductRelation);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_ContextDependentKinematicLinkRepresentation,
                          Standard_Transient)

private:
  occ::handle<StepKinematics_KinematicLinkRepresentationAssociation>  myRepresentationRelation;
  occ::handle<StepKinematics_ProductDefinitionRelationshipKinematics> myRepresentedProductRelation;
};
