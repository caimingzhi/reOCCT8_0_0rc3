

#include "RWStepBasic_RWOrganization.hpp"
#include <StepBasic_Organization.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWOrganization::RWStepBasic_RWOrganization() = default;

void RWStepBasic_RWOrganization::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                          const int                                   num,
                                          occ::handle<Interface_Check>&               ach,
                                          const occ::handle<StepBasic_Organization>&  ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "organization"))
    return;

  occ::handle<TCollection_HAsciiString> aId;
  bool                                  hasAid = true;
  if (data->IsParamDefined(num, 1))
  {

    data->ReadString(num, 1, "id", ach, aId);
  }
  else
  {
    hasAid = false;
    aId.Nullify();
  }

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 2, "name", ach, aName);

  occ::handle<TCollection_HAsciiString> aDescription;
  if (data->IsParamDefined(num, 3))
  {

    data->ReadString(num, 3, "description", ach, aDescription);
  }

  ent->Init(hasAid, aId, aName, aDescription);
}

void RWStepBasic_RWOrganization::WriteStep(StepData_StepWriter&                       SW,
                                           const occ::handle<StepBasic_Organization>& ent) const
{

  bool hasAid = ent->HasId();
  if (hasAid)
  {
    SW.Send(ent->Id());
  }
  else
  {
    SW.SendUndef();
  }

  SW.Send(ent->Name());

  SW.Send(ent->Description());
}
