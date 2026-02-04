#pragma once


#include <StepVisual_SurfaceStyleReflectanceAmbient.hpp>

//! Representation of STEP entity SurfaceStyleReflectanceAmbientDiffuse
class StepVisual_SurfaceStyleReflectanceAmbientDiffuse
    : public StepVisual_SurfaceStyleReflectanceAmbient
{
public:
  //! default constructor
  Standard_EXPORT StepVisual_SurfaceStyleReflectanceAmbientDiffuse();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const double theAmbientReflectance, const double theDiffuseReflectance);

  //! Returns field DiffuseReflectance
  Standard_EXPORT double DiffuseReflectance() const;

  //! Sets field DiffuseReflectance
  Standard_EXPORT void SetDiffuseReflectance(const double theDiffuseReflectance);

  DEFINE_STANDARD_RTTIEXT(StepVisual_SurfaceStyleReflectanceAmbientDiffuse,
                          StepVisual_SurfaceStyleReflectanceAmbient)

private:
  double myDiffuseReflectance;
};
