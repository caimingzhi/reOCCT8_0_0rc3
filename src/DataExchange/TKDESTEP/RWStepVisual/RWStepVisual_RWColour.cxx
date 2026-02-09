

#include "RWStepVisual_RWColour.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_Colour.hpp>

RWStepVisual_RWColour::RWStepVisual_RWColour() = default;

void RWStepVisual_RWColour::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                     const int                                   num,
                                     occ::handle<Interface_Check>&               ach,
                                     const occ::handle<StepVisual_Colour>&) const
{

  if (!data->CheckNbParams(num, 0, ach, "colour"))
    return;
}

void RWStepVisual_RWColour::WriteStep(StepData_StepWriter&,
                                      const occ::handle<StepVisual_Colour>&) const
{
}
