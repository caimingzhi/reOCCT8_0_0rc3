

#include "RWStepRepr_RWParametricRepresentationContext.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_ParametricRepresentationContext.hpp>

RWStepRepr_RWParametricRepresentationContext::RWStepRepr_RWParametricRepresentationContext() =
  default;

void RWStepRepr_RWParametricRepresentationContext::ReadStep(
  const occ::handle<StepData_StepReaderData>&                  data,
  const int                                                    num,
  occ::handle<Interface_Check>&                                ach,
  const occ::handle<StepRepr_ParametricRepresentationContext>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "parametric_representation_context"))
    return;

  occ::handle<TCollection_HAsciiString> aContextIdentifier;

  data->ReadString(num, 1, "context_identifier", ach, aContextIdentifier);

  occ::handle<TCollection_HAsciiString> aContextType;

  data->ReadString(num, 2, "context_type", ach, aContextType);

  ent->Init(aContextIdentifier, aContextType);
}

void RWStepRepr_RWParametricRepresentationContext::WriteStep(
  StepData_StepWriter&                                         SW,
  const occ::handle<StepRepr_ParametricRepresentationContext>& ent) const
{

  SW.Send(ent->ContextIdentifier());

  SW.Send(ent->ContextType());
}
