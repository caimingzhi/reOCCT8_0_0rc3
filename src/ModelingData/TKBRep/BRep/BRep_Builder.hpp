#pragma once

#include <GeomAbs_Shape.hpp>
#include <Poly_Triangulation.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <TopoDS_Builder.hpp>

class TopoDS_Face;
class Geom_Surface;
class TopLoc_Location;
class Poly_Triangulation;
class TopoDS_Edge;
class Geom_Curve;
class Poly_Polygon3D;
class Poly_PolygonOnTriangulation;
class Geom2d_Curve;
class gp_Pnt2d;
class Poly_Polygon2D;
class TopoDS_Vertex;
class gp_Pnt;

class BRep_Builder : public TopoDS_Builder
{
public:
  DEFINE_STANDARD_ALLOC

  void MakeFace(TopoDS_Face& F) const;

  Standard_EXPORT void MakeFace(TopoDS_Face&                     F,
                                const occ::handle<Geom_Surface>& S,
                                const double                     Tol) const;

  Standard_EXPORT void MakeFace(TopoDS_Face&                     F,
                                const occ::handle<Geom_Surface>& S,
                                const TopLoc_Location&           L,
                                const double                     Tol) const;

  Standard_EXPORT void MakeFace(TopoDS_Face&                           theFace,
                                const occ::handle<Poly_Triangulation>& theTriangulation) const;

  Standard_EXPORT void MakeFace(
    TopoDS_Face&                                             theFace,
    const NCollection_List<occ::handle<Poly_Triangulation>>& theTriangulations,
    const occ::handle<Poly_Triangulation>&                   theActiveTriangulation =
      occ::handle<Poly_Triangulation>()) const;

  Standard_EXPORT void UpdateFace(const TopoDS_Face&               F,
                                  const occ::handle<Geom_Surface>& S,
                                  const TopLoc_Location&           L,
                                  const double                     Tol) const;

  Standard_EXPORT void UpdateFace(const TopoDS_Face&                     theFace,
                                  const occ::handle<Poly_Triangulation>& theTriangulation,
                                  const bool                             theToReset = true) const;

  Standard_EXPORT void UpdateFace(const TopoDS_Face& F, const double Tol) const;

  Standard_EXPORT void NaturalRestriction(const TopoDS_Face& F, const bool N) const;

  Standard_EXPORT void MakeEdge(TopoDS_Edge& E) const;

  void MakeEdge(TopoDS_Edge& E, const occ::handle<Geom_Curve>& C, const double Tol) const;

  void MakeEdge(TopoDS_Edge&                   E,
                const occ::handle<Geom_Curve>& C,
                const TopLoc_Location&         L,
                const double                   Tol) const;

  void MakeEdge(TopoDS_Edge& E, const occ::handle<Poly_Polygon3D>& P) const;

  void MakeEdge(TopoDS_Edge&                                    E,
                const occ::handle<Poly_PolygonOnTriangulation>& N,
                const occ::handle<Poly_Triangulation>&          T) const;

  void MakeEdge(TopoDS_Edge&                                    E,
                const occ::handle<Poly_PolygonOnTriangulation>& N,
                const occ::handle<Poly_Triangulation>&          T,
                const TopLoc_Location&                          L) const;

  void UpdateEdge(const TopoDS_Edge& E, const occ::handle<Geom_Curve>& C, const double Tol) const;

  Standard_EXPORT void UpdateEdge(const TopoDS_Edge&             E,
                                  const occ::handle<Geom_Curve>& C,
                                  const TopLoc_Location&         L,
                                  const double                   Tol) const;

  void UpdateEdge(const TopoDS_Edge&               E,
                  const occ::handle<Geom2d_Curve>& C,
                  const TopoDS_Face&               F,
                  const double                     Tol) const;

  void UpdateEdge(const TopoDS_Edge&               E,
                  const occ::handle<Geom2d_Curve>& C1,
                  const occ::handle<Geom2d_Curve>& C2,
                  const TopoDS_Face&               F,
                  const double                     Tol) const;

