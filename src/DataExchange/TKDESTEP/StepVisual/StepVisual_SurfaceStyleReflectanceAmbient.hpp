#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <Standard_Transient.hpp>

//! Representation of STEP entity SurfaceStyleReflectanceAmbient
class StepVisual_SurfaceStyleReflectanceAmbient : public Standard_Transient
{
public:
  //! default constructor
  Standard_EXPORT StepVisual_SurfaceStyleReflectanceAmbient();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const double theAmbientReflectance);

  //! Returns field AmbientReflectance
  Standard_EXPORT double AmbientReflectance() const;
  //! Sets field AmbientReflectance
  Standard_EXPORT void SetAmbientReflectance(const double theAmbientReflectance);

  DEFINE_STANDARD_RTTIEXT(StepVisual_SurfaceStyleReflectanceAmbient, Standard_Transient)

private:
  double myAmbientReflectance;
};
