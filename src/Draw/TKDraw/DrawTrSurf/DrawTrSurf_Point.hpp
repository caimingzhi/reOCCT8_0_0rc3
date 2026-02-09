#pragma once

#include <gp_Pnt.hpp>
#include <Draw_MarkerShape.hpp>
#include <Draw_Color.hpp>
#include <Draw_Drawable3D.hpp>
#include <Draw_Interpretor.hpp>

class DrawTrSurf_Point : public Draw_Drawable3D
{
  DEFINE_STANDARD_RTTIEXT(DrawTrSurf_Point, Draw_Drawable3D)
  Draw_Drawable3D_FACTORY
public:
  Standard_EXPORT DrawTrSurf_Point(const gp_Pnt&          P,
                                   const Draw_MarkerShape Shape,
                                   const Draw_Color&      Col);

  Standard_EXPORT DrawTrSurf_Point(const gp_Pnt2d&        P,
                                   const Draw_MarkerShape Shape,
                                   const Draw_Color&      Col);

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  Standard_EXPORT bool Is3D() const override;

  gp_Pnt Point() const { return myPoint; }

  Standard_EXPORT void Point(const gp_Pnt& P);

  gp_Pnt2d Point2d() const { return gp_Pnt2d(myPoint.X(), myPoint.Y()); }

  Standard_EXPORT void Point2d(const gp_Pnt2d& P);

  void Color(const Draw_Color& theColor) { myColor = theColor; }

  Draw_Color Color() const { return myColor; }

  void Shape(const Draw_MarkerShape theS) { myShape = theS; }

  Draw_MarkerShape Shape() const { return myShape; }

  Standard_EXPORT occ::handle<Draw_Drawable3D> Copy() const override;

  Standard_EXPORT void Dump(Standard_OStream& S) const override;

  Standard_EXPORT void Save(Standard_OStream& theStream) const override;

  Standard_EXPORT void Whatis(Draw_Interpretor& I) const override;

private:
  gp_Pnt           myPoint;
  bool             is3D;
  Draw_MarkerShape myShape;
  Draw_Color       myColor;
};
