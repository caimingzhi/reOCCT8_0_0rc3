#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepBasic_Date;
class StepBasic_DateRole;

class StepBasic_DateAssignment : public Standard_Transient
{

public:
  Standard_EXPORT void Init(const occ::handle<StepBasic_Date>&     aAssignedDate,
                            const occ::handle<StepBasic_DateRole>& aRole);

  Standard_EXPORT void SetAssignedDate(const occ::handle<StepBasic_Date>& aAssignedDate);

  Standard_EXPORT occ::handle<StepBasic_Date> AssignedDate() const;

  Standard_EXPORT void SetRole(const occ::handle<StepBasic_DateRole>& aRole);

  Standard_EXPORT occ::handle<StepBasic_DateRole> Role() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_DateAssignment, Standard_Transient)

private:
  occ::handle<StepBasic_Date>     assignedDate;
  occ::handle<StepBasic_DateRole> role;
};

