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

  Standard_EXPORT StepBasic_PersonOrganizationSelect();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepBasic_Person> Person() const;

  Standard_EXPORT occ::handle<StepBasic_Organization> Organization() const;

  Standard_EXPORT occ::handle<StepBasic_PersonAndOrganization> PersonAndOrganization() const;
};
