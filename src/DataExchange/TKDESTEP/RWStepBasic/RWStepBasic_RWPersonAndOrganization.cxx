

#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWPersonAndOrganization.hpp"
#include <StepBasic_Organization.hpp>
#include <StepBasic_Person.hpp>
#include <StepBasic_PersonAndOrganization.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWPersonAndOrganization::RWStepBasic_RWPersonAndOrganization() = default;

void RWStepBasic_RWPersonAndOrganization::ReadStep(
  const occ::handle<StepData_StepReaderData>&         data,
  const int                                           num,
  occ::handle<Interface_Check>&                       ach,
  const occ::handle<StepBasic_PersonAndOrganization>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "person_and_organization"))
    return;

  occ::handle<StepBasic_Person> aThePerson;

  data->ReadEntity(num, 1, "the_person", ach, STANDARD_TYPE(StepBasic_Person), aThePerson);

  occ::handle<StepBasic_Organization> aTheOrganization;

  data->ReadEntity(num,
                   2,
                   "the_organization",
                   ach,
                   STANDARD_TYPE(StepBasic_Organization),
                   aTheOrganization);

  ent->Init(aThePerson, aTheOrganization);
}

void RWStepBasic_RWPersonAndOrganization::WriteStep(
  StepData_StepWriter&                                SW,
  const occ::handle<StepBasic_PersonAndOrganization>& ent) const
{

  SW.Send(ent->ThePerson());

  SW.Send(ent->TheOrganization());
}

void RWStepBasic_RWPersonAndOrganization::Share(
  const occ::handle<StepBasic_PersonAndOrganization>& ent,
  Interface_EntityIterator&                           iter) const
{

  iter.GetOneItem(ent->ThePerson());

  iter.GetOneItem(ent->TheOrganization());
}
