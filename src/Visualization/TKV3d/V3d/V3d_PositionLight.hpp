#pragma once

#include <V3d_Light.hpp>

class V3d_PositionLight : public Graphic3d_CLight
{
  DEFINE_STANDARD_RTTIEXT(V3d_PositionLight, Graphic3d_CLight)
protected:
  Standard_EXPORT V3d_PositionLight(Graphic3d_TypeOfLightSource theType);

protected:
  using Graphic3d_CLight::Position;
  using Graphic3d_CLight::SetPosition;
};
