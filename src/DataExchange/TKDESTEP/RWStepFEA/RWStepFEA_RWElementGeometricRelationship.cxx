#include <Interface_EntityIterator.hpp>
#include "RWStepFEA_RWElementGeometricRelationship.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepElement_AnalysisItemWithinRepresentation.hpp>
#include <StepFEA_ElementGeometricRelationship.hpp>

RWStepFEA_RWElementGeometricRelationship::RWStepFEA_RWElementGeometricRelationship() = default;

void RWStepFEA_RWElementGeometricRelationship::ReadStep(
  const occ::handle<StepData_StepReaderData>&              data,
  const int                                                num,
  occ::handle<Interface_Check>&                            ach,
  const occ::handle<StepFEA_ElementGeometricRelationship>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "element_geometric_relationship"))
    return;

  StepFEA_ElementOrElementGroup aElementRef;
  data->ReadEntity(num, 1, "element_ref", ach, aElementRef);

  occ::handle<StepElement_AnalysisItemWithinRepresentation> aItem;
  data->ReadEntity(num,
                   2,
                   "item",
                   ach,
                   STANDARD_TYPE(StepElement_AnalysisItemWithinRepresentation),
                   aItem);

  StepElement_ElementAspect aAspect;
  data->ReadEntity(num, 3, "aspect", ach, aAspect);

  ent->Init(aElementRef, aItem, aAspect);
}

void RWStepFEA_RWElementGeometricRelationship::WriteStep(
  StepData_StepWriter&                                     SW,
  const occ::handle<StepFEA_ElementGeometricRelationship>& ent) const
{

  SW.Send(ent->ElementRef().Value());

  SW.Send(ent->Item());

  SW.Send(ent->Aspect().Value());
}

void RWStepFEA_RWElementGeometricRelationship::Share(
  const occ::handle<StepFEA_ElementGeometricRelationship>& ent,
  Interface_EntityIterator&                                iter) const
{

  iter.AddItem(ent->ElementRef().Value());

  iter.AddItem(ent->Item());

  iter.AddItem(ent->Aspect().Value());
}
