#include <StepRepr_ShapeAspect.hpp>
#include <StepShape_AngularSize.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_AngularSize, StepShape_DimensionalSize)

StepShape_AngularSize::StepShape_AngularSize() = default;

void StepShape_AngularSize::Init(
  const occ::handle<StepRepr_ShapeAspect>&     aDimensionalSize_AppliesTo,
  const occ::handle<TCollection_HAsciiString>& aDimensionalSize_Name,
  const StepShape_AngleRelator                 aAngleSelection)
{
  StepShape_DimensionalSize::Init(aDimensionalSize_AppliesTo, aDimensionalSize_Name);

  theAngleSelection = aAngleSelection;
}

StepShape_AngleRelator StepShape_AngularSize::AngleSelection() const
{
  return theAngleSelection;
}

void StepShape_AngularSize::SetAngleSelection(const StepShape_AngleRelator aAngleSelection)
{
  theAngleSelection = aAngleSelection;
}
