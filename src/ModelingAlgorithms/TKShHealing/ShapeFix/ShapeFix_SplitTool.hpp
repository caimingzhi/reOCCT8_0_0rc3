#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>
class TopoDS_Edge;
class TopoDS_Vertex;
class TopoDS_Face;
class ShapeBuild_ReShape;

class ShapeFix_SplitTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ShapeFix_SplitTool();

  Standard_EXPORT bool SplitEdge(const TopoDS_Edge&   edge,
                                 const double         param,
                                 const TopoDS_Vertex& vert,
                                 const TopoDS_Face&   face,
                                 TopoDS_Edge&         newE1,
                                 TopoDS_Edge&         newE2,
                                 const double         tol3d,
                                 const double         tol2d) const;

  Standard_EXPORT bool SplitEdge(const TopoDS_Edge&   edge,
                                 const double         param1,
                                 const double         param2,
                                 const TopoDS_Vertex& vert,
                                 const TopoDS_Face&   face,
                                 TopoDS_Edge&         newE1,
                                 TopoDS_Edge&         newE2,
                                 const double         tol3d,
                                 const double         tol2d) const;

  Standard_EXPORT bool CutEdge(const TopoDS_Edge& edge,
                               const double       pend,
                               const double       cut,
                               const TopoDS_Face& face,
                               bool&              iscutline) const;

  Standard_EXPORT bool SplitEdge(const TopoDS_Edge&                     edge,
                                 const double                           fp,
                                 const TopoDS_Vertex&                   V1,
                                 const double                           lp,
                                 const TopoDS_Vertex&                   V2,
                                 const TopoDS_Face&                     face,
                                 NCollection_Sequence<TopoDS_Shape>&    SeqE,
                                 int&                                   aNum,
                                 const occ::handle<ShapeBuild_ReShape>& context,
                                 const double                           tol3d,
                                 const double                           tol2d) const;
};
