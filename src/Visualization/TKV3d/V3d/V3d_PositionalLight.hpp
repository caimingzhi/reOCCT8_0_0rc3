#pragma once

#include <V3d_PositionLight.hpp>

class V3d_PositionalLight : public V3d_PositionLight
{
  DEFINE_STANDARD_RTTIEXT(V3d_PositionalLight, V3d_PositionLight)
public:
  Standard_EXPORT V3d_PositionalLight(const gp_Pnt&         thePos,
                                      const Quantity_Color& theColor = Quantity_NOC_WHITE);

  using Graphic3d_CLight::Position;
  using Graphic3d_CLight::SetPosition;

private:
  using Graphic3d_CLight::Angle;
  using Graphic3d_CLight::Concentration;
  using Graphic3d_CLight::Direction;
  using Graphic3d_CLight::SetAngle;
  using Graphic3d_CLight::SetConcentration;
  using Graphic3d_CLight::SetDirection;
};
