#include <Interface_Check.hpp>
#include "RWStepRepr_RWValueRepresentationItem.hpp"
#include <StepBasic_MeasureValueMember.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_ValueRepresentationItem.hpp>
#include <TCollection_HAsciiString.hpp>

RWStepRepr_RWValueRepresentationItem::RWStepRepr_RWValueRepresentationItem() = default;

void RWStepRepr_RWValueRepresentationItem::ReadStep(
  const occ::handle<StepData_StepReaderData>&          data,
  const int                                            num,
  occ::handle<Interface_Check>&                        ach,
  const occ::handle<StepRepr_ValueRepresentationItem>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "value_representation_item"))
    return;

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepBasic_MeasureValueMember> aMember = new StepBasic_MeasureValueMember;
  data->ReadMember(num, 2, "value_component", ach, aMember);

  ent->Init(aName, aMember);
}

void RWStepRepr_RWValueRepresentationItem::WriteStep(
  StepData_StepWriter&                                 SW,
  const occ::handle<StepRepr_ValueRepresentationItem>& ent) const
{
  SW.Send(ent->Name());
  SW.Send(ent->ValueComponentMember());
}
