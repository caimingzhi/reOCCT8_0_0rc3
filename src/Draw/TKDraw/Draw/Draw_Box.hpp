#pragma once

#include <Standard.hpp>

#include <Bnd_OBB.hpp>
#include <Draw_Color.hpp>
#include <Draw_Drawable3D.hpp>
class Draw_Display;

class Draw_Box : public Draw_Drawable3D
{
public:
  Standard_EXPORT Draw_Box(const Bnd_OBB& theOBB, const Draw_Color& theColor);

  Standard_EXPORT void DrawOn(Draw_Display& theDis) const override;

  DEFINE_STANDARD_RTTIEXT(Draw_Box, Draw_Drawable3D)

protected:
  void ToWCS(const double theX, const double theY, const double theZ, gp_Pnt& theP) const;

  void MoveX(const double theShift, gp_Pnt& thePt) const;

  void MoveY(const double theShift, gp_Pnt& thePt) const;

  void MoveZ(const double theShift, gp_Pnt& thePt) const;

private:
  Bnd_OBB myOBB;

  Draw_Color myColor;
};
