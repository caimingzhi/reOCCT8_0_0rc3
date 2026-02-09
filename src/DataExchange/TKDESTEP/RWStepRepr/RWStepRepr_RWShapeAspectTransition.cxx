#include <Interface_EntityIterator.hpp>
#include "RWStepRepr_RWShapeAspectTransition.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_ShapeAspect.hpp>
#include <StepRepr_ShapeAspectTransition.hpp>

RWStepRepr_RWShapeAspectTransition::RWStepRepr_RWShapeAspectTransition() = default;

void RWStepRepr_RWShapeAspectTransition::ReadStep(
  const occ::handle<StepData_StepReaderData>&        data,
  const int                                          num,
  occ::handle<Interface_Check>&                      ach,
  const occ::handle<StepRepr_ShapeAspectTransition>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "shape_aspect_transition"))
    return;

  occ::handle<TCollection_HAsciiString> aShapeAspectRelationship_Name;
  data->ReadString(num, 1, "shape_aspect_relationship.name", ach, aShapeAspectRelationship_Name);

  occ::handle<TCollection_HAsciiString> aShapeAspectRelationship_Description;
  bool                                  hasShapeAspectRelationship_Description = true;
  if (data->IsParamDefined(num, 2))
  {
    data->ReadString(num,
                     2,
                     "shape_aspect_relationship.description",
                     ach,
                     aShapeAspectRelationship_Description);
  }
  else
  {
    hasShapeAspectRelationship_Description = false;
  }

  occ::handle<StepRepr_ShapeAspect> aShapeAspectRelationship_RelatingShapeAspect;
  data->ReadEntity(num,
                   3,
                   "shape_aspect_relationship.relating_shape_aspect",
                   ach,
                   STANDARD_TYPE(StepRepr_ShapeAspect),
                   aShapeAspectRelationship_RelatingShapeAspect);

  occ::handle<StepRepr_ShapeAspect> aShapeAspectRelationship_RelatedShapeAspect;
  data->ReadEntity(num,
                   4,
                   "shape_aspect_relationship.related_shape_aspect",
                   ach,
                   STANDARD_TYPE(StepRepr_ShapeAspect),
                   aShapeAspectRelationship_RelatedShapeAspect);

  ent->Init(aShapeAspectRelationship_Name,
            hasShapeAspectRelationship_Description,
            aShapeAspectRelationship_Description,
            aShapeAspectRelationship_RelatingShapeAspect,
            aShapeAspectRelationship_RelatedShapeAspect);
}

void RWStepRepr_RWShapeAspectTransition::WriteStep(
  StepData_StepWriter&                               SW,
  const occ::handle<StepRepr_ShapeAspectTransition>& ent) const
{

  SW.Send(ent->StepRepr_ShapeAspectRelationship::Name());

  if (ent->StepRepr_ShapeAspectRelationship::HasDescription())
  {
    SW.Send(ent->StepRepr_ShapeAspectRelationship::Description());
  }
  else
    SW.SendUndef();

  SW.Send(ent->StepRepr_ShapeAspectRelationship::RelatingShapeAspect());

  SW.Send(ent->StepRepr_ShapeAspectRelationship::RelatedShapeAspect());
}

void RWStepRepr_RWShapeAspectTransition::Share(
  const occ::handle<StepRepr_ShapeAspectTransition>& ent,
  Interface_EntityIterator&                          iter) const
{

  iter.AddItem(ent->StepRepr_ShapeAspectRelationship::RelatingShapeAspect());

  iter.AddItem(ent->StepRepr_ShapeAspectRelationship::RelatedShapeAspect());
}
