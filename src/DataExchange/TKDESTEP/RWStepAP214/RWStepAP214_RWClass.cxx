#include <Interface_EntityIterator.hpp>
#include "RWStepAP214_RWClass.hpp"
#include <StepAP214_Class.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

//=================================================================================================

RWStepAP214_RWClass::RWStepAP214_RWClass() = default;

//=================================================================================================

void RWStepAP214_RWClass::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                   const int                                   num,
                                   occ::handle<Interface_Check>&               ach,
                                   const occ::handle<StepAP214_Class>&         ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 2, ach, "class"))
    return;

  // Inherited fields of Group

  occ::handle<TCollection_HAsciiString> aGroup_Name;
  data->ReadString(num, 1, "group.name", ach, aGroup_Name);

  occ::handle<TCollection_HAsciiString> aGroup_Description;
  bool                                  hasGroup_Description = true;
  if (data->IsParamDefined(num, 2))
  {
    data->ReadString(num, 2, "group.description", ach, aGroup_Description);
  }
  else
  {
    hasGroup_Description = false;
  }

  // Initialize entity
  ent->Init(aGroup_Name, hasGroup_Description, aGroup_Description);
}

//=================================================================================================

void RWStepAP214_RWClass::WriteStep(StepData_StepWriter&                SW,
                                    const occ::handle<StepAP214_Class>& ent) const
{

  // Inherited fields of Group

  SW.Send(ent->StepBasic_Group::Name());

  if (ent->StepBasic_Group::HasDescription())
  {
    SW.Send(ent->StepBasic_Group::Description());
  }
  else
    SW.SendUndef();
}

//=================================================================================================

void RWStepAP214_RWClass::Share(const occ::handle<StepAP214_Class>&,
                                Interface_EntityIterator&) const
{
  // Inherited fields of Group
}
