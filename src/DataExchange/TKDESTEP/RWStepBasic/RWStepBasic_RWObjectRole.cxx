#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWObjectRole.hpp"
#include <StepBasic_ObjectRole.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWObjectRole::RWStepBasic_RWObjectRole() = default;

void RWStepBasic_RWObjectRole::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                        const int                                   num,
                                        occ::handle<Interface_Check>&               ach,
                                        const occ::handle<StepBasic_ObjectRole>&    ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "object_role"))
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

  ent->Init(aName, hasDescription, aDescription);
}

void RWStepBasic_RWObjectRole::WriteStep(StepData_StepWriter&                     SW,
                                         const occ::handle<StepBasic_ObjectRole>& ent) const
{

  SW.Send(ent->Name());

  if (ent->HasDescription())
  {
    SW.Send(ent->Description());
  }
  else
    SW.SendUndef();
}

void RWStepBasic_RWObjectRole::Share(const occ::handle<StepBasic_ObjectRole>&,
                                     Interface_EntityIterator&) const
{
}
