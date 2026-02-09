#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <ShapeExtend_Status.hpp>
class TopoDS_Edge;
class Geom_Curve;
class TopoDS_Face;
class Geom_Surface;
class TopLoc_Location;
class Geom2d_Curve;
class gp_Pnt2d;
class TopoDS_Vertex;
class gp_Vec2d;
class gp_Pnt;

#ifdef Status
  #undef Status
#endif

class ShapeAnalysis_Edge
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ShapeAnalysis_Edge();

  Standard_EXPORT bool HasCurve3d(const TopoDS_Edge& edge) const;

  Standard_EXPORT bool Curve3d(const TopoDS_Edge&       edge,
                               occ::handle<Geom_Curve>& C3d,
                               double&                  cf,
                               double&                  cl,
                               const bool               orient = true) const;

  Standard_EXPORT bool IsClosed3d(const TopoDS_Edge& edge) const;

  Standard_EXPORT bool HasPCurve(const TopoDS_Edge& edge, const TopoDS_Face& face) const;

  Standard_EXPORT bool HasPCurve(const TopoDS_Edge&               edge,
                                 const occ::handle<Geom_Surface>& surface,
                                 const TopLoc_Location&           location) const;

  Standard_EXPORT bool PCurve(const TopoDS_Edge&         edge,
                              const TopoDS_Face&         face,
                              occ::handle<Geom2d_Curve>& C2d,
                              double&                    cf,
                              double&                    cl,
                              const bool                 orient = true) const;

  Standard_EXPORT bool PCurve(const TopoDS_Edge&               edge,
                              const occ::handle<Geom_Surface>& surface,
                              const TopLoc_Location&           location,
                              occ::handle<Geom2d_Curve>&       C2d,
                              double&                          cf,
                              double&                          cl,
                              const bool                       orient = true) const;

  Standard_EXPORT bool BoundUV(const TopoDS_Edge& edge,
                               const TopoDS_Face& face,
                               gp_Pnt2d&          first,
                               gp_Pnt2d&          last) const;

  Standard_EXPORT bool BoundUV(const TopoDS_Edge&               edge,
                               const occ::handle<Geom_Surface>& surface,
                               const TopLoc_Location&           location,
                               gp_Pnt2d&                        first,
                               gp_Pnt2d&                        last) const;

  Standard_EXPORT bool IsSeam(const TopoDS_Edge& edge, const TopoDS_Face& face) const;

  Standard_EXPORT bool IsSeam(const TopoDS_Edge&               edge,
                              const occ::handle<Geom_Surface>& surface,
                              const TopLoc_Location&           location) const;

  Standard_EXPORT TopoDS_Vertex FirstVertex(const TopoDS_Edge& edge) const;

  Standard_EXPORT TopoDS_Vertex LastVertex(const TopoDS_Edge& edge) const;

  Standard_EXPORT bool GetEndTangent2d(const TopoDS_Edge& edge,
                                       const TopoDS_Face& face,
                                       const bool         atEnd,
                                       gp_Pnt2d&          pos,
                                       gp_Vec2d&          tang,
                                       const double       dparam = 0.0) const;

  Standard_EXPORT bool GetEndTangent2d(const TopoDS_Edge&               edge,
                                       const occ::handle<Geom_Surface>& surface,
                                       const TopLoc_Location&           location,
                                       const bool                       atEnd,
                                       gp_Pnt2d&                        pos,
                                       gp_Vec2d&                        tang,
                                       const double                     dparam = 0.0) const;

  Standard_EXPORT bool CheckVerticesWithCurve3d(const TopoDS_Edge& edge,
                                                const double       preci = -1,
                                                const int          vtx   = 0);

  Standard_EXPORT bool CheckVerticesWithPCurve(const TopoDS_Edge& edge,
                                               const TopoDS_Face& face,
                                               const double       preci = -1,
                                               const int          vtx   = 0);

  Standard_EXPORT bool CheckVerticesWithPCurve(const TopoDS_Edge&               edge,
                                               const occ::handle<Geom_Surface>& surface,
                                               const TopLoc_Location&           location,
                                               const double                     preci = -1,
                                               const int                        vtx   = 0);

  Standard_EXPORT bool CheckVertexTolerance(const TopoDS_Edge& edge,
                                            const TopoDS_Face& face,
                                            double&            toler1,
                                            double&            toler2);

  Standard_EXPORT bool CheckVertexTolerance(const TopoDS_Edge& edge,
                                            double&            toler1,
                                            double&            toler2);

  Standard_EXPORT bool CheckCurve3dWithPCurve(const TopoDS_Edge& edge, const TopoDS_Face& face);

  Standard_EXPORT bool CheckCurve3dWithPCurve(const TopoDS_Edge&               edge,
                                              const occ::handle<Geom_Surface>& surface,
                                              const TopLoc_Location&           location);

  Standard_EXPORT bool Status(const ShapeExtend_Status status) const;

  Standard_EXPORT bool CheckSameParameter(const TopoDS_Edge& edge,
                                          double&            maxdev,
                                          const int          NbControl = 23);

  Standard_EXPORT bool CheckSameParameter(const TopoDS_Edge& theEdge,
                                          const TopoDS_Face& theFace,
                                          double&            theMaxdev,
                                          const int          theNbControl = 23);

  Standard_EXPORT bool CheckPCurveRange(const double                     theFirst,
                                        const double                     theLast,
                                        const occ::handle<Geom2d_Curve>& thePC);

  Standard_EXPORT bool CheckOverlapping(const TopoDS_Edge& theEdge1,
                                        const TopoDS_Edge& theEdge2,
                                        double&            theTolOverlap,
                                        const double       theDomainDist = 0.0);

protected:
  int myStatus;

private:
  Standard_EXPORT bool CheckPoints(const gp_Pnt& P1A,
                                   const gp_Pnt& P1B,
                                   const gp_Pnt& P2A,
                                   const gp_Pnt& P2B,
                                   const double  preci1,
                                   const double  preci2);
};
