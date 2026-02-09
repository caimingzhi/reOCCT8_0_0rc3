

#include "RWStepVisual_RWTessellatedStructuredItem.hpp"
#include <StepVisual_TessellatedStructuredItem.hpp>
#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <TCollection_HAsciiString.hpp>

RWStepVisual_RWTessellatedStructuredItem::RWStepVisual_RWTessellatedStructuredItem() = default;

void RWStepVisual_RWTessellatedStructuredItem::ReadStep(
  const occ::handle<StepData_StepReaderData>&              theData,
  const int                                                theNum,
  occ::handle<Interface_Check>&                            theCheck,
  const occ::handle<StepVisual_TessellatedStructuredItem>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 1, theCheck, "tessellated_structured_item"))
  {
    return;
  }

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  theData->ReadString(theNum, 1, "representation_item.name", theCheck, aRepresentationItem_Name);

  theEnt->Init(aRepresentationItem_Name);
}

void RWStepVisual_RWTessellatedStructuredItem::WriteStep(
  StepData_StepWriter&                                     theSW,
  const occ::handle<StepVisual_TessellatedStructuredItem>& theEnt) const
{

  theSW.Send(theEnt->Name());
}

void RWStepVisual_RWTessellatedStructuredItem::Share(
  const occ::handle<StepVisual_TessellatedStructuredItem>&,
  Interface_EntityIterator&) const
{
}
