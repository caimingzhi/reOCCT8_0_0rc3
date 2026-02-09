

#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWDerivedUnitElement.hpp"
#include <StepBasic_DerivedUnitElement.hpp>
#include <StepBasic_NamedUnit.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWDerivedUnitElement::RWStepBasic_RWDerivedUnitElement() = default;

void RWStepBasic_RWDerivedUnitElement::ReadStep(
  const occ::handle<StepData_StepReaderData>&      data,
  const int                                        num,
  occ::handle<Interface_Check>&                    ach,
  const occ::handle<StepBasic_DerivedUnitElement>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "derived_unit_element"))
    return;

  occ::handle<StepBasic_NamedUnit> nu;

  data->ReadEntity(num, 1, "unit", ach, STANDARD_TYPE(StepBasic_NamedUnit), nu);
  double expo;

  data->ReadReal(num, 2, "exponent", ach, expo);

  ent->Init(nu, expo);
}

void RWStepBasic_RWDerivedUnitElement::WriteStep(
  StepData_StepWriter&                             SW,
  const occ::handle<StepBasic_DerivedUnitElement>& ent) const
{

  SW.Send(ent->Unit());
  SW.Send(ent->Exponent());
}

void RWStepBasic_RWDerivedUnitElement::Share(const occ::handle<StepBasic_DerivedUnitElement>& ent,
                                             Interface_EntityIterator& iter) const
{

  iter.GetOneItem(ent->Unit());
}
