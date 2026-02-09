#pragma once

#include <StepVisual_SurfaceStyleReflectanceAmbient.hpp>

class StepVisual_SurfaceStyleReflectanceAmbientDiffuse
    : public StepVisual_SurfaceStyleReflectanceAmbient
{
public:
  Standard_EXPORT StepVisual_SurfaceStyleReflectanceAmbientDiffuse();

  Standard_EXPORT void Init(const double theAmbientReflectance, const double theDiffuseReflectance);

  Standard_EXPORT double DiffuseReflectance() const;

  Standard_EXPORT void SetDiffuseReflectance(const double theDiffuseReflectance);

  DEFINE_STANDARD_RTTIEXT(StepVisual_SurfaceStyleReflectanceAmbientDiffuse,
                          StepVisual_SurfaceStyleReflectanceAmbient)

private:
  double myDiffuseReflectance;
};
