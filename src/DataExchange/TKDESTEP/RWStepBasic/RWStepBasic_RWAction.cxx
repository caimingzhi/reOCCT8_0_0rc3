#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWAction.hpp"
#include <StepBasic_Action.hpp>
#include <StepBasic_ActionMethod.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

//=================================================================================================

RWStepBasic_RWAction::RWStepBasic_RWAction() = default;

//=================================================================================================

void RWStepBasic_RWAction::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                    const int                                   num,
                                    occ::handle<Interface_Check>&               ach,
                                    const occ::handle<StepBasic_Action>&        ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 3, ach, "action"))
    return;

  // Own fields of Action

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

  occ::handle<StepBasic_ActionMethod> aChosenMethod;
  data->ReadEntity(num,
                   3,
                   "chosen_method",
                   ach,
                   STANDARD_TYPE(StepBasic_ActionMethod),
                   aChosenMethod);

  // Initialize entity
  ent->Init(aName, hasDescription, aDescription, aChosenMethod);
}

//=================================================================================================

void RWStepBasic_RWAction::WriteStep(StepData_StepWriter&                 SW,
                                     const occ::handle<StepBasic_Action>& ent) const
{

  // Own fields of Action

  SW.Send(ent->Name());

  if (ent->HasDescription())
  {
    SW.Send(ent->Description());
  }
  else
    SW.SendUndef();

  SW.Send(ent->ChosenMethod());
}

//=================================================================================================

void RWStepBasic_RWAction::Share(const occ::handle<StepBasic_Action>& ent,
                                 Interface_EntityIterator&            iter) const
{

  // Own fields of Action

  iter.AddItem(ent->ChosenMethod());
}
