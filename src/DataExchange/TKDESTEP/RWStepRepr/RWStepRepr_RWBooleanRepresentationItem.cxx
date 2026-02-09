

#include "RWStepRepr_RWBooleanRepresentationItem.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_BooleanRepresentationItem.hpp>
#include <TCollection_HAsciiString.hpp>

RWStepRepr_RWBooleanRepresentationItem::RWStepRepr_RWBooleanRepresentationItem() = default;

void RWStepRepr_RWBooleanRepresentationItem::ReadStep(
  const occ::handle<StepData_StepReaderData>&            theData,
  const int                                              theNum,
  occ::handle<Interface_Check>&                          theAch,
  const occ::handle<StepRepr_BooleanRepresentationItem>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 2, theAch, "boolean_representation_item"))
    return;

  occ::handle<TCollection_HAsciiString> aName;
  theData->ReadString(theNum, 1, "name", theAch, aName);

  bool aValue;
  theData->ReadBoolean(theNum, 2, "value", theAch, aValue);

  theEnt->Init(aName, aValue);
}

void RWStepRepr_RWBooleanRepresentationItem::WriteStep(
  StepData_StepWriter&                                   theSW,
  const occ::handle<StepRepr_BooleanRepresentationItem>& theEnt) const
{
  theSW.Send(theEnt->Name());
  theSW.Send(theEnt->Value());
}
