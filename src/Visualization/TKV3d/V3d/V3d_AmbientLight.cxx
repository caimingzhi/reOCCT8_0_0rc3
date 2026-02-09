#include <V3d_AmbientLight.hpp>

#include <V3d_Viewer.hpp>

IMPLEMENT_STANDARD_RTTIEXT(V3d_AmbientLight, Graphic3d_CLight)

V3d_AmbientLight::V3d_AmbientLight(const Quantity_Color& theColor)
    : Graphic3d_CLight(Graphic3d_TypeOfLightSource_Ambient)
{
  SetColor(theColor);
}
