

#include "RWStepShape_RWPrecisionQualifier.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_PrecisionQualifier.hpp>

RWStepShape_RWPrecisionQualifier::RWStepShape_RWPrecisionQualifier() = default;

void RWStepShape_RWPrecisionQualifier::ReadStep(
  const occ::handle<StepData_StepReaderData>&      data,
  const int                                        num,
  occ::handle<Interface_Check>&                    ach,
  const occ::handle<StepShape_PrecisionQualifier>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "precision_qualifier"))
    return;

  int PV;
  data->ReadInteger(num, 1, "precision_value", ach, PV);

  ent->Init(PV);
}

void RWStepShape_RWPrecisionQualifier::WriteStep(
  StepData_StepWriter&                             SW,
  const occ::handle<StepShape_PrecisionQualifier>& ent) const
{
  SW.Send(ent->PrecisionValue());
}
