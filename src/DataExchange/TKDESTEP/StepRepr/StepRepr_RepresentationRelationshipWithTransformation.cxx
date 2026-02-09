

#include <StepRepr_Representation.hpp>
#include <StepRepr_RepresentationRelationshipWithTransformation.hpp>
#include <StepRepr_Transformation.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_RepresentationRelationshipWithTransformation,
                           StepRepr_ShapeRepresentationRelationship)

StepRepr_RepresentationRelationshipWithTransformation::
  StepRepr_RepresentationRelationshipWithTransformation() = default;

void StepRepr_RepresentationRelationshipWithTransformation::Init(
  const occ::handle<TCollection_HAsciiString>& aName,
  const occ::handle<TCollection_HAsciiString>& aDescription,
  const occ::handle<StepRepr_Representation>&  aRep1,
  const occ::handle<StepRepr_Representation>&  aRep2,
  const StepRepr_Transformation&               aTrans)
{
  StepRepr_RepresentationRelationship::Init(aName, aDescription, aRep1, aRep2);
  theTrans = aTrans;
}

StepRepr_Transformation StepRepr_RepresentationRelationshipWithTransformation::
  TransformationOperator() const
{
  return theTrans;
}

void StepRepr_RepresentationRelationshipWithTransformation::SetTransformationOperator(
  const StepRepr_Transformation& aTrans)
{
  theTrans = aTrans;
}