  Standard_EXPORT void UpdateEdge(const TopoDS_Edge&               E,
                                  const occ::handle<Geom2d_Curve>& C,
                                  const occ::handle<Geom_Surface>& S,
                                  const TopLoc_Location&           L,
                                  const double                     Tol) const;

  Standard_EXPORT void UpdateEdge(const TopoDS_Edge&               E,
                                  const occ::handle<Geom2d_Curve>& C,
                                  const occ::handle<Geom_Surface>& S,
                                  const TopLoc_Location&           L,
                                  const double                     Tol,
                                  const gp_Pnt2d&                  Pf,
                                  const gp_Pnt2d&                  Pl) const;

  Standard_EXPORT void UpdateEdge(const TopoDS_Edge&               E,
                                  const occ::handle<Geom2d_Curve>& C1,
                                  const occ::handle<Geom2d_Curve>& C2,
                                  const occ::handle<Geom_Surface>& S,
                                  const TopLoc_Location&           L,
                                  const double                     Tol) const;

  Standard_EXPORT void UpdateEdge(const TopoDS_Edge&               E,
                                  const occ::handle<Geom2d_Curve>& C1,
                                  const occ::handle<Geom2d_Curve>& C2,
                                  const occ::handle<Geom_Surface>& S,
                                  const TopLoc_Location&           L,
                                  const double                     Tol,
                                  const gp_Pnt2d&                  Pf,
                                  const gp_Pnt2d&                  Pl) const;

  void UpdateEdge(const TopoDS_Edge& E, const occ::handle<Poly_Polygon3D>& P) const;

  Standard_EXPORT void UpdateEdge(const TopoDS_Edge&                 E,
                                  const occ::handle<Poly_Polygon3D>& P,
                                  const TopLoc_Location&             L) const;

  void UpdateEdge(const TopoDS_Edge&                              E,
                  const occ::handle<Poly_PolygonOnTriangulation>& N,
                  const occ::handle<Poly_Triangulation>&          T) const;

  Standard_EXPORT void UpdateEdge(const TopoDS_Edge&                              E,
                                  const occ::handle<Poly_PolygonOnTriangulation>& N,
                                  const occ::handle<Poly_Triangulation>&          T,
                                  const TopLoc_Location&                          L) const;

  void UpdateEdge(const TopoDS_Edge&                              E,
                  const occ::handle<Poly_PolygonOnTriangulation>& N1,
                  const occ::handle<Poly_PolygonOnTriangulation>& N2,
                  const occ::handle<Poly_Triangulation>&          T) const;

  Standard_EXPORT void UpdateEdge(const TopoDS_Edge&                              E,
                                  const occ::handle<Poly_PolygonOnTriangulation>& N1,
                                  const occ::handle<Poly_PolygonOnTriangulation>& N2,
                                  const occ::handle<Poly_Triangulation>&          T,
                                  const TopLoc_Location&                          L) const;

  Standard_EXPORT void UpdateEdge(const TopoDS_Edge&                 E,
                                  const occ::handle<Poly_Polygon2D>& P,
                                  const TopoDS_Face&                 S) const;

  Standard_EXPORT void UpdateEdge(const TopoDS_Edge&                 E,
                                  const occ::handle<Poly_Polygon2D>& P,
                                  const occ::handle<Geom_Surface>&   S,
                                  const TopLoc_Location&             T) const;

  Standard_EXPORT void UpdateEdge(const TopoDS_Edge&                 E,
                                  const occ::handle<Poly_Polygon2D>& P1,
                                  const occ::handle<Poly_Polygon2D>& P2,
                                  const TopoDS_Face&                 S) const;

  Standard_EXPORT void UpdateEdge(const TopoDS_Edge&                 E,
                                  const occ::handle<Poly_Polygon2D>& P1,
                                  const occ::handle<Poly_Polygon2D>& P2,
                                  const occ::handle<Geom_Surface>&   S,
                                  const TopLoc_Location&             L) const;

