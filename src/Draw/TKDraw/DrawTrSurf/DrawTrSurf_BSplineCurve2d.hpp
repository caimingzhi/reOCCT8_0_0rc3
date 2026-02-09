#pragma once

#include <Draw_MarkerShape.hpp>
#include <Draw_Color.hpp>
#include <DrawTrSurf_Curve2d.hpp>

class Geom2d_BSplineCurve;

class DrawTrSurf_BSplineCurve2d : public DrawTrSurf_Curve2d
{
  DEFINE_STANDARD_RTTIEXT(DrawTrSurf_BSplineCurve2d, DrawTrSurf_Curve2d)
  Draw_Drawable3D_FACTORY
public:
  Standard_EXPORT DrawTrSurf_BSplineCurve2d(const occ::handle<Geom2d_BSplineCurve>& C);

  Standard_EXPORT DrawTrSurf_BSplineCurve2d(const occ::handle<Geom2d_BSplineCurve>& C,
                                            const Draw_Color&                       CurvColor,
                                            const Draw_Color&                       PolesColor,
                                            const Draw_Color&                       KnotsColor,
                                            const Draw_MarkerShape                  KnotsShape,
                                            const int                               KnotsSize,
                                            const bool                              ShowPoles,
                                            const bool                              ShowKnots,
                                            const int                               Discret);

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  void ShowPoles() { drawPoles = true; }

  void ShowKnots() { drawKnots = true; }

  void ClearPoles() { drawPoles = false; }

  void ClearKnots() { drawKnots = false; }

  Standard_EXPORT void FindPole(const double        X,
                                const double        Y,
                                const Draw_Display& D,
                                const double        Prec,
                                int&                Index) const;

  Standard_EXPORT void FindKnot(const double        X,
                                const double        Y,
                                const Draw_Display& D,
                                const double        Prec,
                                int&                Index) const;

  void SetPolesColor(const Draw_Color& theColor) { polesLook = theColor; }

  void SetKnotsColor(const Draw_Color& theColor) { knotsLook = theColor; }

  void SetKnotsShape(const Draw_MarkerShape theShape) { knotsForm = theShape; }

  Draw_MarkerShape KnotsShape() const { return knotsForm; }

  Draw_Color KnotsColor() const { return knotsLook; }

  Draw_Color PolesColor() const { return polesLook; }

  Standard_EXPORT occ::handle<Draw_Drawable3D> Copy() const override;

private:
  bool             drawPoles;
  bool             drawKnots;
  Draw_MarkerShape knotsForm;
  Draw_Color       knotsLook;
  int              knotsDim;
  Draw_Color       polesLook;
};
