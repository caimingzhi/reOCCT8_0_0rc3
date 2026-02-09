

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWRatioMeasureWithUnit.hpp"
#include <StepBasic_MeasureValueMember.hpp>
#include <StepBasic_RatioMeasureWithUnit.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWRatioMeasureWithUnit::RWStepBasic_RWRatioMeasureWithUnit() = default;

void RWStepBasic_RWRatioMeasureWithUnit::ReadStep(
  const occ::handle<StepData_StepReaderData>&        data,
  const int                                          num,
  occ::handle<Interface_Check>&                      ach,
  const occ::handle<StepBasic_RatioMeasureWithUnit>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "ratio_measure_with_unit"))
    return;

  occ::handle<StepBasic_MeasureValueMember> mvc = new StepBasic_MeasureValueMember;
  data->ReadMember(num, 1, "value_component", ach, mvc);

  StepBasic_Unit aUnitComponent;
  data->ReadEntity(num, 2, "unit_component", ach, aUnitComponent);

  ent->Init(mvc, aUnitComponent);
}

void RWStepBasic_RWRatioMeasureWithUnit::WriteStep(
  StepData_StepWriter&                               SW,
  const occ::handle<StepBasic_RatioMeasureWithUnit>& ent) const
{

  SW.Send(ent->ValueComponentMember());

  SW.Send(ent->UnitComponent().Value());
}

void RWStepBasic_RWRatioMeasureWithUnit::Share(
  const occ::handle<StepBasic_RatioMeasureWithUnit>& ent,
  Interface_EntityIterator&                          iter) const
{
  iter.GetOneItem(ent->UnitComponent().Value());
}
