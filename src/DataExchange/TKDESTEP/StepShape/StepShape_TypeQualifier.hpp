#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;

class StepShape_TypeQualifier : public Standard_Transient
{

public:
  Standard_EXPORT StepShape_TypeQualifier();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& name);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& name);

  DEFINE_STANDARD_RTTIEXT(StepShape_TypeQualifier, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> theName;
};
