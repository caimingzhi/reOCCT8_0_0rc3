#pragma once


#include <Standard.hpp>

#include <gp_Pnt.hpp>
#include <Draw_Color.hpp>
#include <Draw_Drawable3D.hpp>
class Draw_Display;

class Draw_Segment3D : public Draw_Drawable3D
{

public:
  Standard_EXPORT Draw_Segment3D(const gp_Pnt& p1, const gp_Pnt& p2, const Draw_Color& col);

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  Standard_EXPORT const gp_Pnt& First() const;

  Standard_EXPORT void First(const gp_Pnt& P);

  Standard_EXPORT const gp_Pnt& Last() const;

  Standard_EXPORT void Last(const gp_Pnt& P);

  DEFINE_STANDARD_RTTIEXT(Draw_Segment3D, Draw_Drawable3D)

private:
  gp_Pnt     myFirst;
  gp_Pnt     myLast;
  Draw_Color myColor;
};

