

#include "RWStepRepr_RWRepresentationReference.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_RepresentationReference.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationContextReference.hpp>

RWStepRepr_RWRepresentationReference::RWStepRepr_RWRepresentationReference() = default;

void RWStepRepr_RWRepresentationReference::ReadStep(
  const occ::handle<StepData_StepReaderData>&          theData,
  const int                                            theNum,
  occ::handle<Interface_Check>&                        theAch,
  const occ::handle<StepRepr_RepresentationReference>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 2, theAch, "representation_reference"))
    return;

  occ::handle<TCollection_HAsciiString> aId;
  theData->ReadString(theNum, 1, "id", theAch, aId);

  occ::handle<StepRepr_RepresentationContextReference> aContextOfItems;
  theData->ReadEntity(theNum,
                      2,
                      "context_of_items",
                      theAch,
                      STANDARD_TYPE(StepRepr_RepresentationContextReference),
                      aContextOfItems);

  theEnt->Init(aId, aContextOfItems);
}

void RWStepRepr_RWRepresentationReference::WriteStep(
  StepData_StepWriter&                                 SW,
  const occ::handle<StepRepr_RepresentationReference>& theEnt) const
{

  SW.Send(theEnt->Id());

  SW.Send(theEnt->ContextOfItems());
}

void RWStepRepr_RWRepresentationReference::Share(
  const occ::handle<StepRepr_RepresentationReference>& theEnt,
  Interface_EntityIterator&                            iter) const
{

  iter.AddItem(theEnt->ContextOfItems());
}
