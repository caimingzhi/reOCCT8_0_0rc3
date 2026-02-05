#pragma once

#include <Standard.hpp>

#include <gp_Circ2d.hpp>
#include <Standard_Real.hpp>
#include <Draw_Color.hpp>
#include <Draw_Drawable2D.hpp>
class Draw_Display;

class Draw_Circle2D : public Draw_Drawable2D
{

public:
  Standard_EXPORT Draw_Circle2D(const gp_Circ2d&  C,
                                const double      A1,
                                const double      A2,
                                const Draw_Color& col);

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  DEFINE_STANDARD_RTTIEXT(Draw_Circle2D, Draw_Drawable2D)

private:
  gp_Circ2d  myCirc;
  double     myA1;
  double     myA2;
  Draw_Color myColor;
};
