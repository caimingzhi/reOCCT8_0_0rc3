#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWVersionedActionRequest.hpp"
#include <StepBasic_VersionedActionRequest.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

//=================================================================================================

RWStepBasic_RWVersionedActionRequest::RWStepBasic_RWVersionedActionRequest() = default;

//=================================================================================================

void RWStepBasic_RWVersionedActionRequest::ReadStep(
  const occ::handle<StepData_StepReaderData>&          data,
  const int                                            num,
  occ::handle<Interface_Check>&                        ach,
  const occ::handle<StepBasic_VersionedActionRequest>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 4, ach, "versioned_action_request"))
    return;

  // Own fields of VersionedActionRequest

  occ::handle<TCollection_HAsciiString> aId;
  data->ReadString(num, 1, "id", ach, aId);

  occ::handle<TCollection_HAsciiString> aVersion;
  data->ReadString(num, 2, "version", ach, aVersion);

  occ::handle<TCollection_HAsciiString> aPurpose;
  data->ReadString(num, 3, "purpose", ach, aPurpose);

  occ::handle<TCollection_HAsciiString> aDescription;
  bool                                  hasDescription = true;
  if (data->IsParamDefined(num, 4))
  {
    data->ReadString(num, 4, "description", ach, aDescription);
  }
  else
  {
    hasDescription = false;
  }

  // Initialize entity
  ent->Init(aId, aVersion, aPurpose, hasDescription, aDescription);
}

//=================================================================================================

void RWStepBasic_RWVersionedActionRequest::WriteStep(
  StepData_StepWriter&                                 SW,
  const occ::handle<StepBasic_VersionedActionRequest>& ent) const
{

  // Own fields of VersionedActionRequest

  SW.Send(ent->Id());

  SW.Send(ent->Version());

  SW.Send(ent->Purpose());

  if (ent->HasDescription())
  {
    SW.Send(ent->Description());
  }
  else
    SW.SendUndef();
}

//=================================================================================================

void RWStepBasic_RWVersionedActionRequest::Share(
  const occ::handle<StepBasic_VersionedActionRequest>&,
  Interface_EntityIterator&) const
{

  // Own fields of VersionedActionRequest
}
