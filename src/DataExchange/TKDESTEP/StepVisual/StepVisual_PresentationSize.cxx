

#include <StepVisual_PlanarBox.hpp>
#include <StepVisual_PresentationSize.hpp>
#include <StepVisual_PresentationSizeAssignmentSelect.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_PresentationSize, Standard_Transient)

StepVisual_PresentationSize::StepVisual_PresentationSize() = default;

void StepVisual_PresentationSize::Init(const StepVisual_PresentationSizeAssignmentSelect& aUnit,
                                       const occ::handle<StepVisual_PlanarBox>&           aSize)
{

  unit = aUnit;
  size = aSize;
}

void StepVisual_PresentationSize::SetUnit(const StepVisual_PresentationSizeAssignmentSelect& aUnit)
{
  unit = aUnit;
}

StepVisual_PresentationSizeAssignmentSelect StepVisual_PresentationSize::Unit() const
{
  return unit;
}

void StepVisual_PresentationSize::SetSize(const occ::handle<StepVisual_PlanarBox>& aSize)
{
  size = aSize;
}

occ::handle<StepVisual_PlanarBox> StepVisual_PresentationSize::Size() const
{
  return size;
}
