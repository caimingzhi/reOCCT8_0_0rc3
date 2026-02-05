#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepRepr_ShapeRepresentationRelationship;
class StepRepr_ProductDefinitionShape;

class StepShape_ContextDependentShapeRepresentation : public Standard_Transient
{

public:
  Standard_EXPORT StepShape_ContextDependentShapeRepresentation();

  Standard_EXPORT void Init(const occ::handle<StepRepr_ShapeRepresentationRelationship>& aRepRel,
                            const occ::handle<StepRepr_ProductDefinitionShape>&          aProRel);

  Standard_EXPORT occ::handle<StepRepr_ShapeRepresentationRelationship> RepresentationRelation()
    const;

  Standard_EXPORT void SetRepresentationRelation(
    const occ::handle<StepRepr_ShapeRepresentationRelationship>& aRepRel);

  Standard_EXPORT occ::handle<StepRepr_ProductDefinitionShape> RepresentedProductRelation() const;

  Standard_EXPORT void SetRepresentedProductRelation(
    const occ::handle<StepRepr_ProductDefinitionShape>& aProRel);

  DEFINE_STANDARD_RTTIEXT(StepShape_ContextDependentShapeRepresentation, Standard_Transient)

private:
  occ::handle<StepRepr_ShapeRepresentationRelationship> theRepRel;
  occ::handle<StepRepr_ProductDefinitionShape>          theProRel;
};
