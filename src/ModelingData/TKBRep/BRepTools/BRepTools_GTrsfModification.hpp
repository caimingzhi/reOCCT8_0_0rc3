#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_GTrsf.hpp>
#include <BRepTools_Modification.hpp>
#include <GeomAbs_Shape.hpp>
class TopoDS_Face;
class Geom_Surface;
class TopLoc_Location;
class TopoDS_Edge;
class Geom_Curve;
class TopoDS_Vertex;
class gp_Pnt;
class Geom2d_Curve;

class BRepTools_GTrsfModification : public BRepTools_Modification
{

public:
  Standard_EXPORT BRepTools_GTrsfModification(const gp_GTrsf& T);

  Standard_EXPORT gp_GTrsf& GTrsf();

  Standard_EXPORT bool NewSurface(const TopoDS_Face&         F,
                                  occ::handle<Geom_Surface>& S,
                                  TopLoc_Location&           L,
                                  double&                    Tol,
                                  bool&                      RevWires,
                                  bool&                      RevFace) override;

  Standard_EXPORT bool NewCurve(const TopoDS_Edge&       E,
                                occ::handle<Geom_Curve>& C,
                                TopLoc_Location&         L,
                                double&                  Tol) override;

  Standard_EXPORT bool NewPoint(const TopoDS_Vertex& V, gp_Pnt& P, double& Tol) override;

  Standard_EXPORT bool NewCurve2d(const TopoDS_Edge&         E,
                                  const TopoDS_Face&         F,
                                  const TopoDS_Edge&         NewE,
                                  const TopoDS_Face&         NewF,
                                  occ::handle<Geom2d_Curve>& C,
                                  double&                    Tol) override;

  Standard_EXPORT bool NewParameter(const TopoDS_Vertex& V,
                                    const TopoDS_Edge&   E,
                                    double&              P,
                                    double&              Tol) override;

  Standard_EXPORT GeomAbs_Shape Continuity(const TopoDS_Edge& E,
                                           const TopoDS_Face& F1,
                                           const TopoDS_Face& F2,
                                           const TopoDS_Edge& NewE,
                                           const TopoDS_Face& NewF1,
                                           const TopoDS_Face& NewF2) override;

  Standard_EXPORT bool NewTriangulation(const TopoDS_Face&               theFace,
                                        occ::handle<Poly_Triangulation>& theTri) override;

  Standard_EXPORT bool NewPolygon(const TopoDS_Edge&           theEdge,
                                  occ::handle<Poly_Polygon3D>& thePoly) override;

  Standard_EXPORT bool NewPolygonOnTriangulation(
    const TopoDS_Edge&                        theEdge,
    const TopoDS_Face&                        theFace,
    occ::handle<Poly_PolygonOnTriangulation>& thePoly) override;

  DEFINE_STANDARD_RTTIEXT(BRepTools_GTrsfModification, BRepTools_Modification)

private:
  gp_GTrsf myGTrsf;
  double   myGScale;
};
