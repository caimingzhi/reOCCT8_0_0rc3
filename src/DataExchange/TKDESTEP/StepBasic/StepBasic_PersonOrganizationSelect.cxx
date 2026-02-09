

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepBasic_Organization.hpp>
#include <StepBasic_Person.hpp>
#include <StepBasic_PersonAndOrganization.hpp>
#include <StepBasic_PersonOrganizationSelect.hpp>

StepBasic_PersonOrganizationSelect::StepBasic_PersonOrganizationSelect() = default;

int StepBasic_PersonOrganizationSelect::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_Person)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_Organization)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_PersonAndOrganization)))
    return 3;
  return 0;
}

occ::handle<StepBasic_Person> StepBasic_PersonOrganizationSelect::Person() const
{
  return GetCasted(StepBasic_Person, Value());
}

occ::handle<StepBasic_Organization> StepBasic_PersonOrganizationSelect::Organization() const
{
  return GetCasted(StepBasic_Organization, Value());
}

occ::handle<StepBasic_PersonAndOrganization> StepBasic_PersonOrganizationSelect::
  PersonAndOrganization() const
{
  return GetCasted(StepBasic_PersonAndOrganization, Value());
}
