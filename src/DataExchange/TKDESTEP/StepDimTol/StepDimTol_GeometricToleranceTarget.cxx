#include <StepDimTol_GeometricToleranceTarget.hpp>
#include <MoniTool_Macros.hpp>
#include <StepShape_DimensionalLocation.hpp>
#include <StepShape_DimensionalSize.hpp>
#include <StepRepr_ProductDefinitionShape.hpp>
#include <StepRepr_ShapeAspect.hpp>

StepDimTol_GeometricToleranceTarget::StepDimTol_GeometricToleranceTarget() = default;

int StepDimTol_GeometricToleranceTarget::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepShape_DimensionalLocation)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepShape_DimensionalSize)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_ProductDefinitionShape)))
    return 3;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_ShapeAspect)))
    return 4;
  return 0;
}

occ::handle<StepShape_DimensionalLocation> StepDimTol_GeometricToleranceTarget::
  DimensionalLocation() const
{
  return GetCasted(StepShape_DimensionalLocation, Value());
}

occ::handle<StepShape_DimensionalSize> StepDimTol_GeometricToleranceTarget::DimensionalSize() const
{
  return GetCasted(StepShape_DimensionalSize, Value());
}

occ::handle<StepRepr_ProductDefinitionShape> StepDimTol_GeometricToleranceTarget::
  ProductDefinitionShape() const
{
  return GetCasted(StepRepr_ProductDefinitionShape, Value());
}

occ::handle<StepRepr_ShapeAspect> StepDimTol_GeometricToleranceTarget::ShapeAspect() const
{
  return GetCasted(StepRepr_ShapeAspect, Value());
}
