

#include "RWStepVisual_RWPresentationSet.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_PresentationSet.hpp>

RWStepVisual_RWPresentationSet::RWStepVisual_RWPresentationSet() = default;

void RWStepVisual_RWPresentationSet::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                              const int                                   num,
                                              occ::handle<Interface_Check>&               ach,
                                              const occ::handle<StepVisual_PresentationSet>&) const
{

  if (!data->CheckNbParams(num, 0, ach, "presentation_set"))
    return;
}

void RWStepVisual_RWPresentationSet::WriteStep(StepData_StepWriter&,
                                               const occ::handle<StepVisual_PresentationSet>&) const
{
}
