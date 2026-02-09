#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWExternalIdentificationAssignment.hpp"
#include <StepBasic_ExternalIdentificationAssignment.hpp>
#include <StepBasic_ExternalSource.hpp>
#include <StepBasic_IdentificationRole.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWExternalIdentificationAssignment::RWStepBasic_RWExternalIdentificationAssignment() =
  default;

void RWStepBasic_RWExternalIdentificationAssignment::ReadStep(
  const occ::handle<StepData_StepReaderData>&                    data,
  const int                                                      num,
  occ::handle<Interface_Check>&                                  ach,
  const occ::handle<StepBasic_ExternalIdentificationAssignment>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "external_identification_assignment"))
    return;

  occ::handle<TCollection_HAsciiString> aIdentificationAssignment_AssignedId;
  data->ReadString(num,
                   1,
                   "identification_assignment.assigned_id",
                   ach,
                   aIdentificationAssignment_AssignedId);

  occ::handle<StepBasic_IdentificationRole> aIdentificationAssignment_Role;
  data->ReadEntity(num,
                   2,
                   "identification_assignment.role",
                   ach,
                   STANDARD_TYPE(StepBasic_IdentificationRole),
                   aIdentificationAssignment_Role);

  occ::handle<StepBasic_ExternalSource> aSource;
  data->ReadEntity(num, 3, "source", ach, STANDARD_TYPE(StepBasic_ExternalSource), aSource);

  ent->Init(aIdentificationAssignment_AssignedId, aIdentificationAssignment_Role, aSource);
}

void RWStepBasic_RWExternalIdentificationAssignment::WriteStep(
  StepData_StepWriter&                                           SW,
  const occ::handle<StepBasic_ExternalIdentificationAssignment>& ent) const
{

  SW.Send(ent->StepBasic_IdentificationAssignment::AssignedId());

  SW.Send(ent->StepBasic_IdentificationAssignment::Role());

  SW.Send(ent->Source());
}

void RWStepBasic_RWExternalIdentificationAssignment::Share(
  const occ::handle<StepBasic_ExternalIdentificationAssignment>& ent,
  Interface_EntityIterator&                                      iter) const
{

  iter.AddItem(ent->StepBasic_IdentificationAssignment::Role());

  iter.AddItem(ent->Source());
}
