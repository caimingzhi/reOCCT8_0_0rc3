#include <StepDimTol_DatumSystemOrReference.hpp>
#include <MoniTool_Macros.hpp>
#include <StepDimTol_DatumSystem.hpp>
#include <StepDimTol_DatumReference.hpp>

StepDimTol_DatumSystemOrReference::StepDimTol_DatumSystemOrReference() = default;

int StepDimTol_DatumSystemOrReference::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepDimTol_DatumSystem)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepDimTol_DatumReference)))
    return 2;
  return 0;
}

occ::handle<StepDimTol_DatumSystem> StepDimTol_DatumSystemOrReference::DatumSystem() const
{
  return GetCasted(StepDimTol_DatumSystem, Value());
}

occ::handle<StepDimTol_DatumReference> StepDimTol_DatumSystemOrReference::DatumReference() const
{
  return GetCasted(StepDimTol_DatumReference, Value());
}
