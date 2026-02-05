#include <Interface_EntityIterator.hpp>
#include "RWStepRepr_RWConfigurationDesign.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_ConfigurationDesign.hpp>
#include <StepRepr_ConfigurationItem.hpp>

//=================================================================================================

RWStepRepr_RWConfigurationDesign::RWStepRepr_RWConfigurationDesign() = default;

//=================================================================================================

void RWStepRepr_RWConfigurationDesign::ReadStep(
  const occ::handle<StepData_StepReaderData>&      data,
  const int                                        num,
  occ::handle<Interface_Check>&                    ach,
  const occ::handle<StepRepr_ConfigurationDesign>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 2, ach, "configuration_design"))
    return;

  // Own fields of ConfigurationDesign

  occ::handle<StepRepr_ConfigurationItem> aConfiguration;
  data->ReadEntity(num,
                   1,
                   "configuration",
                   ach,
                   STANDARD_TYPE(StepRepr_ConfigurationItem),
                   aConfiguration);

  StepRepr_ConfigurationDesignItem aDesign;
  data->ReadEntity(num, 2, "design", ach, aDesign);

  // Initialize entity
  ent->Init(aConfiguration, aDesign);
}

//=================================================================================================

void RWStepRepr_RWConfigurationDesign::WriteStep(
  StepData_StepWriter&                             SW,
  const occ::handle<StepRepr_ConfigurationDesign>& ent) const
{

  // Own fields of ConfigurationDesign

  SW.Send(ent->Configuration());

  SW.Send(ent->Design().Value());
}

//=================================================================================================

void RWStepRepr_RWConfigurationDesign::Share(const occ::handle<StepRepr_ConfigurationDesign>& ent,
                                             Interface_EntityIterator& iter) const
{

  // Own fields of ConfigurationDesign

  iter.AddItem(ent->Configuration());

  iter.AddItem(ent->Design().Value());
}
