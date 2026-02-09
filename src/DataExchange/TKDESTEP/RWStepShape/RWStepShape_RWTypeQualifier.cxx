

#include "RWStepShape_RWTypeQualifier.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_TypeQualifier.hpp>

RWStepShape_RWTypeQualifier::RWStepShape_RWTypeQualifier() = default;

void RWStepShape_RWTypeQualifier::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                           const int                                   num,
                                           occ::handle<Interface_Check>&               ach,
                                           const occ::handle<StepShape_TypeQualifier>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "type_qualifier"))
    return;

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);

  ent->Init(aName);
}

void RWStepShape_RWTypeQualifier::WriteStep(StepData_StepWriter&                        SW,
                                            const occ::handle<StepShape_TypeQualifier>& ent) const
{
  SW.Send(ent->Name());
}
