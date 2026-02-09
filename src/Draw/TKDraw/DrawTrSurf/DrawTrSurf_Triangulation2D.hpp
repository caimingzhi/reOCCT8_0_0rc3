#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Draw_Drawable2D.hpp>
#include <Standard_OStream.hpp>
#include <Draw_Interpretor.hpp>
class Poly_Triangulation;
class Draw_Display;
class Draw_Drawable3D;

class DrawTrSurf_Triangulation2D : public Draw_Drawable2D
{

public:
  Standard_EXPORT DrawTrSurf_Triangulation2D(const occ::handle<Poly_Triangulation>& T);

  Standard_EXPORT occ::handle<Poly_Triangulation> Triangulation() const;

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  Standard_EXPORT occ::handle<Draw_Drawable3D> Copy() const override;

  Standard_EXPORT void Dump(Standard_OStream& S) const override;

  Standard_EXPORT void Whatis(Draw_Interpretor& I) const override;

  DEFINE_STANDARD_RTTIEXT(DrawTrSurf_Triangulation2D, Draw_Drawable2D)

private:
  occ::handle<Poly_Triangulation>       myTriangulation;
  occ::handle<NCollection_HArray1<int>> myInternals;
  occ::handle<NCollection_HArray1<int>> myFree;
};
