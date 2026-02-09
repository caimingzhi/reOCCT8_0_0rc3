#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepVisual_SurfaceSide.hpp>
#include <Standard_Transient.hpp>
class StepVisual_SurfaceSideStyle;

class StepVisual_SurfaceStyleUsage : public Standard_Transient
{

public:
  Standard_EXPORT StepVisual_SurfaceStyleUsage();

  Standard_EXPORT void Init(const StepVisual_SurfaceSide                    aSide,
                            const occ::handle<StepVisual_SurfaceSideStyle>& aStyle);

  Standard_EXPORT void SetSide(const StepVisual_SurfaceSide aSide);

  Standard_EXPORT StepVisual_SurfaceSide Side() const;

  Standard_EXPORT void SetStyle(const occ::handle<StepVisual_SurfaceSideStyle>& aStyle);

  Standard_EXPORT occ::handle<StepVisual_SurfaceSideStyle> Style() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_SurfaceStyleUsage, Standard_Transient)

private:
  StepVisual_SurfaceSide                   side;
  occ::handle<StepVisual_SurfaceSideStyle> style;
};
