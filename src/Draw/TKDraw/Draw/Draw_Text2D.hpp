#pragma once


#include <Standard.hpp>

#include <gp_Pnt2d.hpp>
#include <Draw_Color.hpp>
#include <TCollection_AsciiString.hpp>
#include <Standard_Integer.hpp>
#include <Draw_Drawable2D.hpp>
class Draw_Display;

class Draw_Text2D : public Draw_Drawable2D
{

public:
  Standard_EXPORT Draw_Text2D(const gp_Pnt2d& p, const char* T, const Draw_Color& col);

  Standard_EXPORT Draw_Text2D(const gp_Pnt2d&   p,
                              const char*       T,
                              const Draw_Color& col,
                              const int         moveX,
                              const int         moveY);

  Standard_EXPORT void SetPnt2d(const gp_Pnt2d& p);

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  DEFINE_STANDARD_RTTIEXT(Draw_Text2D, Draw_Drawable2D)

private:
  gp_Pnt2d                myPoint;
  Draw_Color              myColor;
  TCollection_AsciiString myText;
  int                     mymoveX;
  int                     mymoveY;
};

