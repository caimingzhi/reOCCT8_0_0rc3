#pragma once

#include <Standard_Transient.hpp>
#include <IMeshData_Types.hpp>
#include <Poly_Triangulation.hpp>
#include <Poly_PolygonOnTriangulation.hpp>

class Geom_Curve;
class Geom2d_Curve;
class Poly_Polygon3D;
class TopoDS_Face;
class TopoDS_Edge;
class Bnd_Box;

class BRepMesh_ShapeTool : public Standard_Transient
{
public:
  Standard_EXPORT static double MaxFaceTolerance(const TopoDS_Face& theFace);

  Standard_EXPORT static void BoxMaxDimension(const Bnd_Box& theBox, double& theMaxDimension);

  Standard_EXPORT static void CheckAndUpdateFlags(const IMeshData::IEdgeHandle&   theEdge,
                                                  const IMeshData::IPCurveHandle& thePCurve);

  Standard_EXPORT static void AddInFace(const TopoDS_Face&               theFace,
                                        occ::handle<Poly_Triangulation>& theTriangulation);

  Standard_EXPORT static void NullifyFace(const TopoDS_Face& theFace);

  Standard_EXPORT static void NullifyEdge(const TopoDS_Edge&                     theEdge,
                                          const occ::handle<Poly_Triangulation>& theTriangulation,
                                          const TopLoc_Location&                 theLocation);

  Standard_EXPORT static void NullifyEdge(const TopoDS_Edge&     theEdge,
                                          const TopLoc_Location& theLocation);

  Standard_EXPORT static void UpdateEdge(const TopoDS_Edge&                              theEdge,
                                         const occ::handle<Poly_PolygonOnTriangulation>& thePolygon,
                                         const occ::handle<Poly_Triangulation>& theTriangulation,
                                         const TopLoc_Location&                 theLocation);

  Standard_EXPORT static void UpdateEdge(const TopoDS_Edge&                 theEdge,
                                         const occ::handle<Poly_Polygon3D>& thePolygon);

  Standard_EXPORT static void UpdateEdge(
    const TopoDS_Edge&                              theEdge,
    const occ::handle<Poly_PolygonOnTriangulation>& thePolygon1,
    const occ::handle<Poly_PolygonOnTriangulation>& thePolygon2,
    const occ::handle<Poly_Triangulation>&          theTriangulation,
    const TopLoc_Location&                          theLocation);

  Standard_EXPORT static gp_Pnt UseLocation(const gp_Pnt& thePnt, const TopLoc_Location& theLoc);

  Standard_EXPORT static bool UVPoints(const TopoDS_Edge& theEdge,
                                       const TopoDS_Face& theFace,
                                       gp_Pnt2d&          theFirstPoint2d,
                                       gp_Pnt2d&          theLastPoint2d,
                                       const bool         isConsiderOrientation = false);

  Standard_EXPORT static bool Range(const TopoDS_Edge&         theEdge,
                                    const TopoDS_Face&         theFace,
                                    occ::handle<Geom2d_Curve>& thePCurve,
                                    double&                    theFirstParam,
                                    double&                    theLastParam,
                                    const bool                 isConsiderOrientation = false);

  Standard_EXPORT static bool Range(const TopoDS_Edge&       theEdge,
                                    occ::handle<Geom_Curve>& theCurve,
                                    double&                  theFirstParam,
                                    double&                  theLastParam,
                                    const bool               isConsiderOrientation = false);

  DEFINE_STANDARD_RTTIEXT(BRepMesh_ShapeTool, Standard_Transient)
};
