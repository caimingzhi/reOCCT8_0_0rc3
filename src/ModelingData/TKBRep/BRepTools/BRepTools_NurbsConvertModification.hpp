#pragma once

#include <Standard.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <BRepTools_CopyModification.hpp>
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

class BRepTools_NurbsConvertModification : public BRepTools_CopyModification
{

public:
  Standard_EXPORT BRepTools_NurbsConvertModification();

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

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& GetUpdatedEdges() const;

  DEFINE_STANDARD_RTTIEXT(BRepTools_NurbsConvertModification, BRepTools_CopyModification)

private:
  NCollection_List<TopoDS_Shape>                    myled;
  NCollection_List<occ::handle<Standard_Transient>> mylcu;
  NCollection_IndexedDataMap<occ::handle<Standard_Transient>, occ::handle<Standard_Transient>>
                                 myMap;
  NCollection_List<TopoDS_Shape> myUpdatedEdges;
};
