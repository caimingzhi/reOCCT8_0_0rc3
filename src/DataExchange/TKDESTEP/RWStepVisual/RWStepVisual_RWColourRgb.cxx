

#include "RWStepVisual_RWColourRgb.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_ColourRgb.hpp>

RWStepVisual_RWColourRgb::RWStepVisual_RWColourRgb() = default;

void RWStepVisual_RWColourRgb::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                        const int                                   num,
                                        occ::handle<Interface_Check>&               ach,
                                        const occ::handle<StepVisual_ColourRgb>&    ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "colour_rgb"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  double aRed;

  data->ReadReal(num, 2, "red", ach, aRed);

  double aGreen;

  data->ReadReal(num, 3, "green", ach, aGreen);

  double aBlue;

  data->ReadReal(num, 4, "blue", ach, aBlue);

  ent->Init(aName, aRed, aGreen, aBlue);
}

void RWStepVisual_RWColourRgb::WriteStep(StepData_StepWriter&                     SW,
                                         const occ::handle<StepVisual_ColourRgb>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Red());

  SW.Send(ent->Green());

  SW.Send(ent->Blue());
}
