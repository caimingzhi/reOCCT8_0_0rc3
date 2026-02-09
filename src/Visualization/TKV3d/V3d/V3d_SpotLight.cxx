

#include <V3d_SpotLight.hpp>

#include <V3d.hpp>

IMPLEMENT_STANDARD_RTTIEXT(V3d_SpotLight, V3d_PositionLight)

V3d_SpotLight::V3d_SpotLight(const gp_Pnt&               thePos,
                             const V3d_TypeOfOrientation theDirection,
                             const Quantity_Color&       theColor)
    : V3d_PositionLight(Graphic3d_TypeOfLightSource_Spot)
{
  SetColor(theColor);
  SetPosition(thePos);
  SetDirection(V3d::GetProjAxis(theDirection));
}

V3d_SpotLight::V3d_SpotLight(const gp_Pnt&         thePos,
                             const gp_Dir&         theDirection,
                             const Quantity_Color& theColor)
    : V3d_PositionLight(Graphic3d_TypeOfLightSource_Spot)
{
  SetColor(theColor);
  SetPosition(thePos);
  SetDirection(theDirection);
}

void V3d_SpotLight::SetDirection(V3d_TypeOfOrientation theDirection)
{
  SetDirection(V3d::GetProjAxis(theDirection));
}
