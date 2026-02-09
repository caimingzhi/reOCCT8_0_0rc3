

#include <StepBasic_Organization.hpp>
#include <StepBasic_Person.hpp>
#include <StepBasic_PersonAndOrganization.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_PersonAndOrganization, Standard_Transient)

StepBasic_PersonAndOrganization::StepBasic_PersonAndOrganization() = default;

void StepBasic_PersonAndOrganization::Init(
  const occ::handle<StepBasic_Person>&       aThePerson,
  const occ::handle<StepBasic_Organization>& aTheOrganization)
{

  thePerson       = aThePerson;
  theOrganization = aTheOrganization;
}

void StepBasic_PersonAndOrganization::SetThePerson(const occ::handle<StepBasic_Person>& aThePerson)
{
  thePerson = aThePerson;
}

occ::handle<StepBasic_Person> StepBasic_PersonAndOrganization::ThePerson() const
{
  return thePerson;
}

void StepBasic_PersonAndOrganization::SetTheOrganization(
  const occ::handle<StepBasic_Organization>& aTheOrganization)
{
  theOrganization = aTheOrganization;
}

occ::handle<StepBasic_Organization> StepBasic_PersonAndOrganization::TheOrganization() const
{
  return theOrganization;
}
