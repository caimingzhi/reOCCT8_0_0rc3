#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWGroup.hpp"
#include <StepBasic_Group.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

//=================================================================================================

RWStepBasic_RWGroup::RWStepBasic_RWGroup() = default;

//=================================================================================================

void RWStepBasic_RWGroup::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                   const int                                   num,
                                   occ::handle<Interface_Check>&               ach,
                                   const occ::handle<StepBasic_Group>&         ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 2, ach, "group"))
    return;

  // Own fields of Group

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

  // Initialize entity
  ent->Init(aName, hasDescription, aDescription);
}

//=================================================================================================

void RWStepBasic_RWGroup::WriteStep(StepData_StepWriter&                SW,
                                    const occ::handle<StepBasic_Group>& ent) const
{

  // Own fields of Group

  SW.Send(ent->Name());

  if (ent->HasDescription())
  {
    SW.Send(ent->Description());
  }
  else
    SW.SendUndef();
}

//=================================================================================================

void RWStepBasic_RWGroup::Share(const occ::handle<StepBasic_Group>&,
                                Interface_EntityIterator&) const
{
  // Own fields of Group
}
