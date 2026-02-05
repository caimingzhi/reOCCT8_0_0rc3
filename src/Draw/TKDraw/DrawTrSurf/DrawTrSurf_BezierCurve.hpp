#pragma once

#include <Draw_Color.hpp>
#include <DrawTrSurf_Curve.hpp>

class Geom_BezierCurve;

class DrawTrSurf_BezierCurve : public DrawTrSurf_Curve
{
  DEFINE_STANDARD_RTTIEXT(DrawTrSurf_BezierCurve, DrawTrSurf_Curve)
  Draw_Drawable3D_FACTORY
public:
  //! creates a drawable Bezier curve from a Bezier curve of package Geom.
  Standard_EXPORT DrawTrSurf_BezierCurve(const occ::handle<Geom_BezierCurve>& C);

  Standard_EXPORT DrawTrSurf_BezierCurve(const occ::handle<Geom_BezierCurve>& C,
                                         const Draw_Color&                    CurvColor,
                                         const Draw_Color&                    PolesColor,
                                         const bool                           ShowPoles,
                                         const int                            Discret,
                                         const double                         Deflection,
                                         const int                            DrawMode);

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  void ShowPoles() { drawPoles = true; }

  void ClearPoles() { drawPoles = false; }

  //! Returns in <Index> the index of the first pole of the
  //! curve projected by the Display <D> at a distance lower
  //! than <Prec> from <X,Y>. If no pole is found index is
  //! set to 0, else index is always greater than the input
  //! value of index.
  Standard_EXPORT void FindPole(const double        X,
                                const double        Y,
                                const Draw_Display& D,
                                const double        Prec,
                                int&                Index) const;

  void SetPolesColor(const Draw_Color& theColor) { polesLook = theColor; }

  Draw_Color PolesColor() const { return polesLook; }

  //! For variable copy.
  Standard_EXPORT occ::handle<Draw_Drawable3D> Copy() const override;

private:
  bool       drawPoles;
  Draw_Color polesLook;
};
