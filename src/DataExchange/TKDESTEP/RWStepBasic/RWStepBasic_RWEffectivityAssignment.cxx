#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWEffectivityAssignment.hpp"
#include <StepBasic_Effectivity.hpp>
#include <StepBasic_EffectivityAssignment.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

//=================================================================================================

RWStepBasic_RWEffectivityAssignment::RWStepBasic_RWEffectivityAssignment() = default;

//=================================================================================================

void RWStepBasic_RWEffectivityAssignment::ReadStep(
  const occ::handle<StepData_StepReaderData>&         data,
  const int                                           num,
  occ::handle<Interface_Check>&                       ach,
  const occ::handle<StepBasic_EffectivityAssignment>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 1, ach, "effectivity_assignment"))
    return;

  // Own fields of EffectivityAssignment

  occ::handle<StepBasic_Effectivity> aAssignedEffectivity;
  data->ReadEntity(num,
                   1,
                   "assigned_effectivity",
                   ach,
                   STANDARD_TYPE(StepBasic_Effectivity),
                   aAssignedEffectivity);

  // Initialize entity
  ent->Init(aAssignedEffectivity);
}

//=================================================================================================

void RWStepBasic_RWEffectivityAssignment::WriteStep(
  StepData_StepWriter&                                SW,
  const occ::handle<StepBasic_EffectivityAssignment>& ent) const
{

  // Own fields of EffectivityAssignment

  SW.Send(ent->AssignedEffectivity());
}

//=================================================================================================

void RWStepBasic_RWEffectivityAssignment::Share(
  const occ::handle<StepBasic_EffectivityAssignment>& ent,
  Interface_EntityIterator&                           iter) const
{

  // Own fields of EffectivityAssignment

  iter.AddItem(ent->AssignedEffectivity());
}
