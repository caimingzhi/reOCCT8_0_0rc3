

#include <Standard_Type.hpp>
#include <StepBasic_DateAndTime.hpp>
#include <StepBasic_DateAndTimeAssignment.hpp>
#include <StepBasic_DateTimeRole.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_DateAndTimeAssignment, Standard_Transient)

void StepBasic_DateAndTimeAssignment::Init(
  const occ::handle<StepBasic_DateAndTime>&  aAssignedDateAndTime,
  const occ::handle<StepBasic_DateTimeRole>& aRole)
{

  assignedDateAndTime = aAssignedDateAndTime;
  role                = aRole;
}

void StepBasic_DateAndTimeAssignment::SetAssignedDateAndTime(
  const occ::handle<StepBasic_DateAndTime>& aAssignedDateAndTime)
{
  assignedDateAndTime = aAssignedDateAndTime;
}

occ::handle<StepBasic_DateAndTime> StepBasic_DateAndTimeAssignment::AssignedDateAndTime() const
{
  return assignedDateAndTime;
}

void StepBasic_DateAndTimeAssignment::SetRole(const occ::handle<StepBasic_DateTimeRole>& aRole)
{
  role = aRole;
}

occ::handle<StepBasic_DateTimeRole> StepBasic_DateAndTimeAssignment::Role() const
{
  return role;
}
