

#include "RWStepRepr_RWRepresentationContext.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_RepresentationContext.hpp>

RWStepRepr_RWRepresentationContext::RWStepRepr_RWRepresentationContext() = default;

void RWStepRepr_RWRepresentationContext::ReadStep(
  const occ::handle<StepData_StepReaderData>&        data,
  const int                                          num,
  occ::handle<Interface_Check>&                      ach,
  const occ::handle<StepRepr_RepresentationContext>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "representation_context"))
    return;

  occ::handle<TCollection_HAsciiString> aContextIdentifier;

  data->ReadString(num, 1, "context_identifier", ach, aContextIdentifier);

  occ::handle<TCollection_HAsciiString> aContextType;

  data->ReadString(num, 2, "context_type", ach, aContextType);

  ent->Init(aContextIdentifier, aContextType);
}

void RWStepRepr_RWRepresentationContext::WriteStep(
  StepData_StepWriter&                               SW,
  const occ::handle<StepRepr_RepresentationContext>& ent) const
{

  SW.Send(ent->ContextIdentifier());

  SW.Send(ent->ContextType());
}
