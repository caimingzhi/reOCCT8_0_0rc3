#pragma once

#include <Draw_Drawable3D.hpp>
#include <GeomAbs_IsoType.hpp>

class Adaptor2d_Curve2d;
class Adaptor3d_Curve;
class Adaptor3d_IsoCurve;

class DrawTrSurf_Drawable : public Draw_Drawable3D
{
  DEFINE_STANDARD_RTTIEXT(DrawTrSurf_Drawable, Draw_Drawable3D)
public:
  Standard_EXPORT void DrawCurve2dOn(Adaptor2d_Curve2d& C, Draw_Display& D) const;

  Standard_EXPORT void DrawCurveOn(Adaptor3d_Curve& C, Draw_Display& D) const;

  Standard_EXPORT void DrawIsoCurveOn(Adaptor3d_IsoCurve&   C,
                                      const GeomAbs_IsoType T,
                                      const double          P,
                                      const double          F,
                                      const double          L,
                                      Draw_Display&         D) const;

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override = 0;

  void SetDiscretisation(const int theDiscret) { myDiscret = theDiscret; }

  int GetDiscretisation() const { return myDiscret; }

  void SetDeflection(const double theDeflection) { myDeflection = theDeflection; }

  double GetDeflection() const { return myDeflection; }

  void SetDrawMode(const int theDrawMode) { myDrawMode = theDrawMode; }

  int GetDrawMode() const { return myDrawMode; }

protected:
  Standard_EXPORT DrawTrSurf_Drawable(const int    discret,
                                      const double deflection = 0.01,
                                      const int    DrawMode   = 0);

private:
  int    myDrawMode;
  int    myDiscret;
  double myDeflection;
};
