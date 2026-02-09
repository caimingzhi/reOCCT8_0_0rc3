#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <Standard_Transient.hpp>

class StepVisual_SurfaceStyleReflectanceAmbient : public Standard_Transient
{
public:
  Standard_EXPORT StepVisual_SurfaceStyleReflectanceAmbient();

  Standard_EXPORT void Init(const double theAmbientReflectance);

  Standard_EXPORT double AmbientReflectance() const;

  Standard_EXPORT void SetAmbientReflectance(const double theAmbientReflectance);

  DEFINE_STANDARD_RTTIEXT(StepVisual_SurfaceStyleReflectanceAmbient, Standard_Transient)

private:
  double myAmbientReflectance;
};
