#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Face.hpp>
#include <TopoDS_Edge.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Sequence.hpp>
#include <GeomAbs_Shape.hpp>
class Geom2d_Curve;
class gp_Pnt2d;
class Geom_Curve;

//! Compute the Pcurves and the 3d curves resulting
//! of the trimming of a face by an extruded surface.
class BRepFill_TrimSurfaceTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepFill_TrimSurfaceTool(const occ::handle<Geom2d_Curve>& Bis,
                                           const TopoDS_Face&               Face1,
                                           const TopoDS_Face&               Face2,
                                           const TopoDS_Edge&               Edge1,
                                           const TopoDS_Edge&               Edge2,
                                           const bool                       Inv1,
                                           const bool                       Inv2);

  //! Intersect <Bis> with the projection of the edges
  //! <EdgeOnFi> and returns the intersecting parameters
  //! on Bis and on the edges
  //! P.X() : Parameter on Bis
  //! P.Y() : Parameter on EdgeOnF1
  //! P.Z() : Parameter on EdgeOnF2
  //! raises if <Edge> is not a edge of Face1 or Face2.
  Standard_EXPORT void IntersectWith(const TopoDS_Edge&            EdgeOnF1,
                                     const TopoDS_Edge&            EdgeOnF2,
                                     NCollection_Sequence<gp_Pnt>& Points) const;

  //! returns True if the Line (P, DZ) intersect the Faces
  Standard_EXPORT bool IsOnFace(const gp_Pnt2d& Point) const;

  //! returns the parameter of the point <Point> on the
  //! Edge <Edge>, assuming that the point is on the edge.
  Standard_EXPORT double ProjOn(const gp_Pnt2d& Point, const TopoDS_Edge& Edge) const;

  Standard_EXPORT void Project(const double               U1,
                               const double               U2,
                               occ::handle<Geom_Curve>&   Curve,
                               occ::handle<Geom2d_Curve>& PCurve1,
                               occ::handle<Geom2d_Curve>& PCurve2,
                               GeomAbs_Shape&             myCont) const;

private:
  TopoDS_Face               myFace1;
  TopoDS_Face               myFace2;
  TopoDS_Edge               myEdge1;
  TopoDS_Edge               myEdge2;
  bool                      myInv1;
  bool                      myInv2;
  occ::handle<Geom2d_Curve> myBis;
};
