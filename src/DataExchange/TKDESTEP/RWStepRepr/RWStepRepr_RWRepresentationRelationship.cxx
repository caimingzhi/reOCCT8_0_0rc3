

#include <Interface_EntityIterator.hpp>
#include "RWStepRepr_RWRepresentationRelationship.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_Representation.hpp>
#include <StepRepr_RepresentationRelationship.hpp>

RWStepRepr_RWRepresentationRelationship::RWStepRepr_RWRepresentationRelationship() = default;

void RWStepRepr_RWRepresentationRelationship::ReadStep(
  const occ::handle<StepData_StepReaderData>&             data,
  const int                                               num,
  occ::handle<Interface_Check>&                           ach,
  const occ::handle<StepRepr_RepresentationRelationship>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "representation_relationship"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<TCollection_HAsciiString> aDescription;
  if (data->IsParamDefined(num, 2))
  {

    data->ReadString(num, 2, "description", ach, aDescription);
  }

  occ::handle<StepRepr_Representation> aRep1;

  data->ReadEntity(num, 3, "rep_1", ach, STANDARD_TYPE(StepRepr_Representation), aRep1);

  occ::handle<StepRepr_Representation> aRep2;

  data->ReadEntity(num, 4, "rep_2", ach, STANDARD_TYPE(StepRepr_Representation), aRep2);

  ent->Init(aName, aDescription, aRep1, aRep2);
}

void RWStepRepr_RWRepresentationRelationship::WriteStep(
  StepData_StepWriter&                                    SW,
  const occ::handle<StepRepr_RepresentationRelationship>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Description());

  SW.Send(ent->Rep1());

  SW.Send(ent->Rep2());
}

void RWStepRepr_RWRepresentationRelationship::Share(
  const occ::handle<StepRepr_RepresentationRelationship>& ent,
  Interface_EntityIterator&                               iter) const
{

  iter.GetOneItem(ent->Rep1());

  iter.GetOneItem(ent->Rep2());
}
