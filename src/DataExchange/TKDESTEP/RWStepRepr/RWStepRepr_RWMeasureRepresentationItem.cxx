#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_MSG.hpp>
#include "RWStepRepr_RWMeasureRepresentationItem.hpp"
#include <StepBasic_MeasureValueMember.hpp>
#include <StepBasic_MeasureWithUnit.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_MeasureRepresentationItem.hpp>

RWStepRepr_RWMeasureRepresentationItem::RWStepRepr_RWMeasureRepresentationItem() = default;

void RWStepRepr_RWMeasureRepresentationItem::ReadStep(
  const occ::handle<StepData_StepReaderData>&            data,
  const int                                              num,
  occ::handle<Interface_Check>&                          ach,
  const occ::handle<StepRepr_MeasureRepresentationItem>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "measure_representation_item"))
    return;

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepBasic_MeasureValueMember> mvc = new StepBasic_MeasureValueMember;
  data->ReadMember(num, 2, "value_component", ach, mvc);

  StepBasic_Unit aUnitComponent;
  data->ReadEntity(num, 3, "unit_component", ach, aUnitComponent);

  ent->Init(aName, mvc, aUnitComponent);
}

void RWStepRepr_RWMeasureRepresentationItem::WriteStep(
  StepData_StepWriter&                                   SW,
  const occ::handle<StepRepr_MeasureRepresentationItem>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Measure()->ValueComponentMember());

  SW.Send(ent->Measure()->UnitComponent().Value());
}

void RWStepRepr_RWMeasureRepresentationItem::Share(
  const occ::handle<StepRepr_MeasureRepresentationItem>& ent,
  Interface_EntityIterator&                              iter) const
{

  iter.GetOneItem(ent->Measure()->UnitComponent().Value());
}
