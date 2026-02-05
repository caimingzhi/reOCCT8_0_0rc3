#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;

class StepBasic_ApprovalRole : public Standard_Transient
{

public:
  //! Returns a ApprovalRole
  Standard_EXPORT StepBasic_ApprovalRole();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aRole);

  Standard_EXPORT void SetRole(const occ::handle<TCollection_HAsciiString>& aRole);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Role() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_ApprovalRole, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> role;
};
