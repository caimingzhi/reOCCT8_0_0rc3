

#include <Interface_Check.hpp>
#include "RWStepRepr_RWDescriptiveRepresentationItem.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_DescriptiveRepresentationItem.hpp>
#include <TCollection_HAsciiString.hpp>

RWStepRepr_RWDescriptiveRepresentationItem::RWStepRepr_RWDescriptiveRepresentationItem() = default;

void RWStepRepr_RWDescriptiveRepresentationItem::ReadStep(
  const occ::handle<StepData_StepReaderData>&                data,
  const int                                                  num,
  occ::handle<Interface_Check>&                              ach,
  const occ::handle<StepRepr_DescriptiveRepresentationItem>& ent) const
{

  if (data->NbParams(num) != 2 && data->NbParams(num) != 1)
  {
    occ::handle<TCollection_HAsciiString> errmess = new TCollection_HAsciiString(
      "Count of Parameters is not 1 or 2 for descriptive_representation_item");
    occ::handle<TCollection_HAsciiString> errmesso =
      new TCollection_HAsciiString("Count of Parameters is not %d or %d for %s");
    ach->AddFail(errmess->ToCString(), errmesso->ToCString());
    return;
  }

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<TCollection_HAsciiString> aDescription;

  data->ReadString(num, 2, "description", ach, aDescription);

  ent->Init(aName, aDescription);
}

void RWStepRepr_RWDescriptiveRepresentationItem::WriteStep(
  StepData_StepWriter&                                       SW,
  const occ::handle<StepRepr_DescriptiveRepresentationItem>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Description());
}
