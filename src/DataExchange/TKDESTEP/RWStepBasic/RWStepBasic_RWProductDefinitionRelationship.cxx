#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWProductDefinitionRelationship.hpp"
#include <StepBasic_ProductDefinitionRelationship.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWProductDefinitionRelationship::RWStepBasic_RWProductDefinitionRelationship() =
  default;

void RWStepBasic_RWProductDefinitionRelationship::ReadStep(
  const occ::handle<StepData_StepReaderData>&                 data,
  const int                                                   num,
  occ::handle<Interface_Check>&                               ach,
  const occ::handle<StepBasic_ProductDefinitionRelationship>& ent) const
{

  if (!data->CheckNbParams(num, 5, ach, "product_definition_relationship"))
    return;

  occ::handle<TCollection_HAsciiString> aId;
  data->ReadString(num, 1, "id", ach, aId);

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 2, "name", ach, aName);

  occ::handle<TCollection_HAsciiString> aDescription;
  bool                                  hasDescription = true;
  if (data->IsParamDefined(num, 3))
  {
    data->ReadString(num, 3, "description", ach, aDescription);
  }
  else
  {
    hasDescription = false;
  }

  StepBasic_ProductDefinitionOrReference aRelatingProductDefinition;
  data->ReadEntity(num, 4, "relating_product_definition", ach, aRelatingProductDefinition);

  StepBasic_ProductDefinitionOrReference aRelatedProductDefinition;
  data->ReadEntity(num, 5, "related_product_definition", ach, aRelatedProductDefinition);

  ent->Init(aId,
            aName,
            hasDescription,
            aDescription,
            aRelatingProductDefinition,
            aRelatedProductDefinition);
}

void RWStepBasic_RWProductDefinitionRelationship::WriteStep(
  StepData_StepWriter&                                        SW,
  const occ::handle<StepBasic_ProductDefinitionRelationship>& ent) const
{

  SW.Send(ent->Id());

  SW.Send(ent->Name());

  if (ent->HasDescription())
  {
    SW.Send(ent->Description());
  }
  else
    SW.SendUndef();

  SW.Send(ent->RelatingProductDefinitionAP242().Value());

  SW.Send(ent->RelatedProductDefinitionAP242().Value());
}

void RWStepBasic_RWProductDefinitionRelationship::Share(
  const occ::handle<StepBasic_ProductDefinitionRelationship>& ent,
  Interface_EntityIterator&                                   iter) const
{

  iter.AddItem(ent->RelatingProductDefinitionAP242().Value());

  iter.AddItem(ent->RelatedProductDefinitionAP242().Value());
}
