#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class TopoDS_Edge;
class TopoDS_Vertex;
class TopoDS_Face;
class Geom_Surface;
class TopLoc_Location;
class Geom2d_Curve;
class gp_Trsf2d;
class Geom_Curve;

class ShapeBuild_Edge
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopoDS_Edge CopyReplaceVertices(const TopoDS_Edge&   edge,
                                                  const TopoDS_Vertex& V1,
                                                  const TopoDS_Vertex& V2) const;

  Standard_EXPORT void CopyRanges(const TopoDS_Edge& toedge,
                                  const TopoDS_Edge& fromedge,
                                  const double       alpha = 0,
                                  const double       beta  = 1) const;

  Standard_EXPORT void SetRange3d(const TopoDS_Edge& edge,
                                  const double       first,
                                  const double       last) const;

  Standard_EXPORT void CopyPCurves(const TopoDS_Edge& toedge, const TopoDS_Edge& fromedge) const;

  Standard_EXPORT TopoDS_Edge Copy(const TopoDS_Edge& edge, const bool sharepcurves = true) const;

  Standard_EXPORT void RemovePCurve(const TopoDS_Edge& edge, const TopoDS_Face& face) const;

  Standard_EXPORT void RemovePCurve(const TopoDS_Edge&               edge,
                                    const occ::handle<Geom_Surface>& surf) const;

  Standard_EXPORT void RemovePCurve(const TopoDS_Edge&               edge,
                                    const occ::handle<Geom_Surface>& surf,
                                    const TopLoc_Location&           loc) const;

  Standard_EXPORT void ReplacePCurve(const TopoDS_Edge&               edge,
                                     const occ::handle<Geom2d_Curve>& pcurve,
                                     const TopoDS_Face&               face) const;

  Standard_EXPORT bool ReassignPCurve(const TopoDS_Edge& edge,
                                      const TopoDS_Face& old,
                                      const TopoDS_Face& sub) const;

  Standard_EXPORT occ::handle<Geom2d_Curve> TransformPCurve(const occ::handle<Geom2d_Curve>& pcurve,
                                                            const gp_Trsf2d&                 trans,
                                                            const double                     uFact,
                                                            double&                          aFirst,
                                                            double& aLast) const;

  Standard_EXPORT void RemoveCurve3d(const TopoDS_Edge& edge) const;

  Standard_EXPORT bool BuildCurve3d(const TopoDS_Edge& edge) const;

  Standard_EXPORT void MakeEdge(TopoDS_Edge&                   edge,
                                const occ::handle<Geom_Curve>& curve,
                                const TopLoc_Location&         L) const;

  Standard_EXPORT void MakeEdge(TopoDS_Edge&                   edge,
                                const occ::handle<Geom_Curve>& curve,
                                const TopLoc_Location&         L,
                                const double                   p1,
                                const double                   p2) const;

  Standard_EXPORT void MakeEdge(TopoDS_Edge&                     edge,
                                const occ::handle<Geom2d_Curve>& pcurve,
                                const TopoDS_Face&               face) const;

  Standard_EXPORT void MakeEdge(TopoDS_Edge&                     edge,
                                const occ::handle<Geom2d_Curve>& pcurve,
                                const TopoDS_Face&               face,
                                const double                     p1,
                                const double                     p2) const;

  Standard_EXPORT void MakeEdge(TopoDS_Edge&                     edge,
                                const occ::handle<Geom2d_Curve>& pcurve,
                                const occ::handle<Geom_Surface>& S,
                                const TopLoc_Location&           L) const;

  Standard_EXPORT void MakeEdge(TopoDS_Edge&                     edge,
                                const occ::handle<Geom2d_Curve>& pcurve,
                                const occ::handle<Geom_Surface>& S,
                                const TopLoc_Location&           L,
                                const double                     p1,
                                const double                     p2) const;
};
