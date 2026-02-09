

#include "RWStepVisual_RWPreDefinedCurveFont.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_PreDefinedCurveFont.hpp>

RWStepVisual_RWPreDefinedCurveFont::RWStepVisual_RWPreDefinedCurveFont() = default;

void RWStepVisual_RWPreDefinedCurveFont::ReadStep(
  const occ::handle<StepData_StepReaderData>&        data,
  const int                                          num,
  occ::handle<Interface_Check>&                      ach,
  const occ::handle<StepVisual_PreDefinedCurveFont>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "pre_defined_curve_font"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  ent->Init(aName);
}

void RWStepVisual_RWPreDefinedCurveFont::WriteStep(
  StepData_StepWriter&                               SW,
  const occ::handle<StepVisual_PreDefinedCurveFont>& ent) const
{

  SW.Send(ent->Name());
}
