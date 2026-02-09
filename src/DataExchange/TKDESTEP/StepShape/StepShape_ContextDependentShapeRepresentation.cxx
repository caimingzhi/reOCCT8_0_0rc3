

#include <StepRepr_ProductDefinitionShape.hpp>
#include <StepRepr_ShapeRepresentationRelationship.hpp>
#include <StepShape_ContextDependentShapeRepresentation.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_ContextDependentShapeRepresentation, Standard_Transient)

StepShape_ContextDependentShapeRepresentation::StepShape_ContextDependentShapeRepresentation() =
  default;

void StepShape_ContextDependentShapeRepresentation::Init(
  const occ::handle<StepRepr_ShapeRepresentationRelationship>& aRepRel,
  const occ::handle<StepRepr_ProductDefinitionShape>&          aProRel)
{
  theRepRel = aRepRel;
  theProRel = aProRel;
}

occ::handle<StepRepr_ShapeRepresentationRelationship>
  StepShape_ContextDependentShapeRepresentation::RepresentationRelation() const
{
  return theRepRel;
}

void StepShape_ContextDependentShapeRepresentation::SetRepresentationRelation(
  const occ::handle<StepRepr_ShapeRepresentationRelationship>& aRepRel)
{
  theRepRel = aRepRel;
}

occ::handle<StepRepr_ProductDefinitionShape> StepShape_ContextDependentShapeRepresentation::
  RepresentedProductRelation() const
{
  return theProRel;
}

void StepShape_ContextDependentShapeRepresentation::SetRepresentedProductRelation(
  const occ::handle<StepRepr_ProductDefinitionShape>& aProRel)
{
  theProRel = aProRel;
}
