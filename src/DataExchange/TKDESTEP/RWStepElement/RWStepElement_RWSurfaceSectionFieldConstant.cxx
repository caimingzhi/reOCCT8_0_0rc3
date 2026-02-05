#include <Interface_EntityIterator.hpp>
#include "RWStepElement_RWSurfaceSectionFieldConstant.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepElement_SurfaceSection.hpp>
#include <StepElement_SurfaceSectionFieldConstant.hpp>

//=================================================================================================

RWStepElement_RWSurfaceSectionFieldConstant::RWStepElement_RWSurfaceSectionFieldConstant() =
  default;

//=================================================================================================

void RWStepElement_RWSurfaceSectionFieldConstant::ReadStep(
  const occ::handle<StepData_StepReaderData>&                 data,
  const int                                                   num,
  occ::handle<Interface_Check>&                               ach,
  const occ::handle<StepElement_SurfaceSectionFieldConstant>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 1, ach, "surface_section_field_constant"))
    return;

  // Own fields of SurfaceSectionFieldConstant

  occ::handle<StepElement_SurfaceSection> aDefinition;
  data
    ->ReadEntity(num, 1, "definition", ach, STANDARD_TYPE(StepElement_SurfaceSection), aDefinition);

  // Initialize entity
  ent->Init(aDefinition);
}

//=================================================================================================

void RWStepElement_RWSurfaceSectionFieldConstant::WriteStep(
  StepData_StepWriter&                                        SW,
  const occ::handle<StepElement_SurfaceSectionFieldConstant>& ent) const
{

  // Own fields of SurfaceSectionFieldConstant

  SW.Send(ent->Definition());
}

//=================================================================================================

void RWStepElement_RWSurfaceSectionFieldConstant::Share(
  const occ::handle<StepElement_SurfaceSectionFieldConstant>& ent,
  Interface_EntityIterator&                                   iter) const
{

  // Own fields of SurfaceSectionFieldConstant

  iter.AddItem(ent->Definition());
}
