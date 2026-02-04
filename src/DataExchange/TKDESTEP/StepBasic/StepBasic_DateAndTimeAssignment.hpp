#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepBasic_DateAndTime;
class StepBasic_DateTimeRole;

class StepBasic_DateAndTimeAssignment : public Standard_Transient
{

public:
  Standard_EXPORT void Init(const occ::handle<StepBasic_DateAndTime>&  aAssignedDateAndTime,
                            const occ::handle<StepBasic_DateTimeRole>& aRole);

  Standard_EXPORT void SetAssignedDateAndTime(
    const occ::handle<StepBasic_DateAndTime>& aAssignedDateAndTime);

  Standard_EXPORT occ::handle<StepBasic_DateAndTime> AssignedDateAndTime() const;

  Standard_EXPORT void SetRole(const occ::handle<StepBasic_DateTimeRole>& aRole);

  Standard_EXPORT occ::handle<StepBasic_DateTimeRole> Role() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_DateAndTimeAssignment, Standard_Transient)

private:
  occ::handle<StepBasic_DateAndTime>  assignedDateAndTime;
  occ::handle<StepBasic_DateTimeRole> role;
};

