#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <Standard_Transient.hpp>

class StepVisual_SurfaceStyleTransparent : public Standard_Transient
{
public:
  Standard_EXPORT StepVisual_SurfaceStyleTransparent();

  Standard_EXPORT void Init(const double theTransparency);

  Standard_EXPORT double Transparency() const;

  Standard_EXPORT void SetTransparency(const double theTransparency);

  DEFINE_STANDARD_RTTIEXT(StepVisual_SurfaceStyleTransparent, Standard_Transient)

private:
  double myTransparency;
};
