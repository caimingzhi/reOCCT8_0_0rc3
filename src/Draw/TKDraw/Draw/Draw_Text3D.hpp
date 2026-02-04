#pragma once


#include <Standard.hpp>

#include <gp_Pnt.hpp>
#include <Draw_Color.hpp>
#include <TCollection_AsciiString.hpp>
#include <Draw_Drawable3D.hpp>
class Draw_Display;

class Draw_Text3D : public Draw_Drawable3D
{

public:
  Standard_EXPORT Draw_Text3D(const gp_Pnt& p, const char* T, const Draw_Color& col);

  Standard_EXPORT Draw_Text3D(const gp_Pnt&     p,
                              const char*       T,
                              const Draw_Color& col,
                              const double      moveX,
                              const double      moveY);

  Standard_EXPORT void SetPnt(const gp_Pnt& p);

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  DEFINE_STANDARD_RTTIEXT(Draw_Text3D, Draw_Drawable3D)

private:
  gp_Pnt                  myPoint;
  Draw_Color              myColor;
  TCollection_AsciiString myText;
  double                  mymoveX;
  double                  mymoveY;
};

