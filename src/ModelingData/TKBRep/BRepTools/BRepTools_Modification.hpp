#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <Standard_Real.hpp>
#include <GeomAbs_Shape.hpp>
class TopoDS_Face;
class Geom_Surface;
class TopLoc_Location;
class TopoDS_Edge;
class Geom_Curve;
class TopoDS_Vertex;
class gp_Pnt;
class Geom2d_Curve;
class Poly_Triangulation;

class Poly_Polygon3D;
class Poly_PolygonOnTriangulation;

class BRepTools_Modification : public Standard_Transient
{

public:
  Standard_EXPORT virtual bool NewSurface(const TopoDS_Face&         F,
                                          occ::handle<Geom_Surface>& S,
                                          TopLoc_Location&           L,
                                          double&                    Tol,
                                          bool&                      RevWires,
                                          bool&                      RevFace) = 0;

  Standard_EXPORT virtual bool NewTriangulation(const TopoDS_Face&               F,
                                                occ::handle<Poly_Triangulation>& T);

  Standard_EXPORT virtual bool NewCurve(const TopoDS_Edge&       E,
                                        occ::handle<Geom_Curve>& C,
                                        TopLoc_Location&         L,
                                        double&                  Tol) = 0;

  Standard_EXPORT virtual bool NewPolygon(const TopoDS_Edge& E, occ::handle<Poly_Polygon3D>& P);

  Standard_EXPORT virtual bool NewPolygonOnTriangulation(
    const TopoDS_Edge&                        E,
    const TopoDS_Face&                        F,
    occ::handle<Poly_PolygonOnTriangulation>& P);

  Standard_EXPORT virtual bool NewPoint(const TopoDS_Vertex& V, gp_Pnt& P, double& Tol) = 0;

  Standard_EXPORT virtual bool NewCurve2d(const TopoDS_Edge&         E,
                                          const TopoDS_Face&         F,
                                          const TopoDS_Edge&         NewE,
                                          const TopoDS_Face&         NewF,
                                          occ::handle<Geom2d_Curve>& C,
                                          double&                    Tol) = 0;

  Standard_EXPORT virtual bool NewParameter(const TopoDS_Vertex& V,
                                            const TopoDS_Edge&   E,
                                            double&              P,
                                            double&              Tol) = 0;

  Standard_EXPORT virtual GeomAbs_Shape Continuity(const TopoDS_Edge& E,
                                                   const TopoDS_Face& F1,
                                                   const TopoDS_Face& F2,
                                                   const TopoDS_Edge& NewE,
                                                   const TopoDS_Face& NewF1,
                                                   const TopoDS_Face& NewF2) = 0;

  DEFINE_STANDARD_RTTIEXT(BRepTools_Modification, Standard_Transient)
};
