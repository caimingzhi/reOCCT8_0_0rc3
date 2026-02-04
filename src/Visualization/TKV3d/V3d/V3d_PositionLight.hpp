#pragma once


#include <V3d_Light.hpp>

//! Base class for Positional, Spot and Directional Light classes.
class V3d_PositionLight : public Graphic3d_CLight
{
  DEFINE_STANDARD_RTTIEXT(V3d_PositionLight, Graphic3d_CLight)
protected:
  //! Protected constructor.
  Standard_EXPORT V3d_PositionLight(Graphic3d_TypeOfLightSource theType);

  //! @name hidden properties not applicable to positional light
protected:
  using Graphic3d_CLight::Position;
  using Graphic3d_CLight::SetPosition;
};

