#pragma once

#include <Draw_Color.hpp>
#include <DrawTrSurf_Curve2d.hpp>

class Geom2d_BezierCurve;

class DrawTrSurf_BezierCurve2d : public DrawTrSurf_Curve2d
{
  DEFINE_STANDARD_RTTIEXT(DrawTrSurf_BezierCurve2d, DrawTrSurf_Curve2d)
  Draw_Drawable3D_FACTORY
public:
  Standard_EXPORT DrawTrSurf_BezierCurve2d(const occ::handle<Geom2d_BezierCurve>& C);

  Standard_EXPORT DrawTrSurf_BezierCurve2d(const occ::handle<Geom2d_BezierCurve>& C,
                                           const Draw_Color&                      CurvColor,
                                           const Draw_Color&                      PolesColor,
                                           const bool                             ShowPoles,
                                           const int                              Discret);

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  void ShowPoles() { drawPoles = true; }

  void ClearPoles() { drawPoles = false; }

  Standard_EXPORT void FindPole(const double        X,
                                const double        Y,
                                const Draw_Display& D,
                                const double        Prec,
                                int&                Index) const;

  void SetPolesColor(const Draw_Color& theColor) { polesLook = theColor; }

  Draw_Color PolesColor() const { return polesLook; }

  Standard_EXPORT occ::handle<Draw_Drawable3D> Copy() const override;

private:
  bool       drawPoles;
  Draw_Color polesLook;
};
