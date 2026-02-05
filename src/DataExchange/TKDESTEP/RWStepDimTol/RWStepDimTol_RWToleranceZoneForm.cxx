#include "RWStepDimTol_RWToleranceZoneForm.hpp"

#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepDimTol_ToleranceZoneForm.hpp>

//=================================================================================================

RWStepDimTol_RWToleranceZoneForm::RWStepDimTol_RWToleranceZoneForm() = default;

//=================================================================================================

void RWStepDimTol_RWToleranceZoneForm::ReadStep(
  const occ::handle<StepData_StepReaderData>&      data,
  const int                                        num,
  occ::handle<Interface_Check>&                    ach,
  const occ::handle<StepDimTol_ToleranceZoneForm>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 1, ach, "tolerance_zone_form"))
    return;

  // Own fields of ToleranceZoneForm

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);

  // Initialize entity
  ent->Init(aName);
}

//=================================================================================================

void RWStepDimTol_RWToleranceZoneForm::WriteStep(
  StepData_StepWriter&                             SW,
  const occ::handle<StepDimTol_ToleranceZoneForm>& ent) const
{
  SW.Send(ent->Name());
}
