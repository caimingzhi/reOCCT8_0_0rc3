

#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWProductDefinitionEffectivity.hpp"
#include <StepBasic_ProductDefinitionEffectivity.hpp>
#include <StepBasic_ProductDefinitionRelationship.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <TCollection_HAsciiString.hpp>

RWStepBasic_RWProductDefinitionEffectivity::RWStepBasic_RWProductDefinitionEffectivity() = default;

void RWStepBasic_RWProductDefinitionEffectivity::ReadStep(
  const occ::handle<StepData_StepReaderData>&                data,
  const int                                                  num,
  occ::handle<Interface_Check>&                              ach,
  const occ::handle<StepBasic_ProductDefinitionEffectivity>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "product_definition_effectivity"))
    return;

  occ::handle<TCollection_HAsciiString> aId;

  data->ReadString(num, 1, "id", ach, aId);

  occ::handle<StepBasic_ProductDefinitionRelationship> aUsage;

  data->ReadEntity(num,
                   2,
                   "kind",
                   ach,
                   STANDARD_TYPE(StepBasic_ProductDefinitionRelationship),
                   aUsage);

  ent->Init(aId, aUsage);
}

void RWStepBasic_RWProductDefinitionEffectivity::WriteStep(
  StepData_StepWriter&                                       SW,
  const occ::handle<StepBasic_ProductDefinitionEffectivity>& ent) const
{

  SW.Send(ent->Id());
  SW.Send(ent->Usage());
}

void RWStepBasic_RWProductDefinitionEffectivity::Share(
  const occ::handle<StepBasic_ProductDefinitionEffectivity>& ent,
  Interface_EntityIterator&                                  iter) const
{
  iter.AddItem(ent->Usage());
}
