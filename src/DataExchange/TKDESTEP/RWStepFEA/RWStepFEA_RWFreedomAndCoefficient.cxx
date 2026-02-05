#include <Interface_EntityIterator.hpp>
#include "RWStepFEA_RWFreedomAndCoefficient.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepFEA_FreedomAndCoefficient.hpp>

//=================================================================================================

RWStepFEA_RWFreedomAndCoefficient::RWStepFEA_RWFreedomAndCoefficient() = default;

//=================================================================================================

void RWStepFEA_RWFreedomAndCoefficient::ReadStep(
  const occ::handle<StepData_StepReaderData>&       data,
  const int                                         num,
  occ::handle<Interface_Check>&                     ach,
  const occ::handle<StepFEA_FreedomAndCoefficient>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 2, ach, "freedom_and_coefficient"))
    return;

  // Own fields of FreedomAndCoefficient

  StepFEA_DegreeOfFreedom aFreedom;
  data->ReadEntity(num, 1, "freedom", ach, aFreedom);

  StepElement_MeasureOrUnspecifiedValue aA;
  data->ReadEntity(num, 2, "a", ach, aA);

  // Initialize entity
  ent->Init(aFreedom, aA);
}

//=================================================================================================

void RWStepFEA_RWFreedomAndCoefficient::WriteStep(
  StepData_StepWriter&                              SW,
  const occ::handle<StepFEA_FreedomAndCoefficient>& ent) const
{

  // Own fields of FreedomAndCoefficient

  SW.Send(ent->Freedom().Value());

  SW.Send(ent->A().Value());
}

//=================================================================================================

void RWStepFEA_RWFreedomAndCoefficient::Share(const occ::handle<StepFEA_FreedomAndCoefficient>& ent,
                                              Interface_EntityIterator& iter) const
{

  // Own fields of FreedomAndCoefficient

  iter.AddItem(ent->Freedom().Value());

  iter.AddItem(ent->A().Value());
}
