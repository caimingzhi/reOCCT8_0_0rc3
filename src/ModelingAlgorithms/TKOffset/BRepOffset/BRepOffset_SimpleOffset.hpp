#pragma once

#include <BRepTools_Modification.hpp>
#include <Geom2d_Curve.hpp>
#include <GeomAbs_Shape.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Macro.hpp>
#include <Standard_Real.hpp>
#include <Standard_Type.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>

class BRepOffset_SimpleOffset : public BRepTools_Modification
{
public:
  DEFINE_STANDARD_RTTI_INLINE(BRepOffset_SimpleOffset, BRepTools_Modification)

  Standard_EXPORT BRepOffset_SimpleOffset(const TopoDS_Shape& theInputShape,
                                          const double        theOffsetValue,
                                          const double        theTolerance);

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

private:
  void FillFaceData(const TopoDS_Face& theFace);

  void FillEdgeData(const TopoDS_Edge&                                         theEdge,
                    const NCollection_IndexedDataMap<TopoDS_Shape,
                                                     NCollection_List<TopoDS_Shape>,
                                                     TopTools_ShapeMapHasher>& theEdgeFaceMap,
                    const int                                                  theIdx);

  void FillVertexData(const TopoDS_Vertex&                                       theVertex,
                      const NCollection_IndexedDataMap<TopoDS_Shape,
                                                       NCollection_List<TopoDS_Shape>,
                                                       TopTools_ShapeMapHasher>& theVertexEdgeMap,
                      const int                                                  theIdx);

  struct NewFaceData
  {
    occ::handle<Geom_Surface> myOffsetS;
    TopLoc_Location           myL;
    double                    myTol;
    bool                      myRevWires;
    bool                      myRevFace;
  };

  struct NewEdgeData
  {
    occ::handle<Geom_Curve> myOffsetC;
    TopLoc_Location         myL;
    double                  myTol;
  };

  struct NewVertexData
  {
    gp_Pnt myP;
    double myTol;
  };

  void FillOffsetData(const TopoDS_Shape& theInputShape);

  void operator=(const BRepOffset_SimpleOffset&)          = delete;
  BRepOffset_SimpleOffset(const BRepOffset_SimpleOffset&) = delete;

  NCollection_DataMap<TopoDS_Face, NewFaceData> myFaceInfo;

  NCollection_DataMap<TopoDS_Edge, NewEdgeData> myEdgeInfo;

  NCollection_DataMap<TopoDS_Vertex, NewVertexData> myVertexInfo;

  double myOffsetValue;

  double myTolerance;
};
