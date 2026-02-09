

#include <V3d_DirectionalLight.hpp>

#include <V3d.hpp>

IMPLEMENT_STANDARD_RTTIEXT(V3d_DirectionalLight, V3d_PositionLight)

V3d_DirectionalLight::V3d_DirectionalLight(const V3d_TypeOfOrientation theDirection,
                                           const Quantity_Color&       theColor,
                                           const bool                  theIsHeadlight)
    : V3d_PositionLight(Graphic3d_TypeOfLightSource_Directional)
{
  SetColor(theColor);
  SetHeadlight(theIsHeadlight);
  SetDirection(V3d::GetProjAxis(theDirection));
}

V3d_DirectionalLight::V3d_DirectionalLight(const gp_Dir&         theDirection,
                                           const Quantity_Color& theColor,
                                           const bool            theIsHeadlight)
    : V3d_PositionLight(Graphic3d_TypeOfLightSource_Directional)
{
  SetColor(theColor);
  SetHeadlight(theIsHeadlight);
  SetDirection(theDirection);
}

void V3d_DirectionalLight::SetDirection(V3d_TypeOfOrientation theDirection)
{
  SetDirection(V3d::GetProjAxis(theDirection));
}
