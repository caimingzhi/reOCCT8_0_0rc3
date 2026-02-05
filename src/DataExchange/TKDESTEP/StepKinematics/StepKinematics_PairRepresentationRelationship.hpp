#pragma once

#include <Standard.hpp>
#include <StepGeom_GeometricRepresentationItem.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationOrRepresentationReference.hpp>
#include <StepRepr_RepresentationRelationshipWithTransformation.hpp>

//! Representation of STEP entity PairRepresentationRelationship
class StepKinematics_PairRepresentationRelationship : public StepGeom_GeometricRepresentationItem
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_PairRepresentationRelationship();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& theRepresentationItem_Name,
    const occ::handle<TCollection_HAsciiString>& theRepresentationRelationship_Name,
    const bool                                   hasRepresentationRelationship_Description,
    const occ::handle<TCollection_HAsciiString>& theRepresentationRelationship_Description,
    const StepRepr_RepresentationOrRepresentationReference& theRepresentationRelationship_Rep1,
    const StepRepr_RepresentationOrRepresentationReference& theRepresentationRelationship_Rep2,
    const StepRepr_Transformation&
      theRepresentationRelationshipWithTransformation_TransformationOperator);

  //! Returns data for supertype RepresentationRelationshipWithTransformation
  Standard_EXPORT occ::handle<StepRepr_RepresentationRelationshipWithTransformation>
                  RepresentationRelationshipWithTransformation() const;
  //! Sets data for supertype RepresentationRelationshipWithTransformation
  Standard_EXPORT void SetRepresentationRelationshipWithTransformation(
    const occ::handle<StepRepr_RepresentationRelationshipWithTransformation>&
      theRepresentationRelationshipWithTransformation);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_PairRepresentationRelationship,
                          StepGeom_GeometricRepresentationItem)

private:
  // clang-format off
  occ::handle<StepRepr_RepresentationRelationshipWithTransformation> myRepresentationRelationshipWithTransformation; //!< supertype
  // clang-format on
};
