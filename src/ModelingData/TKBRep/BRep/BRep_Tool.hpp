#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomAbs_Shape.hpp>
#include <Geom_Surface.hpp>
#include <Geom_Curve.hpp>
#include <Geom2d_Curve.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Pnt.hpp>
#include <Poly_Triangulation.hpp>
#include <Poly_Polygon3D.hpp>
#include <Poly_Polygon2D.hpp>
#include <Poly_PolygonOnTriangulation.hpp>
#include <TopAbs_ShapeEnum.hpp>

class TopoDS_Shape;
class TopoDS_Face;
class TopLoc_Location;
class TopoDS_Edge;
class TopoDS_Vertex;

class BRep_Tool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static bool IsClosed(const TopoDS_Shape& S);

  Standard_EXPORT static const occ::handle<Geom_Surface>& Surface(const TopoDS_Face& F,
                                                                  TopLoc_Location&   L);

  Standard_EXPORT static occ::handle<Geom_Surface> Surface(const TopoDS_Face& F);

  Standard_EXPORT static const occ::handle<Poly_Triangulation>& Triangulation(
    const TopoDS_Face&     theFace,
    TopLoc_Location&       theLocation,
    const Poly_MeshPurpose theMeshPurpose = Poly_MeshPurpose_NONE);

  Standard_EXPORT static const NCollection_List<occ::handle<Poly_Triangulation>>& Triangulations(
    const TopoDS_Face& theFace,
    TopLoc_Location&   theLocation);

  Standard_EXPORT static double Tolerance(const TopoDS_Face& F);

  Standard_EXPORT static bool NaturalRestriction(const TopoDS_Face& F);

  Standard_EXPORT static bool IsGeometric(const TopoDS_Face& F);

  Standard_EXPORT static bool IsGeometric(const TopoDS_Edge& E);

  Standard_EXPORT static const occ::handle<Geom_Curve>& Curve(const TopoDS_Edge& E,
                                                              TopLoc_Location&   L,
                                                              double&            First,
                                                              double&            Last);

  Standard_EXPORT static occ::handle<Geom_Curve> Curve(const TopoDS_Edge& E,
                                                       double&            First,
                                                       double&            Last);

  Standard_EXPORT static const occ::handle<Poly_Polygon3D>& Polygon3D(const TopoDS_Edge& E,
                                                                      TopLoc_Location&   L);

  Standard_EXPORT static occ::handle<Geom2d_Curve> CurveOnSurface(const TopoDS_Edge& E,
                                                                  const TopoDS_Face& F,
                                                                  double&            First,
                                                                  double&            Last,
                                                                  bool* theIsStored = nullptr);

  Standard_EXPORT static occ::handle<Geom2d_Curve> CurveOnSurface(
    const TopoDS_Edge&               E,
    const occ::handle<Geom_Surface>& S,
    const TopLoc_Location&           L,
    double&                          First,
    double&                          Last,
    bool*                            theIsStored = nullptr);

  Standard_EXPORT static occ::handle<Geom2d_Curve> CurveOnPlane(const TopoDS_Edge&               E,
                                                                const occ::handle<Geom_Surface>& S,
                                                                const TopLoc_Location&           L,
                                                                double& First,
                                                                double& Last);

  Standard_EXPORT static void CurveOnSurface(const TopoDS_Edge&         E,
                                             occ::handle<Geom2d_Curve>& C,
                                             occ::handle<Geom_Surface>& S,
                                             TopLoc_Location&           L,
                                             double&                    First,
                                             double&                    Last);

  Standard_EXPORT static void CurveOnSurface(const TopoDS_Edge&         E,
                                             occ::handle<Geom2d_Curve>& C,
                                             occ::handle<Geom_Surface>& S,
                                             TopLoc_Location&           L,
                                             double&                    First,
                                             double&                    Last,
                                             const int                  Index);

  Standard_EXPORT static occ::handle<Poly_Polygon2D> PolygonOnSurface(const TopoDS_Edge& E,
                                                                      const TopoDS_Face& F);

  Standard_EXPORT static occ::handle<Poly_Polygon2D> PolygonOnSurface(
    const TopoDS_Edge&               E,
    const occ::handle<Geom_Surface>& S,
    const TopLoc_Location&           L);

  Standard_EXPORT static void PolygonOnSurface(const TopoDS_Edge&           E,
                                               occ::handle<Poly_Polygon2D>& C,
                                               occ::handle<Geom_Surface>&   S,
                                               TopLoc_Location&             L);

  Standard_EXPORT static void PolygonOnSurface(const TopoDS_Edge&           E,
                                               occ::handle<Poly_Polygon2D>& C,
                                               occ::handle<Geom_Surface>&   S,
                                               TopLoc_Location&             L,
                                               const int                    Index);

  Standard_EXPORT static const occ::handle<Poly_PolygonOnTriangulation>& PolygonOnTriangulation(
    const TopoDS_Edge&                     E,
    const occ::handle<Poly_Triangulation>& T,
    const TopLoc_Location&                 L);

  Standard_EXPORT static void PolygonOnTriangulation(const TopoDS_Edge&                        E,
                                                     occ::handle<Poly_PolygonOnTriangulation>& P,
                                                     occ::handle<Poly_Triangulation>&          T,
                                                     TopLoc_Location&                          L);

  Standard_EXPORT static void PolygonOnTriangulation(const TopoDS_Edge&                        E,
                                                     occ::handle<Poly_PolygonOnTriangulation>& P,
                                                     occ::handle<Poly_Triangulation>&          T,
                                                     TopLoc_Location&                          L,
                                                     const int Index);

  Standard_EXPORT static bool IsClosed(const TopoDS_Edge& E, const TopoDS_Face& F);

  Standard_EXPORT static bool IsClosed(const TopoDS_Edge&               E,
                                       const occ::handle<Geom_Surface>& S,
                                       const TopLoc_Location&           L);

  Standard_EXPORT static bool IsClosed(const TopoDS_Edge&                     E,
                                       const occ::handle<Poly_Triangulation>& T,
                                       const TopLoc_Location&                 L);

  Standard_EXPORT static double Tolerance(const TopoDS_Edge& E);

  Standard_EXPORT static bool SameParameter(const TopoDS_Edge& E);

  Standard_EXPORT static bool SameRange(const TopoDS_Edge& E);

  Standard_EXPORT static bool Degenerated(const TopoDS_Edge& E);

  Standard_EXPORT static void Range(const TopoDS_Edge& E, double& First, double& Last);

  Standard_EXPORT static void Range(const TopoDS_Edge&               E,
                                    const occ::handle<Geom_Surface>& S,
                                    const TopLoc_Location&           L,
                                    double&                          First,
                                    double&                          Last);

  Standard_EXPORT static void Range(const TopoDS_Edge& E,
                                    const TopoDS_Face& F,
                                    double&            First,
                                    double&            Last);

  Standard_EXPORT static void UVPoints(const TopoDS_Edge&               E,
                                       const occ::handle<Geom_Surface>& S,
                                       const TopLoc_Location&           L,
                                       gp_Pnt2d&                        PFirst,
                                       gp_Pnt2d&                        PLast);

  Standard_EXPORT static void UVPoints(const TopoDS_Edge& E,
                                       const TopoDS_Face& F,
                                       gp_Pnt2d&          PFirst,
                                       gp_Pnt2d&          PLast);

  Standard_EXPORT static void SetUVPoints(const TopoDS_Edge&               E,
                                          const occ::handle<Geom_Surface>& S,
                                          const TopLoc_Location&           L,
                                          const gp_Pnt2d&                  PFirst,
                                          const gp_Pnt2d&                  PLast);

  Standard_EXPORT static void SetUVPoints(const TopoDS_Edge& E,
                                          const TopoDS_Face& F,
                                          const gp_Pnt2d&    PFirst,
                                          const gp_Pnt2d&    PLast);

  Standard_EXPORT static bool HasContinuity(const TopoDS_Edge& E,
                                            const TopoDS_Face& F1,
                                            const TopoDS_Face& F2);

  Standard_EXPORT static GeomAbs_Shape Continuity(const TopoDS_Edge& E,
                                                  const TopoDS_Face& F1,
                                                  const TopoDS_Face& F2);

  Standard_EXPORT static bool HasContinuity(const TopoDS_Edge&               E,
                                            const occ::handle<Geom_Surface>& S1,
                                            const occ::handle<Geom_Surface>& S2,
                                            const TopLoc_Location&           L1,
                                            const TopLoc_Location&           L2);

  Standard_EXPORT static GeomAbs_Shape Continuity(const TopoDS_Edge&               E,
                                                  const occ::handle<Geom_Surface>& S1,
                                                  const occ::handle<Geom_Surface>& S2,
                                                  const TopLoc_Location&           L1,
                                                  const TopLoc_Location&           L2);

  Standard_EXPORT static bool HasContinuity(const TopoDS_Edge& E);

  Standard_EXPORT static GeomAbs_Shape MaxContinuity(const TopoDS_Edge& theEdge);

  Standard_EXPORT static gp_Pnt Pnt(const TopoDS_Vertex& V);

  Standard_EXPORT static double Tolerance(const TopoDS_Vertex& V);

  Standard_EXPORT static bool Parameter(const TopoDS_Vertex& theV,
                                        const TopoDS_Edge&   theE,
                                        double&              theParam);

  Standard_EXPORT static double Parameter(const TopoDS_Vertex& V, const TopoDS_Edge& E);

  Standard_EXPORT static double Parameter(const TopoDS_Vertex& V,
                                          const TopoDS_Edge&   E,
                                          const TopoDS_Face&   F);

  Standard_EXPORT static double Parameter(const TopoDS_Vertex&             V,
                                          const TopoDS_Edge&               E,
                                          const occ::handle<Geom_Surface>& S,
                                          const TopLoc_Location&           L);

  Standard_EXPORT static gp_Pnt2d Parameters(const TopoDS_Vertex& V, const TopoDS_Face& F);

  Standard_EXPORT static double MaxTolerance(const TopoDS_Shape&    theShape,
                                             const TopAbs_ShapeEnum theSubShape);
};
