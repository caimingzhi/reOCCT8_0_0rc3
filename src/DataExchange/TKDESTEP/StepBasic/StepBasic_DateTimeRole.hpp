#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;

class StepBasic_DateTimeRole : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_DateTimeRole();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName);

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& aName);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_DateTimeRole, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> name;
};
