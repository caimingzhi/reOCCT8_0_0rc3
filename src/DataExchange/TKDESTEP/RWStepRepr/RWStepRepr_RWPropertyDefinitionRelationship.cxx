#include <Interface_EntityIterator.hpp>
#include "RWStepRepr_RWPropertyDefinitionRelationship.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_PropertyDefinition.hpp>
#include <StepRepr_PropertyDefinitionRelationship.hpp>

RWStepRepr_RWPropertyDefinitionRelationship::RWStepRepr_RWPropertyDefinitionRelationship() =
  default;

void RWStepRepr_RWPropertyDefinitionRelationship::ReadStep(
  const occ::handle<StepData_StepReaderData>&                 data,
  const int                                                   num,
  occ::handle<Interface_Check>&                               ach,
  const occ::handle<StepRepr_PropertyDefinitionRelationship>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "property_definition_relationship"))
    return;

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<TCollection_HAsciiString> aDescription;
  data->ReadString(num, 2, "description", ach, aDescription);

  occ::handle<StepRepr_PropertyDefinition> aRelatingPropertyDefinition;
  data->ReadEntity(num,
                   3,
                   "relating_property_definition",
                   ach,
                   STANDARD_TYPE(StepRepr_PropertyDefinition),
                   aRelatingPropertyDefinition);

  occ::handle<StepRepr_PropertyDefinition> aRelatedPropertyDefinition;
  data->ReadEntity(num,
                   4,
                   "related_property_definition",
                   ach,
                   STANDARD_TYPE(StepRepr_PropertyDefinition),
                   aRelatedPropertyDefinition);

  ent->Init(aName, aDescription, aRelatingPropertyDefinition, aRelatedPropertyDefinition);
}

void RWStepRepr_RWPropertyDefinitionRelationship::WriteStep(
  StepData_StepWriter&                                        SW,
  const occ::handle<StepRepr_PropertyDefinitionRelationship>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Description());

  SW.Send(ent->RelatingPropertyDefinition());

  SW.Send(ent->RelatedPropertyDefinition());
}

void RWStepRepr_RWPropertyDefinitionRelationship::Share(
  const occ::handle<StepRepr_PropertyDefinitionRelationship>& ent,
  Interface_EntityIterator&                                   iter) const
{

  iter.AddItem(ent->RelatingPropertyDefinition());

  iter.AddItem(ent->RelatedPropertyDefinition());
}
