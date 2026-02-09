

#include <Standard_Transient.hpp>
#include <StepShape_PrecisionQualifier.hpp>
#include <StepShape_TypeQualifier.hpp>
#include <StepShape_ValueFormatTypeQualifier.hpp>
#include <StepShape_ValueQualifier.hpp>

StepShape_ValueQualifier::StepShape_ValueQualifier() = default;

int StepShape_ValueQualifier::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepShape_PrecisionQualifier)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepShape_TypeQualifier)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepShape_ValueFormatTypeQualifier)))
    return 4;
  return 0;
}

occ::handle<StepShape_PrecisionQualifier> StepShape_ValueQualifier::PrecisionQualifier() const
{
  return occ::down_cast<StepShape_PrecisionQualifier>(Value());
}

occ::handle<StepShape_TypeQualifier> StepShape_ValueQualifier::TypeQualifier() const
{
  return occ::down_cast<StepShape_TypeQualifier>(Value());
}

occ::handle<StepShape_ValueFormatTypeQualifier> StepShape_ValueQualifier::ValueFormatTypeQualifier()
  const
{
  return occ::down_cast<StepShape_ValueFormatTypeQualifier>(Value());
}
