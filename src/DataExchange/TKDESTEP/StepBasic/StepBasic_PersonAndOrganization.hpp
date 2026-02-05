#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepBasic_Person;
class StepBasic_Organization;

class StepBasic_PersonAndOrganization : public Standard_Transient
{

public:
  //! Returns a PersonAndOrganization
  Standard_EXPORT StepBasic_PersonAndOrganization();

  Standard_EXPORT void Init(const occ::handle<StepBasic_Person>&       aThePerson,
                            const occ::handle<StepBasic_Organization>& aTheOrganization);

  Standard_EXPORT void SetThePerson(const occ::handle<StepBasic_Person>& aThePerson);

  Standard_EXPORT occ::handle<StepBasic_Person> ThePerson() const;

  Standard_EXPORT void SetTheOrganization(
    const occ::handle<StepBasic_Organization>& aTheOrganization);

  Standard_EXPORT occ::handle<StepBasic_Organization> TheOrganization() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_PersonAndOrganization, Standard_Transient)

private:
  occ::handle<StepBasic_Person>       thePerson;
  occ::handle<StepBasic_Organization> theOrganization;
};
