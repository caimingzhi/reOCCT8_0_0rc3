// Created on : Sat May 02 12:41:15 2020

#include <StepKinematics_PairRepresentationRelationship.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_PairRepresentationRelationship,
                           StepGeom_GeometricRepresentationItem)

//=================================================================================================

StepKinematics_PairRepresentationRelationship::StepKinematics_PairRepresentationRelationship() =
  default;

//=================================================================================================

void StepKinematics_PairRepresentationRelationship::Init(
  const occ::handle<TCollection_HAsciiString>& theRepresentationItem_Name,
  const occ::handle<TCollection_HAsciiString>& theRepresentationRelationship_Name,
  const bool /*hasRepresentationRelationship_Description*/,
  const occ::handle<TCollection_HAsciiString>&            theRepresentationRelationship_Description,
  const StepRepr_RepresentationOrRepresentationReference& theRepresentationRelationship_Rep1,
  const StepRepr_RepresentationOrRepresentationReference& theRepresentationRelationship_Rep2,
  const StepRepr_Transformation&
    theRepresentationRelationshipWithTransformation_TransformationOperator)
{
  StepGeom_GeometricRepresentationItem::Init(theRepresentationItem_Name);
  myRepresentationRelationshipWithTransformation =
    new StepRepr_RepresentationRelationshipWithTransformation;
  myRepresentationRelationshipWithTransformation->Init(
    theRepresentationRelationship_Name,
    /*hasRepresentationRelationship_Description,*/
    theRepresentationRelationship_Description,
    theRepresentationRelationship_Rep1.Representation(),
    theRepresentationRelationship_Rep2.Representation(),
    theRepresentationRelationshipWithTransformation_TransformationOperator);
}

//=================================================================================================

occ::handle<StepRepr_RepresentationRelationshipWithTransformation>
  StepKinematics_PairRepresentationRelationship::RepresentationRelationshipWithTransformation()
    const
{
  return myRepresentationRelationshipWithTransformation;
}

//=================================================================================================

void StepKinematics_PairRepresentationRelationship::SetRepresentationRelationshipWithTransformation(
  const occ::handle<StepRepr_RepresentationRelationshipWithTransformation>&
    theRepresentationRelationshipWithTransformation)
{
  myRepresentationRelationshipWithTransformation = theRepresentationRelationshipWithTransformation;
}
