#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWProductDefinitionReference.hpp"
#include <StepBasic_ExternalSource.hpp>
#include <StepBasic_ProductDefinitionReference.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWProductDefinitionReference::RWStepBasic_RWProductDefinitionReference() = default;

void RWStepBasic_RWProductDefinitionReference::ReadStep(
  const occ::handle<StepData_StepReaderData>&              data,
  const int                                                num,
  occ::handle<Interface_Check>&                            ach,
  const occ::handle<StepBasic_ProductDefinitionReference>& ent) const
{

  if (!data->CheckNbParams(num, 5, ach, "product_definition_reference"))
    return;

  occ::handle<StepBasic_ExternalSource> aSource;
  data->ReadEntity(num, 1, "source", ach, STANDARD_TYPE(StepBasic_ExternalSource), aSource);

  occ::handle<TCollection_HAsciiString> aProductId;
  data->ReadString(num, 2, "product_id", ach, aProductId);

  occ::handle<TCollection_HAsciiString> aProductDefinitionFormationId;
  data->ReadString(num, 3, "product_definition_formation_id", ach, aProductDefinitionFormationId);

  occ::handle<TCollection_HAsciiString> aProductDefinitionId;
  data->ReadString(num, 4, "product_definition_id", ach, aProductDefinitionId);

  occ::handle<TCollection_HAsciiString> aIdOwningOrganizationName;
  if (data->IsParamDefined(num, 5))
  {
    data->ReadString(num, 5, "id_owning_organization_name", ach, aIdOwningOrganizationName);
  }

  ent->Init(aSource,
            aProductId,
            aProductDefinitionFormationId,
            aProductDefinitionId,
            aIdOwningOrganizationName);
}

void RWStepBasic_RWProductDefinitionReference::WriteStep(
  StepData_StepWriter&                                     SW,
  const occ::handle<StepBasic_ProductDefinitionReference>& ent) const
{

  SW.Send(ent->Source());

  SW.Send(ent->ProductId());

  SW.Send(ent->ProductDefinitionFormationId());

  SW.Send(ent->ProductDefinitionId());

  if (ent->HasIdOwningOrganizationName())
    SW.Send(ent->IdOwningOrganizationName());
  else
    SW.SendUndef();
}

void RWStepBasic_RWProductDefinitionReference::Share(
  const occ::handle<StepBasic_ProductDefinitionReference>& ent,
  Interface_EntityIterator&                                iter) const
{
  iter.GetOneItem(ent->Source());
}
