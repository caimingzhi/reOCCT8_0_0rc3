

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_MSG.hpp>
#include "RWStepBasic_RWUncertaintyMeasureWithUnit.hpp"
#include <StepBasic_MeasureValueMember.hpp>
#include <StepBasic_UncertaintyMeasureWithUnit.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWUncertaintyMeasureWithUnit::RWStepBasic_RWUncertaintyMeasureWithUnit() = default;

void RWStepBasic_RWUncertaintyMeasureWithUnit::ReadStep(
  const occ::handle<StepData_StepReaderData>&              data,
  const int                                                num,
  occ::handle<Interface_Check>&                            ach,
  const occ::handle<StepBasic_UncertaintyMeasureWithUnit>& ent) const
{
  if (data->IsComplex(num))
  {

    ach->AddWarning("Complex Type not allowed, only suitable values are read");

    int num1 = num;

    num1 = data->NextForComplex(num1);

    if (!data->CheckNbParams(num1, 2, ach, "measure_with_unit"))
      return;

    occ::handle<StepBasic_MeasureValueMember> mvc = new StepBasic_MeasureValueMember;
    data->ReadMember(num1, 1, "value_component", ach, mvc);

    StepBasic_Unit aUnitComponent;
    data->ReadEntity(num1, 2, "unit_component", ach, aUnitComponent);

    num1 = data->NextForComplex(num1);

    if (!data->CheckNbParams(num1, 2, ach, "uncertainty_measure_with_unit"))
      return;

    occ::handle<TCollection_HAsciiString> aName;
    data->ReadString(num1, 1, "name", ach, aName);

    occ::handle<TCollection_HAsciiString> aDescription;
    if (data->IsParamDefined(num1, 2))
    {
      data->ReadString(num1, 2, "description", ach, aDescription);
    }

    ent->Init(mvc, aUnitComponent, aName, aDescription);
    return;
  }

  if (!data->CheckNbParams(num, 4, ach, "uncertainty_measure_with_unit"))
    return;

  occ::handle<StepBasic_MeasureValueMember> mvc = new StepBasic_MeasureValueMember;
  data->ReadMember(num, 1, "value_component", ach, mvc);

  StepBasic_Unit aUnitComponent;
  data->ReadEntity(num, 2, "unit_component", ach, aUnitComponent);

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 3, "name", ach, aName);

  occ::handle<TCollection_HAsciiString> aDescription;
  data->ReadString(num, 4, "description", ach, aDescription);

  ent->Init(mvc, aUnitComponent, aName, aDescription);
}

void RWStepBasic_RWUncertaintyMeasureWithUnit::WriteStep(
  StepData_StepWriter&                                     SW,
  const occ::handle<StepBasic_UncertaintyMeasureWithUnit>& ent) const
{

  SW.Send(ent->ValueComponentMember());

  SW.Send(ent->UnitComponent().Value());

  SW.Send(ent->Name());

  SW.Send(ent->Description());
}

void RWStepBasic_RWUncertaintyMeasureWithUnit::Share(
  const occ::handle<StepBasic_UncertaintyMeasureWithUnit>& ent,
  Interface_EntityIterator&                                iter) const
{

  iter.GetOneItem(ent->UnitComponent().Value());
}
