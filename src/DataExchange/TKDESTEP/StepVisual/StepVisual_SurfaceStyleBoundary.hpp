#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepVisual_CurveStyle;

class StepVisual_SurfaceStyleBoundary : public Standard_Transient
{

public:
  //! Returns a SurfaceStyleBoundary
  Standard_EXPORT StepVisual_SurfaceStyleBoundary();

  Standard_EXPORT void Init(const occ::handle<StepVisual_CurveStyle>& aStyleOfBoundary);

  Standard_EXPORT void SetStyleOfBoundary(
    const occ::handle<StepVisual_CurveStyle>& aStyleOfBoundary);

  Standard_EXPORT occ::handle<StepVisual_CurveStyle> StyleOfBoundary() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_SurfaceStyleBoundary, Standard_Transient)

private:
  occ::handle<StepVisual_CurveStyle> styleOfBoundary;
};

