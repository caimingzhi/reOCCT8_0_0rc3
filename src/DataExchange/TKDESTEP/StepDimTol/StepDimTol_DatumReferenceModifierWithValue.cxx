#include <StepDimTol_DatumReferenceModifierWithValue.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepDimTol_DatumReferenceModifierWithValue, Standard_Transient)

//=================================================================================================

StepDimTol_DatumReferenceModifierWithValue::StepDimTol_DatumReferenceModifierWithValue() = default;

//=================================================================================================

void StepDimTol_DatumReferenceModifierWithValue::Init(
  const StepDimTol_DatumReferenceModifierType&        theModifierType,
  const occ::handle<StepBasic_LengthMeasureWithUnit>& theModifierValue)
{
  myModifierType  = theModifierType;
  myModifierValue = theModifierValue;
}
