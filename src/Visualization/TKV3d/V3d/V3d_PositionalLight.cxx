

#include <V3d_PositionalLight.hpp>

IMPLEMENT_STANDARD_RTTIEXT(V3d_PositionalLight, V3d_PositionLight)

V3d_PositionalLight::V3d_PositionalLight(const gp_Pnt& thePos, const Quantity_Color& theColor)
    : V3d_PositionLight(Graphic3d_TypeOfLightSource_Positional)
{
  SetColor(theColor);
  SetPosition(thePos);
}
