#pragma once

#include <V3d_PositionLight.hpp>
#include <V3d_TypeOfOrientation.hpp>

class V3d_SpotLight : public V3d_PositionLight
{
  DEFINE_STANDARD_RTTIEXT(V3d_SpotLight, V3d_PositionLight)
public:
  Standard_EXPORT V3d_SpotLight(const gp_Pnt&               thePos,
                                const V3d_TypeOfOrientation theDirection = V3d_XnegYnegZpos,
                                const Quantity_Color&       theColor     = Quantity_NOC_WHITE);

  Standard_EXPORT V3d_SpotLight(const gp_Pnt&         thePos,
                                const gp_Dir&         theDirection,
                                const Quantity_Color& theColor = Quantity_NOC_WHITE);

  Standard_EXPORT void SetDirection(V3d_TypeOfOrientation theOrientation);
  using Graphic3d_CLight::Position;
  using Graphic3d_CLight::SetDirection;
  using Graphic3d_CLight::SetPosition;
};
