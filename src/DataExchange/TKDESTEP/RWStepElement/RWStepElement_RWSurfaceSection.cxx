#include <Interface_EntityIterator.hpp>
#include "RWStepElement_RWSurfaceSection.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepElement_SurfaceSection.hpp>

RWStepElement_RWSurfaceSection::RWStepElement_RWSurfaceSection() = default;

void RWStepElement_RWSurfaceSection::ReadStep(
  const occ::handle<StepData_StepReaderData>&    data,
  const int                                      num,
  occ::handle<Interface_Check>&                  ach,
  const occ::handle<StepElement_SurfaceSection>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "surface_section"))
    return;

  StepElement_MeasureOrUnspecifiedValue aOffset;
  data->ReadEntity(num, 1, "offset", ach, aOffset);

  StepElement_MeasureOrUnspecifiedValue aNonStructuralMass;
  data->ReadEntity(num, 2, "non_structural_mass", ach, aNonStructuralMass);

  StepElement_MeasureOrUnspecifiedValue aNonStructuralMassOffset;
  data->ReadEntity(num, 3, "non_structural_mass_offset", ach, aNonStructuralMassOffset);

  ent->Init(aOffset, aNonStructuralMass, aNonStructuralMassOffset);
}

void RWStepElement_RWSurfaceSection::WriteStep(
  StepData_StepWriter&                           SW,
  const occ::handle<StepElement_SurfaceSection>& ent) const
{

  SW.Send(ent->Offset().Value());

  SW.Send(ent->NonStructuralMass().Value());

  SW.Send(ent->NonStructuralMassOffset().Value());
}

void RWStepElement_RWSurfaceSection::Share(const occ::handle<StepElement_SurfaceSection>&,
                                           Interface_EntityIterator&) const
{
}
