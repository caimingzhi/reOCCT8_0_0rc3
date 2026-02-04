#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;

class StepBasic_PersonAndOrganizationRole : public Standard_Transient
{

public:
  //! Returns a PersonAndOrganizationRole
  Standard_EXPORT StepBasic_PersonAndOrganizationRole();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName);

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& aName);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_PersonAndOrganizationRole, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> name;
};

