#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepBasic_ApprovalStatus;
class TCollection_HAsciiString;

#ifdef Status
  #undef Status
#endif

class StepBasic_Approval : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_Approval();

  Standard_EXPORT void Init(const occ::handle<StepBasic_ApprovalStatus>& aStatus,
                            const occ::handle<TCollection_HAsciiString>& aLevel);

  Standard_EXPORT void SetStatus(const occ::handle<StepBasic_ApprovalStatus>& aStatus);

  Standard_EXPORT occ::handle<StepBasic_ApprovalStatus> Status() const;

  Standard_EXPORT void SetLevel(const occ::handle<TCollection_HAsciiString>& aLevel);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Level() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_Approval, Standard_Transient)

private:
  occ::handle<StepBasic_ApprovalStatus> status;
  occ::handle<TCollection_HAsciiString> level;
};
