

#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWContextDependentShapeRepresentation.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_ProductDefinitionShape.hpp>
#include <StepRepr_ShapeRepresentationRelationship.hpp>
#include <StepShape_ContextDependentShapeRepresentation.hpp>

RWStepShape_RWContextDependentShapeRepresentation::
  RWStepShape_RWContextDependentShapeRepresentation() = default;

void RWStepShape_RWContextDependentShapeRepresentation::ReadStep(
  const occ::handle<StepData_StepReaderData>&                       data,
  const int                                                         num,
  occ::handle<Interface_Check>&                                     ach,
  const occ::handle<StepShape_ContextDependentShapeRepresentation>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "context_dependent_shape_representation"))
    return;

  occ::handle<StepRepr_ShapeRepresentationRelationship> aRepRel;

  data->ReadEntity(num,
                   1,
                   "representation_relation",
                   ach,
                   STANDARD_TYPE(StepRepr_ShapeRepresentationRelationship),
                   aRepRel);

  occ::handle<StepRepr_ProductDefinitionShape> aProRel;

  data->ReadEntity(num,
                   2,
                   "represented_product_relation",
                   ach,
                   STANDARD_TYPE(StepRepr_ProductDefinitionShape),
                   aProRel);

  ent->Init(aRepRel, aProRel);
}

void RWStepShape_RWContextDependentShapeRepresentation::WriteStep(
  StepData_StepWriter&                                              SW,
  const occ::handle<StepShape_ContextDependentShapeRepresentation>& ent) const
{
  SW.Send(ent->RepresentationRelation());
  SW.Send(ent->RepresentedProductRelation());
}

void RWStepShape_RWContextDependentShapeRepresentation::Share(
  const occ::handle<StepShape_ContextDependentShapeRepresentation>& ent,
  Interface_EntityIterator&                                         iter) const
{
  iter.AddItem(ent->RepresentationRelation());
  iter.AddItem(ent->RepresentedProductRelation());
}
