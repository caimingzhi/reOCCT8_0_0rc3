#pragma once

#include <StepVisual_SurfaceStyleReflectanceAmbientDiffuse.hpp>
#include <StepVisual_Colour.hpp>

//! Representation of STEP entity SurfaceStyleReflectanceAmbientDiffuseSpecular
class StepVisual_SurfaceStyleReflectanceAmbientDiffuseSpecular
    : public StepVisual_SurfaceStyleReflectanceAmbientDiffuse
{
public:
  //! default constructor
  Standard_EXPORT StepVisual_SurfaceStyleReflectanceAmbientDiffuseSpecular();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const double                          theAmbientReflectance,
                            const double                          theDiffuseReflectance,
                            const double                          theSpecularReflectance,
                            const double                          theSpecularExponent,
                            const occ::handle<StepVisual_Colour>& theSpecularColour);

  //! Returns field SpecularReflectance
  Standard_EXPORT double SpecularReflectance() const;

  //! Sets field SpecularReflectance
  Standard_EXPORT void SetSpecularReflectance(const double theSpecularReflectance);

  //! Returns field SpecularExponent
  Standard_EXPORT double SpecularExponent() const;

  //! Sets field SpecularExponent
  Standard_EXPORT void SetSpecularExponent(const double theSpecularExponent);

  //! Returns field SpecularColour
  Standard_EXPORT occ::handle<StepVisual_Colour> SpecularColour() const;

  //! Sets field SpecularColour
  Standard_EXPORT void SetSpecularColour(const occ::handle<StepVisual_Colour>& theSpecularColour);

  DEFINE_STANDARD_RTTIEXT(StepVisual_SurfaceStyleReflectanceAmbientDiffuseSpecular,
                          StepVisual_SurfaceStyleReflectanceAmbientDiffuse)

private:
  double                         mySpecularReflectance;
  double                         mySpecularExponent;
  occ::handle<StepVisual_Colour> mySpecularColour;
};
