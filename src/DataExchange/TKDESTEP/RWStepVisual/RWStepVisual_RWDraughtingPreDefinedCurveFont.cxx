

#include "RWStepVisual_RWDraughtingPreDefinedCurveFont.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_DraughtingPreDefinedCurveFont.hpp>

RWStepVisual_RWDraughtingPreDefinedCurveFont::RWStepVisual_RWDraughtingPreDefinedCurveFont() =
  default;

void RWStepVisual_RWDraughtingPreDefinedCurveFont::ReadStep(
  const occ::handle<StepData_StepReaderData>&                  data,
  const int                                                    num,
  occ::handle<Interface_Check>&                                ach,
  const occ::handle<StepVisual_DraughtingPreDefinedCurveFont>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "draughting_pre_defined_curve_font has not 1 parameter(s)"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  ent->Init(aName);
}

void RWStepVisual_RWDraughtingPreDefinedCurveFont::WriteStep(
  StepData_StepWriter&                                         SW,
  const occ::handle<StepVisual_DraughtingPreDefinedCurveFont>& ent) const
{

  SW.Send(ent->Name());
}
