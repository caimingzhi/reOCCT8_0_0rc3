#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;

class StepBasic_NameAssignment : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_NameAssignment();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aAssignedName);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> AssignedName() const;

  Standard_EXPORT void SetAssignedName(const occ::handle<TCollection_HAsciiString>& AssignedName);

  DEFINE_STANDARD_RTTIEXT(StepBasic_NameAssignment, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> theAssignedName;
};
