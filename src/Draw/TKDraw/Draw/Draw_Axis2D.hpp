#pragma once


#include <Standard.hpp>

#include <gp_Ax22d.hpp>
#include <Draw_Color.hpp>
#include <Standard_Integer.hpp>
#include <Draw_Drawable2D.hpp>
class gp_Pnt2d;
class Draw_Display;

class Draw_Axis2D : public Draw_Drawable2D
{

public:
  Standard_EXPORT Draw_Axis2D(const Draw_Color& col, const int Size = 5);

  Standard_EXPORT Draw_Axis2D(const gp_Pnt2d& p, const Draw_Color& col, const int Size = 5);

  Standard_EXPORT Draw_Axis2D(const gp_Ax22d& A, const Draw_Color& col, const int Size = 5);

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  DEFINE_STANDARD_RTTIEXT(Draw_Axis2D, Draw_Drawable2D)

private:
  gp_Ax22d   myAxes;
  Draw_Color myColor;
  int        mySize;
};

