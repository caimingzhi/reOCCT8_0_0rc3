#pragma once

#include <Draw_MarkerShape.hpp>
#include <Draw_Color.hpp>
#include <DrawTrSurf_Curve.hpp>

class Geom_BSplineCurve;

class DrawTrSurf_BSplineCurve : public DrawTrSurf_Curve
{
  DEFINE_STANDARD_RTTIEXT(DrawTrSurf_BSplineCurve, DrawTrSurf_Curve)
  Draw_Drawable3D_FACTORY
public:
  //! creates a drawable BSpline curve from a BSpline curve of package Geom.
  Standard_EXPORT DrawTrSurf_BSplineCurve(const occ::handle<Geom_BSplineCurve>& C);

  //! creates a drawable BSpline curve from a BSpline curve of package Geom.
  Standard_EXPORT DrawTrSurf_BSplineCurve(const occ::handle<Geom_BSplineCurve>& C,
                                          const Draw_Color&                     CurvColor,
                                          const Draw_Color&                     PolesColor,
                                          const Draw_Color&                     KnotsColor,
                                          const Draw_MarkerShape                KnotsShape,
                                          const int                             KnotsSize,
                                          const bool                            ShowPoles,
                                          const bool                            ShowKnots,
                                          const int                             Discret,
                                          const double                          Deflection,
                                          const int                             DrawMode);

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  Standard_EXPORT void DrawOn(Draw_Display& dis, const bool ShowPoles, const bool ShowKnots) const;

  Standard_EXPORT void DrawOn(Draw_Display& dis,
                              const double  U1,
                              const double  U2,
                              const int     Pindex,
                              const bool    ShowPoles = true,
                              const bool    ShowKnots = true) const;

  void ShowPoles() { drawPoles = true; }

  void ShowKnots() { drawKnots = true; }

  void ClearPoles() { drawPoles = false; }

  void ClearKnots() { drawKnots = false; }

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

  //! For variable copy.
  Standard_EXPORT occ::handle<Draw_Drawable3D> Copy() const override;

private:
  bool             drawPoles;
  bool             drawKnots;
  Draw_MarkerShape knotsForm;
  Draw_Color       knotsLook;
  int              knotsDim;
  Draw_Color       polesLook;
};
