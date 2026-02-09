

#include "RWStepRepr_RWRealRepresentationItem.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_RealRepresentationItem.hpp>
#include <TCollection_HAsciiString.hpp>

RWStepRepr_RWRealRepresentationItem::RWStepRepr_RWRealRepresentationItem() = default;

void RWStepRepr_RWRealRepresentationItem::ReadStep(
  const occ::handle<StepData_StepReaderData>&         theData,
  const int                                           theNum,
  occ::handle<Interface_Check>&                       theAch,
  const occ::handle<StepRepr_RealRepresentationItem>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 2, theAch, "real_representation_item"))
    return;

  occ::handle<TCollection_HAsciiString> aName;
  theData->ReadString(theNum, 1, "name", theAch, aName);

  double aValue;
  theData->ReadReal(theNum, 2, "value", theAch, aValue);

  theEnt->Init(aName, aValue);
}

void RWStepRepr_RWRealRepresentationItem::WriteStep(
  StepData_StepWriter&                                theSW,
  const occ::handle<StepRepr_RealRepresentationItem>& theEnt) const
{
  theSW.Send(theEnt->Name());
  theSW.Send(theEnt->Value());
}
