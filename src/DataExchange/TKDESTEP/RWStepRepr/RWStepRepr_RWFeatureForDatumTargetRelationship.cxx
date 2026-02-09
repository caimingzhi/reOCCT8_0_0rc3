#include <Interface_EntityIterator.hpp>
#include "RWStepRepr_RWFeatureForDatumTargetRelationship.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_ShapeAspect.hpp>
#include <StepRepr_FeatureForDatumTargetRelationship.hpp>

RWStepRepr_RWFeatureForDatumTargetRelationship::RWStepRepr_RWFeatureForDatumTargetRelationship() =
  default;

void RWStepRepr_RWFeatureForDatumTargetRelationship::ReadStep(
  const occ::handle<StepData_StepReaderData>&                    data,
  const int                                                      num,
  occ::handle<Interface_Check>&                                  ach,
  const occ::handle<StepRepr_FeatureForDatumTargetRelationship>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "feature_for_datum_target-relationship"))
    return;

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<TCollection_HAsciiString> aDescription;
  bool                                  hasDescription = true;
  if (data->IsParamDefined(num, 2))
  {
    data->ReadString(num, 2, "description", ach, aDescription);
  }
  else
  {
    hasDescription = false;
  }

  occ::handle<StepRepr_ShapeAspect> aRelatingShapeAspect;
  data->ReadEntity(num,
                   3,
                   "relating_shape_aspect",
                   ach,
                   STANDARD_TYPE(StepRepr_ShapeAspect),
                   aRelatingShapeAspect);

  occ::handle<StepRepr_ShapeAspect> aRelatedShapeAspect;
  data->ReadEntity(num,
                   4,
                   "related_shape_aspect",
                   ach,
                   STANDARD_TYPE(StepRepr_ShapeAspect),
                   aRelatedShapeAspect);

  ent->Init(aName, hasDescription, aDescription, aRelatingShapeAspect, aRelatedShapeAspect);
}

void RWStepRepr_RWFeatureForDatumTargetRelationship::WriteStep(
  StepData_StepWriter&                                           SW,
  const occ::handle<StepRepr_FeatureForDatumTargetRelationship>& ent) const
{

  SW.Send(ent->Name());

  if (ent->HasDescription())
  {
    SW.Send(ent->Description());
  }
  else
    SW.SendUndef();

  SW.Send(ent->RelatingShapeAspect());

  SW.Send(ent->RelatedShapeAspect());
}

void RWStepRepr_RWFeatureForDatumTargetRelationship::Share(
  const occ::handle<StepRepr_FeatureForDatumTargetRelationship>& ent,
  Interface_EntityIterator&                                      iter) const
{

  iter.AddItem(ent->RelatingShapeAspect());

  iter.AddItem(ent->RelatedShapeAspect());
}
