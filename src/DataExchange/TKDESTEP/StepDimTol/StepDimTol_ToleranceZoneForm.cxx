#include <StepDimTol_ToleranceZoneForm.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepDimTol_ToleranceZoneForm, Standard_Transient)

//=================================================================================================

StepDimTol_ToleranceZoneForm::StepDimTol_ToleranceZoneForm() = default;

//=================================================================================================

void StepDimTol_ToleranceZoneForm::Init(const occ::handle<TCollection_HAsciiString>& theName)
{
  // --- classe own fields ---
  myName = theName;
}
