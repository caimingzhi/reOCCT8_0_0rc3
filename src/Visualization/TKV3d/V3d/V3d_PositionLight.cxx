

#include <V3d_PositionLight.hpp>

IMPLEMENT_STANDARD_RTTIEXT(V3d_PositionLight, Graphic3d_CLight)

V3d_PositionLight::V3d_PositionLight(Graphic3d_TypeOfLightSource theType)
    : Graphic3d_CLight(theType)
{
}
