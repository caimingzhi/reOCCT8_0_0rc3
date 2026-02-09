

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWMassMeasureWithUnit.hpp"
#include <StepBasic_MassMeasureWithUnit.hpp>
#include <StepBasic_MeasureValueMember.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWMassMeasureWithUnit::RWStepBasic_RWMassMeasureWithUnit() = default;

void RWStepBasic_RWMassMeasureWithUnit::ReadStep(
  const occ::handle<StepData_StepReaderData>&       data,
  const int                                         num,
  occ::handle<Interface_Check>&                     ach,
  const occ::handle<StepBasic_MassMeasureWithUnit>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "Mass_measure_with_unit"))
    return;

  occ::handle<StepBasic_MeasureValueMember> mvc = new StepBasic_MeasureValueMember;
  data->ReadMember(num, 1, "value_component", ach, mvc);

  StepBasic_Unit aUnitComponent;
  data->ReadEntity(num, 2, "unit_component", ach, aUnitComponent);

  ent->Init(mvc, aUnitComponent);
}

void RWStepBasic_RWMassMeasureWithUnit::WriteStep(
  StepData_StepWriter&                              SW,
  const occ::handle<StepBasic_MassMeasureWithUnit>& ent) const
{

  SW.Send(ent->ValueComponentMember());

  SW.Send(ent->UnitComponent().Value());
}

void RWStepBasic_RWMassMeasureWithUnit::Share(const occ::handle<StepBasic_MassMeasureWithUnit>& ent,
                                              Interface_EntityIterator& iter) const
{
  iter.GetOneItem(ent->UnitComponent().Value());
}
