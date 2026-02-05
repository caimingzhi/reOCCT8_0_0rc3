#pragma once

#include <Standard_Transient.hpp>
#include <Standard.hpp>
#include <TCollection_HAsciiString.hpp>

class TCollection_HAsciiString;

//! Added for Dimensional Tolerances
class StepShape_ValueFormatTypeQualifier : public Standard_Transient
{

public:
  Standard_EXPORT StepShape_ValueFormatTypeQualifier();

  //! Init all field own and inherited
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& theFormatType);

  //! Returns field FormatType
  inline occ::handle<TCollection_HAsciiString> FormatType() { return formatType; }

  //! Set field FormatType
  inline void SetFormatType(const occ::handle<TCollection_HAsciiString>& theFormatType)
  {
    formatType = theFormatType;
  }

  DEFINE_STANDARD_RTTIEXT(StepShape_ValueFormatTypeQualifier, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> formatType;
};
