#pragma once


#include <V3d_PositionLight.hpp>

//! Creation and modification of an isolated (positional) light source.
//! It is also defined by the color and two attenuation factors ConstAttentuation() and
//! LinearAttentuation(). The resulting attenuation factor determining the illumination of a surface
//! depends on the following formula:
//! @code
//!   F = 1 / (ConstAttenuation() + LinearAttenuation() * Distance)
//! @endcode
//! Where Distance is the distance of the isolated source from the surface.
class V3d_PositionalLight : public V3d_PositionLight
{
  DEFINE_STANDARD_RTTIEXT(V3d_PositionalLight, V3d_PositionLight)
public:
  //! Creates an isolated light source in the viewer with default attenuation factors (1.0, 0.0).
  Standard_EXPORT V3d_PositionalLight(const gp_Pnt&         thePos,
                                      const Quantity_Color& theColor = Quantity_NOC_WHITE);

  using Graphic3d_CLight::Position;
  using Graphic3d_CLight::SetPosition;

  //! @name hidden properties not applicable to positional light
private:
  using Graphic3d_CLight::Angle;
  using Graphic3d_CLight::Concentration;
  using Graphic3d_CLight::Direction;
  using Graphic3d_CLight::SetAngle;
  using Graphic3d_CLight::SetConcentration;
  using Graphic3d_CLight::SetDirection;
};

