#pragma once

#include <Standard.hpp>

#include <gp_Circ.hpp>
#include <Standard_Real.hpp>
#include <Draw_Color.hpp>
#include <Draw_Drawable3D.hpp>
class Draw_Display;

class Draw_Circle3D : public Draw_Drawable3D
{

public:
  Standard_EXPORT Draw_Circle3D(const gp_Circ&    C,
                                const double      A1,
                                const double      A2,
                                const Draw_Color& col);

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  DEFINE_STANDARD_RTTIEXT(Draw_Circle3D, Draw_Drawable3D)

private:
  gp_Circ    myCirc;
  double     myA1;
  double     myA2;
  Draw_Color myColor;
};
