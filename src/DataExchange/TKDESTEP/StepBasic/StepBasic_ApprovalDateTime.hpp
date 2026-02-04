#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_DateTimeSelect.hpp>
#include <Standard_Transient.hpp>
class StepBasic_Approval;

//! Added from StepBasic Rev2 to Rev4
class StepBasic_ApprovalDateTime : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_ApprovalDateTime();

  Standard_EXPORT void Init(const StepBasic_DateTimeSelect&        aDateTime,
                            const occ::handle<StepBasic_Approval>& aDatedApproval);

  Standard_EXPORT void SetDateTime(const StepBasic_DateTimeSelect& aDateTime);

  Standard_EXPORT StepBasic_DateTimeSelect DateTime() const;

  Standard_EXPORT void SetDatedApproval(const occ::handle<StepBasic_Approval>& aDatedApproval);

  Standard_EXPORT occ::handle<StepBasic_Approval> DatedApproval() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_ApprovalDateTime, Standard_Transient)

private:
  StepBasic_DateTimeSelect        theDateTime;
  occ::handle<StepBasic_Approval> theDatedApproval;
};