  Standard_EXPORT void UpdateEdge(const TopoDS_Edge& E, const double Tol) const;

  Standard_EXPORT void Continuity(const TopoDS_Edge&  E,
                                  const TopoDS_Face&  F1,
                                  const TopoDS_Face&  F2,
                                  const GeomAbs_Shape C) const;

  Standard_EXPORT void Continuity(const TopoDS_Edge&               E,
                                  const occ::handle<Geom_Surface>& S1,
                                  const occ::handle<Geom_Surface>& S2,
                                  const TopLoc_Location&           L1,
                                  const TopLoc_Location&           L2,
                                  const GeomAbs_Shape              C) const;

  Standard_EXPORT void SameParameter(const TopoDS_Edge& E, const bool S) const;

  Standard_EXPORT void SameRange(const TopoDS_Edge& E, const bool S) const;

  Standard_EXPORT void Degenerated(const TopoDS_Edge& E, const bool D) const;

  Standard_EXPORT void Range(const TopoDS_Edge& E,
                             const double       First,
                             const double       Last,
                             const bool         Only3d = false) const;

  Standard_EXPORT void Range(const TopoDS_Edge&               E,
                             const occ::handle<Geom_Surface>& S,
                             const TopLoc_Location&           L,
                             const double                     First,
                             const double                     Last) const;

  void Range(const TopoDS_Edge& E,
             const TopoDS_Face& F,
             const double       First,
             const double       Last) const;

  Standard_EXPORT void Transfert(const TopoDS_Edge& Ein, const TopoDS_Edge& Eout) const;

  void MakeVertex(TopoDS_Vertex& V) const;

  void MakeVertex(TopoDS_Vertex& V, const gp_Pnt& P, const double Tol) const;

  Standard_EXPORT void UpdateVertex(const TopoDS_Vertex& V,
                                    const gp_Pnt&        P,
                                    const double         Tol) const;

  Standard_EXPORT void UpdateVertex(const TopoDS_Vertex& V,
                                    const double         P,
                                    const TopoDS_Edge&   E,
                                    const double         Tol) const;

  void UpdateVertex(const TopoDS_Vertex& V,
                    const double         P,
                    const TopoDS_Edge&   E,
                    const TopoDS_Face&   F,
                    const double         Tol) const;

  Standard_EXPORT void UpdateVertex(const TopoDS_Vertex&             V,
                                    const double                     P,
                                    const TopoDS_Edge&               E,
                                    const occ::handle<Geom_Surface>& S,
                                    const TopLoc_Location&           L,
                                    const double                     Tol) const;

  Standard_EXPORT void UpdateVertex(const TopoDS_Vertex& Ve,
                                    const double         U,
                                    const double         V,
                                    const TopoDS_Face&   F,
                                    const double         Tol) const;

  Standard_EXPORT void UpdateVertex(const TopoDS_Vertex& V, const double Tol) const;

  Standard_EXPORT void Transfert(const TopoDS_Edge&   Ein,
                                 const TopoDS_Edge&   Eout,
                                 const TopoDS_Vertex& Vin,
                                 const TopoDS_Vertex& Vout) const;
};

#include <TopoDS_Face.hpp>
#include <TopoDS_Vertex.hpp>
#include <BRep_TFace.hpp>
#include <BRep_TVertex.hpp>
#include <BRep_Tool.hpp>

inline void BRep_Builder::MakeFace(TopoDS_Face& F) const
{
  occ::handle<BRep_TFace> TF = new BRep_TFace();
  MakeShape(F, TF);
}

inline void BRep_Builder::MakeEdge(TopoDS_Edge&                   E,
                                   const occ::handle<Geom_Curve>& C,
                                   const double                   Tol) const
{
  MakeEdge(E);
  UpdateEdge(E, C, TopLoc_Location(), Tol);
}

inline void BRep_Builder::MakeEdge(TopoDS_Edge& E, const occ::handle<Poly_Polygon3D>& P) const
{
  MakeEdge(E);
  UpdateEdge(E, P);
}

