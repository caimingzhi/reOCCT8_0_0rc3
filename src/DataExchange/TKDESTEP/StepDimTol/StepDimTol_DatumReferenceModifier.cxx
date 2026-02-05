#include <StepDimTol_DatumReferenceModifier.hpp>
#include <MoniTool_Macros.hpp>
#include <StepDimTol_DatumReferenceModifierWithValue.hpp>
#include <StepDimTol_SimpleDatumReferenceModifierMember.hpp>

//=================================================================================================

StepDimTol_DatumReferenceModifier::StepDimTol_DatumReferenceModifier() = default;

//=================================================================================================

int StepDimTol_DatumReferenceModifier::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepDimTol_DatumReferenceModifierWithValue)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepDimTol_SimpleDatumReferenceModifierMember)))
    return 2;
  return 0;
}

occ::handle<StepDimTol_DatumReferenceModifierWithValue> StepDimTol_DatumReferenceModifier::
  DatumReferenceModifierWithValue() const
{
  return GetCasted(StepDimTol_DatumReferenceModifierWithValue, Value());
}

occ::handle<StepDimTol_SimpleDatumReferenceModifierMember> StepDimTol_DatumReferenceModifier::
  SimpleDatumReferenceModifierMember() const
{
  return GetCasted(StepDimTol_SimpleDatumReferenceModifierMember, Value());
}
