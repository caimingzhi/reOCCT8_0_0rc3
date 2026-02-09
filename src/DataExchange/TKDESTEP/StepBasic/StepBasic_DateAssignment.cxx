

#include <Standard_Type.hpp>
#include <StepBasic_Date.hpp>
#include <StepBasic_DateAssignment.hpp>
#include <StepBasic_DateRole.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_DateAssignment, Standard_Transient)

void StepBasic_DateAssignment::Init(const occ::handle<StepBasic_Date>&     aAssignedDate,
                                    const occ::handle<StepBasic_DateRole>& aRole)
{

  assignedDate = aAssignedDate;
  role         = aRole;
}

void StepBasic_DateAssignment::SetAssignedDate(const occ::handle<StepBasic_Date>& aAssignedDate)
{
  assignedDate = aAssignedDate;
}

occ::handle<StepBasic_Date> StepBasic_DateAssignment::AssignedDate() const
{
  return assignedDate;
}

void StepBasic_DateAssignment::SetRole(const occ::handle<StepBasic_DateRole>& aRole)
{
  role = aRole;
}

occ::handle<StepBasic_DateRole> StepBasic_DateAssignment::Role() const
{
  return role;
}
