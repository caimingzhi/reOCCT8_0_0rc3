#include <StepShape_ValueFormatTypeQualifier.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_ValueFormatTypeQualifier, Standard_Transient)

//=================================================================================================

StepShape_ValueFormatTypeQualifier::StepShape_ValueFormatTypeQualifier() = default;

//=================================================================================================

void StepShape_ValueFormatTypeQualifier::Init(
  const occ::handle<TCollection_HAsciiString>& theFormatType)
{
  // --- classe own fields ---
  formatType = theFormatType;
}
