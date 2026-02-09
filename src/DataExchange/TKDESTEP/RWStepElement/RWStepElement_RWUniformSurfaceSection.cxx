#include <Interface_EntityIterator.hpp>
#include "RWStepElement_RWUniformSurfaceSection.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepElement_UniformSurfaceSection.hpp>

RWStepElement_RWUniformSurfaceSection::RWStepElement_RWUniformSurfaceSection() = default;

void RWStepElement_RWUniformSurfaceSection::ReadStep(
  const occ::handle<StepData_StepReaderData>&           data,
  const int                                             num,
  occ::handle<Interface_Check>&                         ach,
  const occ::handle<StepElement_UniformSurfaceSection>& ent) const
{

  if (!data->CheckNbParams(num, 6, ach, "uniform_surface_section"))
    return;

  StepElement_MeasureOrUnspecifiedValue aSurfaceSection_Offset;
  data->ReadEntity(num, 1, "surface_section.offset", ach, aSurfaceSection_Offset);

  StepElement_MeasureOrUnspecifiedValue aSurfaceSection_NonStructuralMass;
  data->ReadEntity(num,
                   2,
                   "surface_section.non_structural_mass",
                   ach,
                   aSurfaceSection_NonStructuralMass);

  StepElement_MeasureOrUnspecifiedValue aSurfaceSection_NonStructuralMassOffset;
  data->ReadEntity(num,
                   3,
                   "surface_section.non_structural_mass_offset",
                   ach,
                   aSurfaceSection_NonStructuralMassOffset);

  double aThickness;
  data->ReadReal(num, 4, "thickness", ach, aThickness);

  StepElement_MeasureOrUnspecifiedValue aBendingThickness;
  data->ReadEntity(num, 5, "bending_thickness", ach, aBendingThickness);

  StepElement_MeasureOrUnspecifiedValue aShearThickness;
  data->ReadEntity(num, 6, "shear_thickness", ach, aShearThickness);

  ent->Init(aSurfaceSection_Offset,
            aSurfaceSection_NonStructuralMass,
            aSurfaceSection_NonStructuralMassOffset,
            aThickness,
            aBendingThickness,
            aShearThickness);
}

void RWStepElement_RWUniformSurfaceSection::WriteStep(
  StepData_StepWriter&                                  SW,
  const occ::handle<StepElement_UniformSurfaceSection>& ent) const
{

  SW.Send(ent->StepElement_SurfaceSection::Offset().Value());

  SW.Send(ent->StepElement_SurfaceSection::NonStructuralMass().Value());

  SW.Send(ent->StepElement_SurfaceSection::NonStructuralMassOffset().Value());

  SW.Send(ent->Thickness());

  SW.Send(ent->BendingThickness().Value());

  SW.Send(ent->ShearThickness().Value());
}

void RWStepElement_RWUniformSurfaceSection::Share(
  const occ::handle<StepElement_UniformSurfaceSection>&,
  Interface_EntityIterator&) const
{
}
