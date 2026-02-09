#pragma once

#include <V3d_PositionLight.hpp>
#include <V3d_TypeOfOrientation.hpp>

class V3d_DirectionalLight : public V3d_PositionLight
{
  DEFINE_STANDARD_RTTIEXT(V3d_DirectionalLight, V3d_PositionLight)
public:
  Standard_EXPORT V3d_DirectionalLight(const V3d_TypeOfOrientation theDirection = V3d_XposYposZpos,
                                       const Quantity_Color&       theColor = Quantity_NOC_WHITE,
                                       const bool                  theIsHeadlight = false);

  Standard_EXPORT V3d_DirectionalLight(const gp_Dir&         theDirection,
                                       const Quantity_Color& theColor       = Quantity_NOC_WHITE,
                                       const bool            theIsHeadlight = false);

  Standard_EXPORT void SetDirection(V3d_TypeOfOrientation theDirection);
  using Graphic3d_CLight::SetDirection;

private:
  using Graphic3d_CLight::Angle;
  using Graphic3d_CLight::Attenuation;
  using Graphic3d_CLight::Concentration;
  using Graphic3d_CLight::ConstAttenuation;
  using Graphic3d_CLight::LinearAttenuation;
  using Graphic3d_CLight::Position;
  using Graphic3d_CLight::SetAngle;
  using Graphic3d_CLight::SetAttenuation;
  using Graphic3d_CLight::SetConcentration;
  using Graphic3d_CLight::SetPosition;
};
