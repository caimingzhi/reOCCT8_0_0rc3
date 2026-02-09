#pragma once

#include <Draw_Drawable3D.hpp>
#include <Draw_Interpretor.hpp>

class Poly_Polygon3D;

class DrawTrSurf_Polygon3D : public Draw_Drawable3D
{
  DEFINE_STANDARD_RTTIEXT(DrawTrSurf_Polygon3D, Draw_Drawable3D)
  Draw_Drawable3D_FACTORY
public:
  Standard_EXPORT DrawTrSurf_Polygon3D(const occ::handle<Poly_Polygon3D>& P);

  occ::handle<Poly_Polygon3D> Polygon3D() const { return myPolygon3D; }

  void ShowNodes(const bool theB) { myNodes = theB; }

  bool ShowNodes() const { return myNodes; }

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  Standard_EXPORT occ::handle<Draw_Drawable3D> Copy() const override;

  Standard_EXPORT void Dump(Standard_OStream& S) const override;

  Standard_EXPORT void Save(Standard_OStream& theStream) const override;

  Standard_EXPORT void Whatis(Draw_Interpretor& I) const override;

private:
  occ::handle<Poly_Polygon3D> myPolygon3D;
  bool                        myNodes;
};
