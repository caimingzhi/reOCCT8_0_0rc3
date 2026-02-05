#pragma once

#include <V3d_PositionLight.hpp>
#include <V3d_TypeOfOrientation.hpp>

//! Creation and modification of a spot.
//! The attenuation factor F determines the illumination of a surface:
//! @code
//!   F = 1/(ConstAttenuation() + LinearAttenuation() * Distance)
//! @endcode
//! Where Distance is the distance from the source to the surface.
//! The default values (1.0, 0.0) correspond to a minimum of attenuation.
//! The concentration factor determines the dispersion of the light on the surface, the default
//! value (1.0) corresponds to a minimum of dispersion.
class V3d_SpotLight : public V3d_PositionLight
{
  DEFINE_STANDARD_RTTIEXT(V3d_SpotLight, V3d_PositionLight)
public:
  //! Creates a light source of the Spot type in the viewer with default attenuation factors (1.0,
  //! 0.0), concentration factor 1.0 and spot angle 30 degrees.
  Standard_EXPORT V3d_SpotLight(const gp_Pnt&               thePos,
                                const V3d_TypeOfOrientation theDirection = V3d_XnegYnegZpos,
                                const Quantity_Color&       theColor     = Quantity_NOC_WHITE);

  //! Creates a light source of the Spot type in the viewer with default attenuation factors (1.0,
  //! 0.0), concentration factor 1.0 and spot angle 30 degrees.
  Standard_EXPORT V3d_SpotLight(const gp_Pnt&         thePos,
                                const gp_Dir&         theDirection,
                                const Quantity_Color& theColor = Quantity_NOC_WHITE);

  //! Defines the direction of the light source
  //! according to a predefined directional vector.
  Standard_EXPORT void SetDirection(V3d_TypeOfOrientation theOrientation);
  using Graphic3d_CLight::Position;
  using Graphic3d_CLight::SetDirection;
  using Graphic3d_CLight::SetPosition;
};
