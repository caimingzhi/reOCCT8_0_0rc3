

#include "RWStepRepr_RWRepresentationContextReference.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_RepresentationContextReference.hpp>
#include <TCollection_HAsciiString.hpp>

RWStepRepr_RWRepresentationContextReference::RWStepRepr_RWRepresentationContextReference() =
  default;

void RWStepRepr_RWRepresentationContextReference::ReadStep(
  const occ::handle<StepData_StepReaderData>&                 theData,
  const int                                                   theNum,
  occ::handle<Interface_Check>&                               theAch,
  const occ::handle<StepRepr_RepresentationContextReference>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 1, theAch, "representation_context_reference"))
    return;

  occ::handle<TCollection_HAsciiString> aContextIdentifier;
  theData->ReadString(theNum, 1, "context_identifier", theAch, aContextIdentifier);

  theEnt->Init(aContextIdentifier);
}

void RWStepRepr_RWRepresentationContextReference::WriteStep(
  StepData_StepWriter&                                        theSW,
  const occ::handle<StepRepr_RepresentationContextReference>& theEnt) const
{

  theSW.Send(theEnt->ContextIdentifier());
}

void RWStepRepr_RWRepresentationContextReference::Share(
  const occ::handle<StepRepr_RepresentationContextReference>&,
  Interface_EntityIterator&) const
{
}
