

#include "RWStepRepr_RWFunctionallyDefinedTransformation.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_FunctionallyDefinedTransformation.hpp>

RWStepRepr_RWFunctionallyDefinedTransformation::RWStepRepr_RWFunctionallyDefinedTransformation() =
  default;

void RWStepRepr_RWFunctionallyDefinedTransformation::ReadStep(
  const occ::handle<StepData_StepReaderData>&                    data,
  const int                                                      num,
  occ::handle<Interface_Check>&                                  ach,
  const occ::handle<StepRepr_FunctionallyDefinedTransformation>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "functionally_defined_transformation"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<TCollection_HAsciiString> aDescription;
  if (data->IsParamDefined(num, 2))
  {

    data->ReadString(num, 2, "description", ach, aDescription);
  }

  ent->Init(aName, aDescription);
}

void RWStepRepr_RWFunctionallyDefinedTransformation::WriteStep(
  StepData_StepWriter&                                           SW,
  const occ::handle<StepRepr_FunctionallyDefinedTransformation>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Description());
}
