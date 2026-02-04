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

//! This class represents mechanism of simple offset algorithm
//! i.e. topology-preserve offset construction without intersection.
//!
//! The list below shows mapping scheme:
//! - Each surface is mapped to its geometric offset surface.
//! - For each edge, pcurves are mapped to the same pcurves on offset surfaces.
//! - For each edge, 3d curve is constructed by re-approximation of pcurve on the first offset face.
//! - Position of each vertex in a result shell is computed as average point of all ends of edges
//! shared by that vertex.
//! - Tolerances are updated according to the resulting geometry.
class BRepOffset_SimpleOffset : public BRepTools_Modification
{
public:
  DEFINE_STANDARD_RTTI_INLINE(BRepOffset_SimpleOffset, BRepTools_Modification)

  //! Constructor.
  //! @param theInputShape shape to be offset
  //! @param theOffsetValue offset distance (signed)
  //! @param theTolerance tolerance for handling singular points
  Standard_EXPORT BRepOffset_SimpleOffset(const TopoDS_Shape& theInputShape,
                                          const double        theOffsetValue,
                                          const double        theTolerance);

  //! Returns true if the face <F> has been
  //! modified. In this case, <S> is the new geometric
  //! support of the face, <L> the new location,
  //! <Tol> the new tolerance. <RevWires> has to be set to
  //! true when the modification reverses the
  //! normal of the surface. (the wires have to be
  //! reversed). <RevFace> has to be set to
  //! true if the orientation of the modified
  //! face changes in the shells which contain it.
  //! Here, <RevFace> will return true if the
  //! gp_Trsf is negative.
  Standard_EXPORT bool NewSurface(const TopoDS_Face&         F,
                                  occ::handle<Geom_Surface>& S,
                                  TopLoc_Location&           L,
                                  double&                    Tol,
                                  bool&                      RevWires,
                                  bool&                      RevFace) override;

  //! Returns true if the edge <E> has been
  //! modified. In this case, <C> is the new geometric
  //! support of the edge, <L> the new location,
  //! <Tol> the new tolerance. Otherwise, returns
  //! false, and <C>, <L>,
  //! <Tol> are not significant.
  Standard_EXPORT bool NewCurve(const TopoDS_Edge&       E,
                                occ::handle<Geom_Curve>& C,
                                TopLoc_Location&         L,
                                double&                  Tol) override;

  //! Returns true if the vertex <V> has been
  //! modified. In this case, <P> is the new geometric
  //! support of the vertex, <Tol> the new tolerance.
  //! Otherwise, returns false, and <P>,
  //! <Tol> are not significant.
  Standard_EXPORT bool NewPoint(const TopoDS_Vertex& V, gp_Pnt& P, double& Tol) override;

  //! Returns true if the edge <E> has a new
  //! curve on surface on the face <F>. In this case,
  //! <C> is the new geometric support of the edge,
  //! <L> the new location, <Tol> the new tolerance.
  //! Otherwise, returns false, and <C>, <L>,
  //! <Tol> are not significant.
  Standard_EXPORT bool NewCurve2d(const TopoDS_Edge&         E,
                                  const TopoDS_Face&         F,
                                  const TopoDS_Edge&         NewE,
                                  const TopoDS_Face&         NewF,
                                  occ::handle<Geom2d_Curve>& C,
                                  double&                    Tol) override;

  //! Returns true if the Vertex <V> has a new
  //! parameter on the edge <E>. In this case,
  //! <P> is the parameter, <Tol> the new tolerance.
  //! Otherwise, returns false, and <P>,
  //! <Tol> are not significant.
  Standard_EXPORT bool NewParameter(const TopoDS_Vertex& V,
                                    const TopoDS_Edge&   E,
                                    double&              P,
                                    double&              Tol) override;

  //! Returns the continuity of <NewE> between <NewF1>
  //! and <NewF2>.
  //!
  //! <NewE> is the new edge created from <E>. <NewF1>
  //! (resp. <NewF2>) is the new face created from <F1>
  //! (resp. <F2>).
  Standard_EXPORT GeomAbs_Shape Continuity(const TopoDS_Edge& E,
                                           const TopoDS_Face& F1,
                                           const TopoDS_Face& F2,
                                           const TopoDS_Edge& NewE,
                                           const TopoDS_Face& NewF1,
                                           const TopoDS_Face& NewF2) override;

private:
  //! Method to fill new face data for single face.
  void FillFaceData(const TopoDS_Face& theFace);

  //! Method to fill new edge data for single edge.
  void FillEdgeData(const TopoDS_Edge&                                         theEdge,
                    const NCollection_IndexedDataMap<TopoDS_Shape,
                                                     NCollection_List<TopoDS_Shape>,
                                                     TopTools_ShapeMapHasher>& theEdgeFaceMap,
                    const int                                                  theIdx);

  //! Method to fill new vertex data for single vertex.
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
    occ::handle<Geom_Curve> myOffsetC; // Resulting curve.
    TopLoc_Location         myL;
    double                  myTol;
  };

  struct NewVertexData
  {
    gp_Pnt myP;
    double myTol;
  };

  //! Fills offset data.
  void FillOffsetData(const TopoDS_Shape& theInputShape);

  //! Copy-assignment constructor and copy constructor are not allowed.
  void operator=(const BRepOffset_SimpleOffset&)          = delete;
  BRepOffset_SimpleOffset(const BRepOffset_SimpleOffset&) = delete;

  //! Map of faces to new faces information.
  NCollection_DataMap<TopoDS_Face, NewFaceData> myFaceInfo;

  //! Map of edges to new edges information.
  NCollection_DataMap<TopoDS_Edge, NewEdgeData> myEdgeInfo;

  //! Map of vertices to new vertices information.
  NCollection_DataMap<TopoDS_Vertex, NewVertexData> myVertexInfo;

  //! Offset value.
  double myOffsetValue;

  //! Tolerance.
  double myTolerance;
};

