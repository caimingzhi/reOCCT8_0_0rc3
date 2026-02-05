#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepVisual_CurveStyle;

class StepVisual_SurfaceStyleControlGrid : public Standard_Transient
{

public:
  //! Returns a SurfaceStyleControlGrid
  Standard_EXPORT StepVisual_SurfaceStyleControlGrid();

  Standard_EXPORT void Init(const occ::handle<StepVisual_CurveStyle>& aStyleOfControlGrid);

  Standard_EXPORT void SetStyleOfControlGrid(
    const occ::handle<StepVisual_CurveStyle>& aStyleOfControlGrid);

  Standard_EXPORT occ::handle<StepVisual_CurveStyle> StyleOfControlGrid() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_SurfaceStyleControlGrid, Standard_Transient)

private:
  occ::handle<StepVisual_CurveStyle> styleOfControlGrid;
};
