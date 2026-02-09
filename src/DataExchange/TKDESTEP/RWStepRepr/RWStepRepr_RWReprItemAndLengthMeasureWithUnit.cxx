

#include <Interface_Check.hpp>
#include "RWStepRepr_RWReprItemAndLengthMeasureWithUnit.hpp"
#include <StepBasic_MeasureValueMember.hpp>
#include <StepBasic_MeasureWithUnit.hpp>
#include <StepBasic_Unit.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_ReprItemAndLengthMeasureWithUnit.hpp>

RWStepRepr_RWReprItemAndLengthMeasureWithUnit::RWStepRepr_RWReprItemAndLengthMeasureWithUnit() =
  default;

void RWStepRepr_RWReprItemAndLengthMeasureWithUnit::ReadStep(
  const occ::handle<StepData_StepReaderData>&                   data,
  const int                                                     num0,
  occ::handle<Interface_Check>&                                 ach,
  const occ::handle<StepRepr_ReprItemAndLengthMeasureWithUnit>& ent) const
{
  int num = 0;
  data->NamedForComplex("MEASURE_WITH_UNIT", "MSWTUN", num0, num, ach);
  if (!data->CheckNbParams(num, 2, ach, "measure_with_unit"))
    return;

  occ::handle<StepBasic_MeasureValueMember> mvc = new StepBasic_MeasureValueMember;
  data->ReadMember(num, 1, "value_component", ach, mvc);

  StepBasic_Unit aUnitComponent;
  data->ReadEntity(num, 2, "unit_component", ach, aUnitComponent);
  occ::handle<StepBasic_MeasureWithUnit> aMeasureWithUnit = new StepBasic_MeasureWithUnit;
  aMeasureWithUnit->Init(mvc, aUnitComponent);

  data->NamedForComplex("REPRESENTATION_ITEM", "RPRITM", num0, num, ach);
  if (!data->CheckNbParams(num, 1, ach, "representation_item"))
    return;

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);
  occ::handle<StepRepr_RepresentationItem> aReprItem = new StepRepr_RepresentationItem;
  aReprItem->Init(aName);

  ent->Init(aMeasureWithUnit, aReprItem);
}

void RWStepRepr_RWReprItemAndLengthMeasureWithUnit::WriteStep(
  StepData_StepWriter&                                          SW,
  const occ::handle<StepRepr_ReprItemAndLengthMeasureWithUnit>& ent) const
{
  SW.StartEntity("LENGTH_MEASURE_WITH_UNIT");
  SW.StartEntity("MEASURE_REPRESENTATION_ITEM");
  SW.StartEntity("MEASURE_WITH_UNIT");
  SW.Send(ent->GetMeasureWithUnit()->ValueComponentMember());
  SW.Send(ent->GetMeasureWithUnit()->UnitComponent().Value());
  SW.StartEntity("REPRESENTATION_ITEM");
  SW.Send(ent->Name());
}
