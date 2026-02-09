#pragma once

#include <StepVisual_SurfaceStyleReflectanceAmbientDiffuse.hpp>
#include <StepVisual_Colour.hpp>

class StepVisual_SurfaceStyleReflectanceAmbientDiffuseSpecular
    : public StepVisual_SurfaceStyleReflectanceAmbientDiffuse
{
public:
  Standard_EXPORT StepVisual_SurfaceStyleReflectanceAmbientDiffuseSpecular();

  Standard_EXPORT void Init(const double                          theAmbientReflectance,
                            const double                          theDiffuseReflectance,
                            const double                          theSpecularReflectance,
                            const double                          theSpecularExponent,
                            const occ::handle<StepVisual_Colour>& theSpecularColour);

  Standard_EXPORT double SpecularReflectance() const;

  Standard_EXPORT void SetSpecularReflectance(const double theSpecularReflectance);

  Standard_EXPORT double SpecularExponent() const;

  Standard_EXPORT void SetSpecularExponent(const double theSpecularExponent);

  Standard_EXPORT occ::handle<StepVisual_Colour> SpecularColour() const;

  Standard_EXPORT void SetSpecularColour(const occ::handle<StepVisual_Colour>& theSpecularColour);

  DEFINE_STANDARD_RTTIEXT(StepVisual_SurfaceStyleReflectanceAmbientDiffuseSpecular,
                          StepVisual_SurfaceStyleReflectanceAmbientDiffuse)

private:
  double                         mySpecularReflectance;
  double                         mySpecularExponent;
  occ::handle<StepVisual_Colour> mySpecularColour;
};
