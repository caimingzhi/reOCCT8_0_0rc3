#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepBasic_Person;
class StepBasic_Organization;
class StepBasic_PersonAndOrganization;

class StepBasic_PersonOrganizationSelect : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a PersonOrganizationSelect SelectType
  Standard_EXPORT StepBasic_PersonOrganizationSelect();

  //! Recognizes a PersonOrganizationSelect Kind Entity that is :
  //! 1 -> Person
  //! 2 -> Organization
  //! 3 -> PersonAndOrganization
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a Person (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_Person> Person() const;

  //! returns Value as a Organization (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_Organization> Organization() const;

  //! returns Value as a PersonAndOrganization (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_PersonAndOrganization> PersonAndOrganization() const;
};
