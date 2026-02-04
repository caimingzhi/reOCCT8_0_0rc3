#pragma once


#include <Standard_Transient.hpp>
#include <Standard.hpp>
#include <TCollection_HAsciiString.hpp>

class TCollection_HAsciiString;

//! Added for Dimensional Tolerances
class StepDimTol_ToleranceZoneForm : public Standard_Transient
{

public:
  Standard_EXPORT StepDimTol_ToleranceZoneForm();

  //! Init all field own and inherited
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& theName);

  //! Returns field Name
  inline occ::handle<TCollection_HAsciiString> Name() { return myName; }

  //! Set field Name
  inline void SetName(const occ::handle<TCollection_HAsciiString>& theName) { myName = theName; }

  DEFINE_STANDARD_RTTIEXT(StepDimTol_ToleranceZoneForm, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> myName;
};
