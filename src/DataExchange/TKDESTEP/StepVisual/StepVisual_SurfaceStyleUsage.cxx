

#include <StepVisual_SurfaceSideStyle.hpp>
#include <StepVisual_SurfaceStyleUsage.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_SurfaceStyleUsage, Standard_Transient)

StepVisual_SurfaceStyleUsage::StepVisual_SurfaceStyleUsage() = default;

void StepVisual_SurfaceStyleUsage::Init(const StepVisual_SurfaceSide                    aSide,
                                        const occ::handle<StepVisual_SurfaceSideStyle>& aStyle)
{

  side  = aSide;
  style = aStyle;
}

void StepVisual_SurfaceStyleUsage::SetSide(const StepVisual_SurfaceSide aSide)
{
  side = aSide;
}

StepVisual_SurfaceSide StepVisual_SurfaceStyleUsage::Side() const
{
  return side;
}

void StepVisual_SurfaceStyleUsage::SetStyle(const occ::handle<StepVisual_SurfaceSideStyle>& aStyle)
{
  style = aStyle;
}

occ::handle<StepVisual_SurfaceSideStyle> StepVisual_SurfaceStyleUsage::Style() const
{
  return style;
}
