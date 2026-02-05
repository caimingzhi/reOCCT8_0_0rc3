#include <Interface_EntityIterator.hpp>
#include "RWStepRepr_RWConfigurationEffectivity.hpp"
#include <StepBasic_ProductDefinitionRelationship.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_ConfigurationDesign.hpp>
#include <StepRepr_ConfigurationEffectivity.hpp>

//=================================================================================================

RWStepRepr_RWConfigurationEffectivity::RWStepRepr_RWConfigurationEffectivity() = default;

//=================================================================================================

void RWStepRepr_RWConfigurationEffectivity::ReadStep(
  const occ::handle<StepData_StepReaderData>&           data,
  const int                                             num,
  occ::handle<Interface_Check>&                         ach,
  const occ::handle<StepRepr_ConfigurationEffectivity>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 3, ach, "configuration_effectivity"))
    return;

  // Inherited fields of Effectivity

  occ::handle<TCollection_HAsciiString> aEffectivity_Id;
  data->ReadString(num, 1, "effectivity.id", ach, aEffectivity_Id);

  // Inherited fields of ProductDefinitionEffectivity

  occ::handle<StepBasic_ProductDefinitionRelationship> aProductDefinitionEffectivity_Usage;
  data->ReadEntity(num,
                   2,
                   "product_definition_effectivity.usage",
                   ach,
                   STANDARD_TYPE(StepBasic_ProductDefinitionRelationship),
                   aProductDefinitionEffectivity_Usage);

  // Own fields of ConfigurationEffectivity

  occ::handle<StepRepr_ConfigurationDesign> aConfiguration;
  data->ReadEntity(num,
                   3,
                   "configuration",
                   ach,
                   STANDARD_TYPE(StepRepr_ConfigurationDesign),
                   aConfiguration);

  // Initialize entity
  ent->Init(aEffectivity_Id, aProductDefinitionEffectivity_Usage, aConfiguration);
}

//=================================================================================================

void RWStepRepr_RWConfigurationEffectivity::WriteStep(
  StepData_StepWriter&                                  SW,
  const occ::handle<StepRepr_ConfigurationEffectivity>& ent) const
{

  // Inherited fields of Effectivity

  SW.Send(ent->StepBasic_Effectivity::Id());

  // Inherited fields of ProductDefinitionEffectivity

  SW.Send(ent->StepBasic_ProductDefinitionEffectivity::Usage());

  // Own fields of ConfigurationEffectivity

  SW.Send(ent->Configuration());
}

//=================================================================================================

void RWStepRepr_RWConfigurationEffectivity::Share(
  const occ::handle<StepRepr_ConfigurationEffectivity>& ent,
  Interface_EntityIterator&                             iter) const
{

  // Inherited fields of Effectivity

  // Inherited fields of ProductDefinitionEffectivity

  iter.AddItem(ent->StepBasic_ProductDefinitionEffectivity::Usage());

  // Own fields of ConfigurationEffectivity

  iter.AddItem(ent->Configuration());
}
