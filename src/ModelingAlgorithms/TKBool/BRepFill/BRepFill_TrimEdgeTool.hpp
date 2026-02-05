#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt2d.hpp>
#include <Bisector_Bisec.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <GeomAbs_JoinType.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Sequence.hpp>
class Geom2d_Curve;
class Geom2d_Geometry;
class TopoDS_Edge;
class TopoDS_Shape;
class TopoDS_Vertex;

//! Geometric Tool using to construct Offset Wires.
class BRepFill_TrimEdgeTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepFill_TrimEdgeTool();

  Standard_EXPORT BRepFill_TrimEdgeTool(const Bisector_Bisec&               Bisec,
                                        const occ::handle<Geom2d_Geometry>& S1,
                                        const occ::handle<Geom2d_Geometry>& S2,
                                        const double                        Offset);

  Standard_EXPORT void IntersectWith(const TopoDS_Edge&            Edge1,
                                     const TopoDS_Edge&            Edge2,
                                     const TopoDS_Shape&           InitShape1,
                                     const TopoDS_Shape&           InitShape2,
                                     const TopoDS_Vertex&          End1,
                                     const TopoDS_Vertex&          End2,
                                     const GeomAbs_JoinType        theJoinType,
                                     const bool                    IsOpenResult,
                                     NCollection_Sequence<gp_Pnt>& Params);

  Standard_EXPORT void AddOrConfuse(const bool                    Start,
                                    const TopoDS_Edge&            Edge1,
                                    const TopoDS_Edge&            Edge2,
                                    NCollection_Sequence<gp_Pnt>& Params) const;

  Standard_EXPORT bool IsInside(const gp_Pnt2d& P) const;

private:
  bool                      isPoint1;
  bool                      isPoint2;
  gp_Pnt2d                  myP1;
  gp_Pnt2d                  myP2;
  occ::handle<Geom2d_Curve> myC1;
  occ::handle<Geom2d_Curve> myC2;
  double                    myOffset;
  Bisector_Bisec            myBisec;
  Geom2dAdaptor_Curve       myBis;
};
