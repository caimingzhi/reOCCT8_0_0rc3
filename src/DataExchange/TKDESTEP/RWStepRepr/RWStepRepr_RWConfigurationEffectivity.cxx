#include <Interface_EntityIterator.hpp>
#include "RWStepRepr_RWConfigurationEffectivity.hpp"
#include <StepBasic_ProductDefinitionRelationship.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_ConfigurationDesign.hpp>
#include <StepRepr_ConfigurationEffectivity.hpp>

RWStepRepr_RWConfigurationEffectivity::RWStepRepr_RWConfigurationEffectivity() = default;

void RWStepRepr_RWConfigurationEffectivity::ReadStep(
  const occ::handle<StepData_StepReaderData>&           data,
  const int                                             num,
  occ::handle<Interface_Check>&                         ach,
  const occ::handle<StepRepr_ConfigurationEffectivity>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "configuration_effectivity"))
    return;

  occ::handle<TCollection_HAsciiString> aEffectivity_Id;
  data->ReadString(num, 1, "effectivity.id", ach, aEffectivity_Id);

  occ::handle<StepBasic_ProductDefinitionRelationship> aProductDefinitionEffectivity_Usage;
  data->ReadEntity(num,
                   2,
                   "product_definition_effectivity.usage",
                   ach,
                   STANDARD_TYPE(StepBasic_ProductDefinitionRelationship),
                   aProductDefinitionEffectivity_Usage);

  occ::handle<StepRepr_ConfigurationDesign> aConfiguration;
  data->ReadEntity(num,
                   3,
                   "configuration",
                   ach,
                   STANDARD_TYPE(StepRepr_ConfigurationDesign),
                   aConfiguration);

  ent->Init(aEffectivity_Id, aProductDefinitionEffectivity_Usage, aConfiguration);
}

void RWStepRepr_RWConfigurationEffectivity::WriteStep(
  StepData_StepWriter&                                  SW,
  const occ::handle<StepRepr_ConfigurationEffectivity>& ent) const
{

  SW.Send(ent->StepBasic_Effectivity::Id());

  SW.Send(ent->StepBasic_ProductDefinitionEffectivity::Usage());

  SW.Send(ent->Configuration());
}

void RWStepRepr_RWConfigurationEffectivity::Share(
  const occ::handle<StepRepr_ConfigurationEffectivity>& ent,
  Interface_EntityIterator&                             iter) const
{

  iter.AddItem(ent->StepBasic_ProductDefinitionEffectivity::Usage());

  iter.AddItem(ent->Configuration());
}
