#pragma once

#include <Standard.hpp>
#include <StepGeom_GeometricRepresentationItem.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationOrRepresentationReference.hpp>
#include <StepRepr_RepresentationRelationshipWithTransformation.hpp>

class StepKinematics_PairRepresentationRelationship : public StepGeom_GeometricRepresentationItem
{
public:
  Standard_EXPORT StepKinematics_PairRepresentationRelationship();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& theRepresentationItem_Name,
    const occ::handle<TCollection_HAsciiString>& theRepresentationRelationship_Name,
    const bool                                   hasRepresentationRelationship_Description,
    const occ::handle<TCollection_HAsciiString>& theRepresentationRelationship_Description,
    const StepRepr_RepresentationOrRepresentationReference& theRepresentationRelationship_Rep1,
    const StepRepr_RepresentationOrRepresentationReference& theRepresentationRelationship_Rep2,
    const StepRepr_Transformation&
      theRepresentationRelationshipWithTransformation_TransformationOperator);

  Standard_EXPORT occ::handle<StepRepr_RepresentationRelationshipWithTransformation>
                  RepresentationRelationshipWithTransformation() const;

  Standard_EXPORT void SetRepresentationRelationshipWithTransformation(
    const occ::handle<StepRepr_RepresentationRelationshipWithTransformation>&
      theRepresentationRelationshipWithTransformation);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_PairRepresentationRelationship,
                          StepGeom_GeometricRepresentationItem)

private:
  occ::handle<StepRepr_RepresentationRelationshipWithTransformation>
    myRepresentationRelationshipWithTransformation;
};
