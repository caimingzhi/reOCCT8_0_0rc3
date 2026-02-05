#pragma once

#include <Poly_Connect.hpp>
#include <Poly_Triangulation.hpp>

class TopoDS_Face;
class Poly_Triangulation;

//! Provides methods for calculating normals to Poly_Triangulation of TopoDS_Face.
class BRepLib_ToolTriangulatedShape
{
public:
  //! Computes nodal normals for Poly_Triangulation structure using UV coordinates and surface.
  //! Does nothing if triangulation already defines normals.
  //! @param[in] theFace the face
  //! @param[in] theTris the definition of a face triangulation
  static void ComputeNormals(const TopoDS_Face&                     theFace,
                             const occ::handle<Poly_Triangulation>& theTris)
  {
    Poly_Connect aPolyConnect;
    ComputeNormals(theFace, theTris, aPolyConnect);
  }

  //! Computes nodal normals for Poly_Triangulation structure using UV coordinates and surface.
  //! Does nothing if triangulation already defines normals.
  //! @param[in] theFace the face
  //! @param[in] theTris the definition of a face triangulation
  //! @param[in,out] thePolyConnect optional, initialized tool for exploring triangulation
  Standard_EXPORT static void ComputeNormals(const TopoDS_Face&                     theFace,
                                             const occ::handle<Poly_Triangulation>& theTris,
                                             Poly_Connect&                          thePolyConnect);
};
