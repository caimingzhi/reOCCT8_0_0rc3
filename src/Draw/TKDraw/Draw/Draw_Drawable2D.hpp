#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Draw_Drawable3D.hpp>

class Draw_Drawable2D : public Draw_Drawable3D
{

public:
  Standard_EXPORT bool Is3D() const override;

  DEFINE_STANDARD_RTTIEXT(Draw_Drawable2D, Draw_Drawable3D)
};
