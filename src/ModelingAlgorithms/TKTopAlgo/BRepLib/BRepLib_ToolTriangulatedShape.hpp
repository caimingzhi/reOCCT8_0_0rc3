#pragma once

#include <Poly_Connect.hpp>
#include <Poly_Triangulation.hpp>

class TopoDS_Face;
class Poly_Triangulation;

class BRepLib_ToolTriangulatedShape
{
public:
  static void ComputeNormals(const TopoDS_Face&                     theFace,
                             const occ::handle<Poly_Triangulation>& theTris)
  {
    Poly_Connect aPolyConnect;
    ComputeNormals(theFace, theTris, aPolyConnect);
  }

  Standard_EXPORT static void ComputeNormals(const TopoDS_Face&                     theFace,
                                             const occ::handle<Poly_Triangulation>& theTris,
                                             Poly_Connect&                          thePolyConnect);
};
