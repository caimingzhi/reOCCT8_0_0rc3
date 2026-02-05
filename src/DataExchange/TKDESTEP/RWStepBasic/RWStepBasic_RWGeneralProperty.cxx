#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWGeneralProperty.hpp"
#include <StepBasic_GeneralProperty.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

//=================================================================================================

RWStepBasic_RWGeneralProperty::RWStepBasic_RWGeneralProperty() = default;

//=================================================================================================

void RWStepBasic_RWGeneralProperty::ReadStep(
  const occ::handle<StepData_StepReaderData>&   data,
  const int                                     num,
  occ::handle<Interface_Check>&                 ach,
  const occ::handle<StepBasic_GeneralProperty>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 3, ach, "general_property"))
    return;

  // Own fields of GeneralProperty

  occ::handle<TCollection_HAsciiString> aId;
  data->ReadString(num, 1, "id", ach, aId);

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 2, "name", ach, aName);

  occ::handle<TCollection_HAsciiString> aDescription;
  bool                                  hasDescription = true;
  if (data->IsParamDefined(num, 3))
  {
    data->ReadString(num, 3, "description", ach, aDescription);
  }
  else
  {
    hasDescription = false;
  }

  // Initialize entity
  ent->Init(aId, aName, hasDescription, aDescription);
}

//=================================================================================================

void RWStepBasic_RWGeneralProperty::WriteStep(
  StepData_StepWriter&                          SW,
  const occ::handle<StepBasic_GeneralProperty>& ent) const
{

  // Own fields of GeneralProperty

  SW.Send(ent->Id());

  SW.Send(ent->Name());

  if (ent->HasDescription())
  {
    SW.Send(ent->Description());
  }
  else
    SW.SendUndef();
}

//=================================================================================================

void RWStepBasic_RWGeneralProperty::Share(const occ::handle<StepBasic_GeneralProperty>&,
                                          Interface_EntityIterator&) const
{
  // Own fields of GeneralProperty
}
