#pragma once

#include <Draw_Color.hpp>
#include <DrawTrSurf_Surface.hpp>

class Geom_BezierSurface;

class DrawTrSurf_BezierSurface : public DrawTrSurf_Surface
{
  DEFINE_STANDARD_RTTIEXT(DrawTrSurf_BezierSurface, DrawTrSurf_Surface)
  Draw_Drawable3D_FACTORY
public:
  Standard_EXPORT DrawTrSurf_BezierSurface(const occ::handle<Geom_BezierSurface>& S);

  Standard_EXPORT DrawTrSurf_BezierSurface(const occ::handle<Geom_BezierSurface>& S,
                                           const int                              NbUIsos,
                                           const int                              NbVIsos,
                                           const Draw_Color&                      BoundsColor,
                                           const Draw_Color&                      IsosColor,
                                           const Draw_Color&                      PolesColor,
                                           const bool                             ShowPoles,
                                           const int                              Discret,
                                           const double                           Deflection,
                                           const int                              DrawMode);

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  void ShowPoles() { drawPoles = true; }

  void ClearPoles() { drawPoles = false; }

  Standard_EXPORT void FindPole(const double        X,
                                const double        Y,
                                const Draw_Display& D,
                                const double        Prec,
                                int&                UIndex,
                                int&                VIndex) const;

  void SetPolesColor(const Draw_Color& theColor) { polesLook = theColor; }

  Draw_Color PolesColor() const { return polesLook; }

  Standard_EXPORT occ::handle<Draw_Drawable3D> Copy() const override;

private:
  bool       drawPoles;
  Draw_Color polesLook;
};
