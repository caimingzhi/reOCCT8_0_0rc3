#pragma once

#include <BRepTools_Modification.hpp>

class BRepTools_CopyModification : public BRepTools_Modification
{
public:
  Standard_EXPORT explicit BRepTools_CopyModification(const bool theCopyGeom = true,
                                                      const bool theCopyMesh = true);

  Standard_EXPORT bool NewSurface(const TopoDS_Face&         theFace,
                                  occ::handle<Geom_Surface>& theSurf,
                                  TopLoc_Location&           theLoc,
                                  double&                    theTol,
                                  bool&                      theRevWires,
                                  bool&                      theRevFace) override;

  Standard_EXPORT bool NewCurve(const TopoDS_Edge&       theEdge,
                                occ::handle<Geom_Curve>& theCurve,
                                TopLoc_Location&         theLoc,
                                double&                  theTol) override;

  Standard_EXPORT bool NewPoint(const TopoDS_Vertex& theVertex,
                                gp_Pnt&              thePnt,
                                double&              theTol) override;

  Standard_EXPORT bool NewCurve2d(const TopoDS_Edge&         theEdge,
                                  const TopoDS_Face&         theFace,
                                  const TopoDS_Edge&         theNewEdge,
                                  const TopoDS_Face&         theNewFace,
                                  occ::handle<Geom2d_Curve>& theCurve,
                                  double&                    theTol) override;

  Standard_EXPORT bool NewParameter(const TopoDS_Vertex& theVertex,
                                    const TopoDS_Edge&   theEdge,
                                    double&              thePnt,
                                    double&              theTol) override;

  Standard_EXPORT GeomAbs_Shape Continuity(const TopoDS_Edge& theEdge,
                                           const TopoDS_Face& theFace1,
                                           const TopoDS_Face& theFace2,
                                           const TopoDS_Edge& theNewEdge,
                                           const TopoDS_Face& theNewFace1,
                                           const TopoDS_Face& theNewFace2) override;

  Standard_EXPORT bool NewTriangulation(const TopoDS_Face&               theFace,
                                        occ::handle<Poly_Triangulation>& theTri) override;

  Standard_EXPORT bool NewPolygon(const TopoDS_Edge&           theEdge,
                                  occ::handle<Poly_Polygon3D>& thePoly) override;

  Standard_EXPORT bool NewPolygonOnTriangulation(
    const TopoDS_Edge&                        theEdge,
    const TopoDS_Face&                        theFace,
    occ::handle<Poly_PolygonOnTriangulation>& thePoly) override;

  DEFINE_STANDARD_RTTIEXT(BRepTools_CopyModification, BRepTools_Modification)

private:
  bool myCopyGeom;
  bool myCopyMesh;
};
