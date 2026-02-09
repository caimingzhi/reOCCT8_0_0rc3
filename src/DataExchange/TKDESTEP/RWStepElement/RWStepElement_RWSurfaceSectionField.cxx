#include <Interface_EntityIterator.hpp>
#include "RWStepElement_RWSurfaceSectionField.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepElement_SurfaceSectionField.hpp>

RWStepElement_RWSurfaceSectionField::RWStepElement_RWSurfaceSectionField() = default;

void RWStepElement_RWSurfaceSectionField::ReadStep(
  const occ::handle<StepData_StepReaderData>& data,
  const int                                   num,
  occ::handle<Interface_Check>&               ach,
  const occ::handle<StepElement_SurfaceSectionField>&) const
{

  if (!data->CheckNbParams(num, 0, ach, "surface_section_field"))
    return;
}

void RWStepElement_RWSurfaceSectionField::WriteStep(
  StepData_StepWriter&,
  const occ::handle<StepElement_SurfaceSectionField>&) const
{
}

void RWStepElement_RWSurfaceSectionField::Share(const occ::handle<StepElement_SurfaceSectionField>&,
                                                Interface_EntityIterator&) const
{
}
