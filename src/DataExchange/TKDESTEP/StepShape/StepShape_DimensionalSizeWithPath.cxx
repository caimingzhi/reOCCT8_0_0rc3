#include <StepRepr_ShapeAspect.hpp>
#include <StepShape_DimensionalSizeWithPath.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_DimensionalSizeWithPath, StepShape_DimensionalSize)

//=================================================================================================

StepShape_DimensionalSizeWithPath::StepShape_DimensionalSizeWithPath() = default;

//=================================================================================================

void StepShape_DimensionalSizeWithPath::Init(
  const occ::handle<StepRepr_ShapeAspect>&     aDimensionalSize_AppliesTo,
  const occ::handle<TCollection_HAsciiString>& aDimensionalSize_Name,
  const occ::handle<StepRepr_ShapeAspect>&     aPath)
{
  StepShape_DimensionalSize::Init(aDimensionalSize_AppliesTo, aDimensionalSize_Name);

  thePath = aPath;
}

//=================================================================================================

occ::handle<StepRepr_ShapeAspect> StepShape_DimensionalSizeWithPath::Path() const
{
  return thePath;
}

//=================================================================================================

void StepShape_DimensionalSizeWithPath::SetPath(const occ::handle<StepRepr_ShapeAspect>& aPath)
{
  thePath = aPath;
}
