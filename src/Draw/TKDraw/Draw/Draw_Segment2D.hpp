#pragma once

#include <Standard.hpp>

#include <gp_Pnt2d.hpp>
#include <Draw_Color.hpp>
#include <Draw_Drawable2D.hpp>
#include <Standard_OStream.hpp>
#include <Draw_Interpretor.hpp>
class Draw_Display;

class Draw_Segment2D : public Draw_Drawable2D
{

public:
  Standard_EXPORT Draw_Segment2D(const gp_Pnt2d& p1, const gp_Pnt2d& p2, const Draw_Color& col);

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  Standard_EXPORT const gp_Pnt2d& First() const;

  Standard_EXPORT void First(const gp_Pnt2d& P);

  Standard_EXPORT const gp_Pnt2d& Last() const;

  Standard_EXPORT void Last(const gp_Pnt2d& P);

  Standard_EXPORT void Dump(Standard_OStream& S) const override;

  Standard_EXPORT void Whatis(Draw_Interpretor& I) const override;

  DEFINE_STANDARD_RTTIEXT(Draw_Segment2D, Draw_Drawable2D)

private:
  gp_Pnt2d   myFirst;
  gp_Pnt2d   myLast;
  Draw_Color myColor;
};
