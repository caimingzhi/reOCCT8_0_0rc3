#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWGroupRelationship.hpp"
#include <StepBasic_Group.hpp>
#include <StepBasic_GroupRelationship.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWGroupRelationship::RWStepBasic_RWGroupRelationship() = default;

void RWStepBasic_RWGroupRelationship::ReadStep(
  const occ::handle<StepData_StepReaderData>&     data,
  const int                                       num,
  occ::handle<Interface_Check>&                   ach,
  const occ::handle<StepBasic_GroupRelationship>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "group_relationship"))
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

  occ::handle<StepBasic_Group> aRelatingGroup;
  data->ReadEntity(num, 3, "relating_group", ach, STANDARD_TYPE(StepBasic_Group), aRelatingGroup);

  occ::handle<StepBasic_Group> aRelatedGroup;
  data->ReadEntity(num, 4, "related_group", ach, STANDARD_TYPE(StepBasic_Group), aRelatedGroup);

  ent->Init(aName, hasDescription, aDescription, aRelatingGroup, aRelatedGroup);
}

void RWStepBasic_RWGroupRelationship::WriteStep(
  StepData_StepWriter&                            SW,
  const occ::handle<StepBasic_GroupRelationship>& ent) const
{

  SW.Send(ent->Name());

  if (ent->HasDescription())
  {
    SW.Send(ent->Description());
  }
  else
    SW.SendUndef();

  SW.Send(ent->RelatingGroup());

  SW.Send(ent->RelatedGroup());
}

void RWStepBasic_RWGroupRelationship::Share(const occ::handle<StepBasic_GroupRelationship>& ent,
                                            Interface_EntityIterator& iter) const
{

  iter.AddItem(ent->RelatingGroup());

  iter.AddItem(ent->RelatedGroup());
}
