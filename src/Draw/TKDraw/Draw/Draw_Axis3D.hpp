#pragma once

#include <Standard.hpp>

#include <gp_Ax3.hpp>
#include <Draw_Color.hpp>
#include <Standard_Integer.hpp>
#include <Draw_Drawable3D.hpp>
class gp_Pnt;
class Draw_Display;

class Draw_Axis3D : public Draw_Drawable3D
{

public:
  Standard_EXPORT Draw_Axis3D(const Draw_Color& col, const int Size = 5);

  Standard_EXPORT Draw_Axis3D(const gp_Pnt& p, const Draw_Color& col, const int Size = 5);

  Standard_EXPORT Draw_Axis3D(const gp_Ax3& A, const Draw_Color& col, const int Size = 5);

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  DEFINE_STANDARD_RTTIEXT(Draw_Axis3D, Draw_Drawable3D)

private:
  gp_Ax3     myAxes;
  Draw_Color myColor;
  int        mySize;
};
