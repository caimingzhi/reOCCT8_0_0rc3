#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <TopoDS_Shape.hpp>
#include <Bnd_Box2d.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
class ShapeBuild_ReShape;
class TopoDS_Edge;
class TopoDS_Vertex;
class TopoDS_Face;
class ShapeExtend_WireData;
class Bnd_Box2d;
class Geom2d_Curve;

class ShapeFix_IntersectionTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ShapeFix_IntersectionTool(const occ::handle<ShapeBuild_ReShape>& context,
                                            const double                           preci,
                                            const double                           maxtol = 1.0);

  occ::handle<ShapeBuild_ReShape> Context() const;

  Standard_EXPORT bool SplitEdge(const TopoDS_Edge&   edge,
                                 const double         param,
                                 const TopoDS_Vertex& vert,
                                 const TopoDS_Face&   face,
                                 TopoDS_Edge&         newE1,
                                 TopoDS_Edge&         newE2,
                                 const double         preci) const;

  Standard_EXPORT bool CutEdge(const TopoDS_Edge& edge,
                               const double       pend,
                               const double       cut,
                               const TopoDS_Face& face,
                               bool&              iscutline) const;

  Standard_EXPORT bool FixSelfIntersectWire(occ::handle<ShapeExtend_WireData>& sewd,
                                            const TopoDS_Face&                 face,
                                            int&                               NbSplit,
                                            int&                               NbCut,
                                            int&                               NbRemoved) const;

  Standard_EXPORT bool FixIntersectingWires(TopoDS_Face& face) const;

private:
  Standard_EXPORT bool SplitEdge1(
    const occ::handle<ShapeExtend_WireData>&                               sewd,
    const TopoDS_Face&                                                     face,
    const int                                                              num,
    const double                                                           param,
    const TopoDS_Vertex&                                                   vert,
    const double                                                           preci,
    NCollection_DataMap<TopoDS_Shape, Bnd_Box2d, TopTools_ShapeMapHasher>& boxes) const;

  Standard_EXPORT bool SplitEdge2(
    const occ::handle<ShapeExtend_WireData>&                               sewd,
    const TopoDS_Face&                                                     face,
    const int                                                              num,
    const double                                                           param1,
    const double                                                           param2,
    const TopoDS_Vertex&                                                   vert,
    const double                                                           preci,
    NCollection_DataMap<TopoDS_Shape, Bnd_Box2d, TopTools_ShapeMapHasher>& boxes) const;

  Standard_EXPORT bool UnionVertexes(
    const occ::handle<ShapeExtend_WireData>&                               sewd,
    TopoDS_Edge&                                                           edge1,
    TopoDS_Edge&                                                           edge2,
    const int                                                              num2,
    NCollection_DataMap<TopoDS_Shape, Bnd_Box2d, TopTools_ShapeMapHasher>& boxes,
    const Bnd_Box2d&                                                       B2) const;

  Standard_EXPORT bool FindVertAndSplitEdge(
    const double                                                           param1,
    const TopoDS_Edge&                                                     edge1,
    const TopoDS_Edge&                                                     edge2,
    const occ::handle<Geom2d_Curve>&                                       Crv1,
    double&                                                                MaxTolVert,
    int&                                                                   num1,
    const occ::handle<ShapeExtend_WireData>&                               sewd,
    const TopoDS_Face&                                                     face,
    NCollection_DataMap<TopoDS_Shape, Bnd_Box2d, TopTools_ShapeMapHasher>& boxes,
    const bool                                                             aTmpKey) const;

  occ::handle<ShapeBuild_ReShape> myContext;
  double                          myPreci;
  double                          myMaxTol;
};

inline occ::handle<ShapeBuild_ReShape> ShapeFix_IntersectionTool::Context() const
{
  return myContext;
}