inline void BRep_Builder::MakeEdge(TopoDS_Edge&                                    E,
                                   const occ::handle<Poly_PolygonOnTriangulation>& P,
                                   const occ::handle<Poly_Triangulation>&          T) const
{
  MakeEdge(E);
  UpdateEdge(E, P, T, TopLoc_Location());
}

inline void BRep_Builder::MakeEdge(TopoDS_Edge&                                    E,
                                   const occ::handle<Poly_PolygonOnTriangulation>& P,
                                   const occ::handle<Poly_Triangulation>&          T,
                                   const TopLoc_Location&                          L) const
{
  MakeEdge(E);
  UpdateEdge(E, P, T, L);
}

inline void BRep_Builder::MakeEdge(TopoDS_Edge&                   E,
                                   const occ::handle<Geom_Curve>& C,
                                   const TopLoc_Location&         L,
                                   const double                   Tol) const
{
  MakeEdge(E);
  UpdateEdge(E, C, L, Tol);
}

inline void BRep_Builder::UpdateEdge(const TopoDS_Edge&             E,
                                     const occ::handle<Geom_Curve>& C,
                                     const double                   Tol) const
{
  UpdateEdge(E, C, TopLoc_Location(), Tol);
}

inline void BRep_Builder::UpdateEdge(const TopoDS_Edge&               E,
                                     const occ::handle<Geom2d_Curve>& C,
                                     const TopoDS_Face&               F,
                                     const double                     Tol) const
{
  TopLoc_Location l;
  UpdateEdge(E, C, BRep_Tool::Surface(F, l), l, Tol);
}

inline void BRep_Builder::UpdateEdge(const TopoDS_Edge&               E,
                                     const occ::handle<Geom2d_Curve>& C1,
                                     const occ::handle<Geom2d_Curve>& C2,
                                     const TopoDS_Face&               F,
                                     const double                     Tol) const
{
  TopLoc_Location l;
  UpdateEdge(E, C1, C2, BRep_Tool::Surface(F, l), l, Tol);
}

inline void BRep_Builder::UpdateEdge(const TopoDS_Edge&                 E,
                                     const occ::handle<Poly_Polygon3D>& P) const
{
  UpdateEdge(E, P, TopLoc_Location());
}

inline void BRep_Builder::UpdateEdge(const TopoDS_Edge&                              E,
                                     const occ::handle<Poly_PolygonOnTriangulation>& P,
                                     const occ::handle<Poly_Triangulation>&          T) const
{
  UpdateEdge(E, P, T, TopLoc_Location());
}

inline void BRep_Builder::UpdateEdge(const TopoDS_Edge&                              E,
                                     const occ::handle<Poly_PolygonOnTriangulation>& P1,
                                     const occ::handle<Poly_PolygonOnTriangulation>& P2,
                                     const occ::handle<Poly_Triangulation>&          T) const
{
  UpdateEdge(E, P1, P2, T, TopLoc_Location());
}

inline void BRep_Builder::Range(const TopoDS_Edge& E,
                                const TopoDS_Face& F,
                                const double       First,
                                const double       Last) const
{
  TopLoc_Location l;
  Range(E, BRep_Tool::Surface(F, l), l, First, Last);
}

inline void BRep_Builder::MakeVertex(TopoDS_Vertex& V) const
{
  occ::handle<BRep_TVertex> TV = new BRep_TVertex();
  MakeShape(V, TV);
}

inline void BRep_Builder::MakeVertex(TopoDS_Vertex& V, const gp_Pnt& P, const double Tol) const
{
  MakeVertex(V);
  UpdateVertex(V, P, Tol);
}

inline void BRep_Builder::UpdateVertex(const TopoDS_Vertex& V,
                                       const double         Par,
                                       const TopoDS_Edge&   E,
                                       const TopoDS_Face&   F,
                                       const double         Tol) const
{
  TopLoc_Location l;
  UpdateVertex(V, Par, E, BRep_Tool::Surface(F, l), l, Tol);
}
