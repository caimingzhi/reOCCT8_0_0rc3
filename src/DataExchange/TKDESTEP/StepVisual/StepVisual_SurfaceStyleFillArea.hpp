#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepVisual_FillAreaStyle;

class StepVisual_SurfaceStyleFillArea : public Standard_Transient
{

public:
  //! Returns a SurfaceStyleFillArea
  Standard_EXPORT StepVisual_SurfaceStyleFillArea();

  Standard_EXPORT void Init(const occ::handle<StepVisual_FillAreaStyle>& aFillArea);

  Standard_EXPORT void SetFillArea(const occ::handle<StepVisual_FillAreaStyle>& aFillArea);

  Standard_EXPORT occ::handle<StepVisual_FillAreaStyle> FillArea() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_SurfaceStyleFillArea, Standard_Transient)

private:
  occ::handle<StepVisual_FillAreaStyle> fillArea;
};
