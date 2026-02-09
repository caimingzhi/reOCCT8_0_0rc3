#include <StepDimTol_ToleranceZoneTarget.hpp>
#include <MoniTool_Macros.hpp>
#include <StepShape_DimensionalLocation.hpp>
#include <StepShape_DimensionalSize.hpp>
#include <StepDimTol_GeneralDatumReference.hpp>
#include <StepDimTol_GeometricTolerance.hpp>

StepDimTol_ToleranceZoneTarget::StepDimTol_ToleranceZoneTarget() = default;

int StepDimTol_ToleranceZoneTarget::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepShape_DimensionalLocation)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepShape_DimensionalSize)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepDimTol_GeometricTolerance)))
    return 3;
  if (ent->IsKind(STANDARD_TYPE(StepDimTol_GeneralDatumReference)))
    return 4;
  return 0;
}

occ::handle<StepShape_DimensionalLocation> StepDimTol_ToleranceZoneTarget::DimensionalLocation()
  const
{
  return GetCasted(StepShape_DimensionalLocation, Value());
}

occ::handle<StepShape_DimensionalSize> StepDimTol_ToleranceZoneTarget::DimensionalSize() const
{
  return GetCasted(StepShape_DimensionalSize, Value());
}

occ::handle<StepDimTol_GeometricTolerance> StepDimTol_ToleranceZoneTarget::GeometricTolerance()
  const
{
  return GetCasted(StepDimTol_GeometricTolerance, Value());
}

occ::handle<StepDimTol_GeneralDatumReference> StepDimTol_ToleranceZoneTarget::
  GeneralDatumReference() const
{
  return GetCasted(StepDimTol_GeneralDatumReference, Value());
}
