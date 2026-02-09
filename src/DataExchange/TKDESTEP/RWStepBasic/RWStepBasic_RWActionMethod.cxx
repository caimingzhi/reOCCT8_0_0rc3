#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWActionMethod.hpp"
#include <StepBasic_ActionMethod.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWActionMethod::RWStepBasic_RWActionMethod() = default;

void RWStepBasic_RWActionMethod::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                          const int                                   num,
                                          occ::handle<Interface_Check>&               ach,
                                          const occ::handle<StepBasic_ActionMethod>&  ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "action_method"))
    return;

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<TCollection_HAsciiString> aDescription;
  bool                                  hasDescription = true;
  if (data->IsParamDefined(num, 2))
  {
    data->ReadString(num, 2, "description", ach, aDescription);
  }
  else
  {
    hasDescription = false;
  }

  occ::handle<TCollection_HAsciiString> aConsequence;
  data->ReadString(num, 3, "consequence", ach, aConsequence);

  occ::handle<TCollection_HAsciiString> aPurpose;
  data->ReadString(num, 4, "purpose", ach, aPurpose);

  ent->Init(aName, hasDescription, aDescription, aConsequence, aPurpose);
}

void RWStepBasic_RWActionMethod::WriteStep(StepData_StepWriter&                       SW,
                                           const occ::handle<StepBasic_ActionMethod>& ent) const
{

  SW.Send(ent->Name());

  if (ent->HasDescription())
  {
    SW.Send(ent->Description());
  }
  else
    SW.SendUndef();

  SW.Send(ent->Consequence());

  SW.Send(ent->Purpose());
}

void RWStepBasic_RWActionMethod::Share(const occ::handle<StepBasic_ActionMethod>&,
                                       Interface_EntityIterator&) const
{
}
