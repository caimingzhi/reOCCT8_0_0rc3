

#include <StepVisual_PlanarBox.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_PlanarBox, StepVisual_PlanarExtent)

StepVisual_PlanarBox::StepVisual_PlanarBox() = default;

void StepVisual_PlanarBox::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                const double                                 aSizeInX,
                                const double                                 aSizeInY,
                                const StepGeom_Axis2Placement&               aPlacement)
{

  placement = aPlacement;

  StepVisual_PlanarExtent::Init(aName, aSizeInX, aSizeInY);
}

void StepVisual_PlanarBox::SetPlacement(const StepGeom_Axis2Placement& aPlacement)
{
  placement = aPlacement;
}

StepGeom_Axis2Placement StepVisual_PlanarBox::Placement() const
{
  return placement;
}
