#pragma once

#include <V3d_Light.hpp>

class V3d_AmbientLight : public Graphic3d_CLight
{
  DEFINE_STANDARD_RTTIEXT(V3d_AmbientLight, Graphic3d_CLight)
public:
  Standard_EXPORT V3d_AmbientLight(const Quantity_Color& theColor = Quantity_NOC_WHITE);

private:
  using Graphic3d_CLight::Angle;
  using Graphic3d_CLight::Attenuation;
  using Graphic3d_CLight::Concentration;
  using Graphic3d_CLight::ConstAttenuation;
  using Graphic3d_CLight::Direction;
  using Graphic3d_CLight::Headlight;
  using Graphic3d_CLight::IsHeadlight;
  using Graphic3d_CLight::LinearAttenuation;
  using Graphic3d_CLight::Position;
  using Graphic3d_CLight::SetAngle;
  using Graphic3d_CLight::SetAttenuation;
  using Graphic3d_CLight::SetConcentration;
  using Graphic3d_CLight::SetDirection;
  using Graphic3d_CLight::SetHeadlight;
  using Graphic3d_CLight::SetPosition;
  using Graphic3d_CLight::SetSmoothAngle;
  using Graphic3d_CLight::SetSmoothRadius;
  using Graphic3d_CLight::Smoothness;
};
