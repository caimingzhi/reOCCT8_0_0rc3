#pragma once

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Draw_Drawable3D.hpp>
#include <Draw_Interpretor.hpp>

class Poly_Triangulation;

//! Used to display a triangulation.
//!
//! Display internal edges in blue
//! Display boundary edges in red
//! Optional display of triangles and nodes indices.
class DrawTrSurf_Triangulation : public Draw_Drawable3D
{
  DEFINE_STANDARD_RTTIEXT(DrawTrSurf_Triangulation, Draw_Drawable3D)
  Draw_Drawable3D_FACTORY
public:
  Standard_EXPORT DrawTrSurf_Triangulation(const occ::handle<Poly_Triangulation>& T);

  occ::handle<Poly_Triangulation> Triangulation() const { return myTriangulation; }

  void ShowNodes(const bool theB) { myNodes = theB; }

  bool ShowNodes() const { return myNodes; }

  void ShowTriangles(const bool theB) { myTriangles = theB; }

  bool ShowTriangles() const { return myTriangles; }

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  //! For variable copy.
  Standard_EXPORT occ::handle<Draw_Drawable3D> Copy() const override;

  //! For variable dump.
  Standard_EXPORT void Dump(Standard_OStream& S) const override;

  //! Save drawable into stream.
  Standard_EXPORT void Save(Standard_OStream& theStream) const override;

  //! For variable whatis command. Set as a result the type of the variable.
  Standard_EXPORT void Whatis(Draw_Interpretor& I) const override;

private:
  occ::handle<Poly_Triangulation>       myTriangulation;
  occ::handle<NCollection_HArray1<int>> myInternals;
  occ::handle<NCollection_HArray1<int>> myFree;
  bool                                  myNodes;
  bool                                  myTriangles;
};
