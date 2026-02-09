#pragma once

#include <Standard_Transient.hpp>
#include <Standard.hpp>
#include <TCollection_HAsciiString.hpp>

class TCollection_HAsciiString;

class StepDimTol_ToleranceZoneForm : public Standard_Transient
{

public:
  Standard_EXPORT StepDimTol_ToleranceZoneForm();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& theName);

  inline occ::handle<TCollection_HAsciiString> Name() { return myName; }

  inline void SetName(const occ::handle<TCollection_HAsciiString>& theName) { myName = theName; }

  DEFINE_STANDARD_RTTIEXT(StepDimTol_ToleranceZoneForm, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> myName;
};
