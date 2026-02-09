#pragma once

#include <Draw_Color.hpp>
#include <DrawTrSurf_Drawable.hpp>
#include <Draw_Interpretor.hpp>

class Geom_Curve;
class Draw_Display;

class DrawTrSurf_Curve : public DrawTrSurf_Drawable
{
  DEFINE_STANDARD_RTTIEXT(DrawTrSurf_Curve, DrawTrSurf_Drawable)
  Draw_Drawable3D_FACTORY
public:
  Standard_EXPORT DrawTrSurf_Curve(const occ::handle<Geom_Curve>& C, const bool DispOrigin = true);

  Standard_EXPORT DrawTrSurf_Curve(const occ::handle<Geom_Curve>& C,
                                   const Draw_Color&              aColor,
                                   const int                      Discret,
                                   const double                   Deflection,
                                   const int                      DrawMode,
                                   const bool                     DispOrigin     = true,
                                   const bool                     DispCurvRadius = false,
                                   const double                   RadiusMax      = 1.0e3,
                                   const double                   RatioOfRadius  = 0.1);

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  occ::handle<Geom_Curve> GetCurve() const { return curv; }

  void SetColor(const Draw_Color& theColor) { look = theColor; }

  bool DisplayOrigin() const { return disporigin; }

  void DisplayOrigin(const bool V) { disporigin = V; }

  void ShowCurvature() { dispcurvradius = true; }

  void ClearCurvature() { dispcurvradius = false; }

  void SetRadiusMax(const double theRadius) { radiusmax = theRadius; }

  void SetRadiusRatio(const double theRatio) { radiusratio = theRatio; }

  Draw_Color Color() const { return look; }

  double RadiusMax() const { return radiusmax; }

  double RadiusRatio() const { return radiusratio; }

  Standard_EXPORT occ::handle<Draw_Drawable3D> Copy() const override;

  Standard_EXPORT void Dump(Standard_OStream& S) const override;

  Standard_EXPORT void Save(Standard_OStream& theStream) const override;

  Standard_EXPORT void Whatis(Draw_Interpretor& I) const override;

protected:
  occ::handle<Geom_Curve> curv;
  Draw_Color              look;
  bool                    disporigin;
  bool                    dispcurvradius;
  double                  radiusmax;
  double                  radiusratio;
};
