#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <TopoDS_Shape.hpp>
#include <TopOpeBRepDS_ShapeWithState.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <TopAbs_State.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <NCollection_List.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_IndexedMap.hpp>
class TopoDS_Shape;
class TopOpeBRepTool_ShapeClassifier;
class TopoDS_Face;
class TopoDS_Edge;
class gp_Vec;
class TopoDS_Wire;

//! Auxiliary methods used in TopOpeBRepBuild_Builder1 class
class TopOpeBRepBuild_Tools
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void FindState(
    const TopoDS_Shape&                                                       aVertex,
    const TopAbs_State                                                        aState,
    const TopAbs_ShapeEnum                                                    aShapeEnum,
    const NCollection_IndexedDataMap<TopoDS_Shape,
                                     NCollection_List<TopoDS_Shape>,
                                     TopTools_ShapeMapHasher>&                aMapVertexEdges,
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>&                   aMapProcessedVertices,
    NCollection_DataMap<TopoDS_Shape, TopAbs_State, TopTools_ShapeMapHasher>& aMapVs);

  Standard_EXPORT static void PropagateState(
    const NCollection_DataMap<TopoDS_Shape, TopAbs_State, TopTools_ShapeMapHasher>& aSplEdgesState,
    const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& anEdgesToRestMap,
    const TopAbs_ShapeEnum                                               aShapeEnum1,
    const TopAbs_ShapeEnum                                               aShapeEnum2,
    TopOpeBRepTool_ShapeClassifier&                                      aShapeClassifier,
    NCollection_IndexedDataMap<TopoDS_Shape, TopOpeBRepDS_ShapeWithState, TopTools_ShapeMapHasher>&
                                                                  aMapOfShapeWithState,
    const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& anUnkStateShapes);

  Standard_EXPORT static TopAbs_State FindStateThroughVertex(
    const TopoDS_Shape&             aShape,
    TopOpeBRepTool_ShapeClassifier& aShapeClassifier,
    NCollection_IndexedDataMap<TopoDS_Shape, TopOpeBRepDS_ShapeWithState, TopTools_ShapeMapHasher>&
                                                                  aMapOfShapeWithState,
    const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& anAvoidSubshMap);

  Standard_EXPORT static void PropagateStateForWires(
    const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& aFacesToRestMap,
    NCollection_IndexedDataMap<TopoDS_Shape, TopOpeBRepDS_ShapeWithState, TopTools_ShapeMapHasher>&
      aMapOfShapeWithState);

  Standard_EXPORT static void SpreadStateToChild(
    const TopoDS_Shape& aShape,
    const TopAbs_State  aState,
    NCollection_IndexedDataMap<TopoDS_Shape, TopOpeBRepDS_ShapeWithState, TopTools_ShapeMapHasher>&
      aMapOfShapeWithState);

  Standard_EXPORT static void FindState1(
    const TopoDS_Shape&                                                       anEdge,
    const TopAbs_State                                                        aState,
    const NCollection_IndexedDataMap<TopoDS_Shape,
                                     NCollection_List<TopoDS_Shape>,
                                     TopTools_ShapeMapHasher>&                aMapEdgesFaces,
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>&                   aMapProcessedVertices,
    NCollection_DataMap<TopoDS_Shape, TopAbs_State, TopTools_ShapeMapHasher>& aMapVs);

  Standard_EXPORT static void FindState2(
    const TopoDS_Shape&                                                       anEdge,
    const TopAbs_State                                                        aState,
    const NCollection_IndexedDataMap<TopoDS_Shape,
                                     NCollection_List<TopoDS_Shape>,
                                     TopTools_ShapeMapHasher>&                aMapEdgesFaces,
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>&                   aMapProcessedEdges,
    NCollection_DataMap<TopoDS_Shape, TopAbs_State, TopTools_ShapeMapHasher>& aMapVs);

  Standard_EXPORT static bool GetAdjacentFace(
    const TopoDS_Shape&                                        aFaceObj,
    const TopoDS_Shape&                                        anEObj,
    const NCollection_IndexedDataMap<TopoDS_Shape,
                                     NCollection_List<TopoDS_Shape>,
                                     TopTools_ShapeMapHasher>& anEdgeFaceMap,
    TopoDS_Shape&                                              anAdjFaceObj);

  Standard_EXPORT static void GetNormalToFaceOnEdge(const TopoDS_Face& aFObj,
                                                    const TopoDS_Edge& anEdgeObj,
                                                    gp_Vec&            aDirNormal);

  //! This function used to compute normal in point which is located
  //! near the point with param UV (used for computation of normals where the normal
  //! in the point UV equal to zero).
  Standard_EXPORT static void GetNormalInNearestPoint(const TopoDS_Face& aFace,
                                                      const TopoDS_Edge& anEdge,
                                                      gp_Vec&            aNormal);

  Standard_EXPORT static bool GetTangentToEdgeEdge(const TopoDS_Face& aFObj,
                                                   const TopoDS_Edge& anEdgeObj,
                                                   const TopoDS_Edge& aOriEObj,
                                                   gp_Vec&            aTangent);

  Standard_EXPORT static bool GetTangentToEdge(const TopoDS_Edge& anEdgeObj, gp_Vec& aTangent);

  //! Recompute PCurves of the all edges from the wire on the <toFace>
  Standard_EXPORT static void UpdatePCurves(const TopoDS_Wire& aWire,
                                            const TopoDS_Face& fromFace,
                                            const TopoDS_Face& toFace);

  //! Recompute PCurves of the closing (SIM, with 2 PCurves) edge on the NewFace
  Standard_EXPORT static void UpdateEdgeOnPeriodicalFace(const TopoDS_Edge& aEdgeToUpdate,
                                                         const TopoDS_Face& OldFace,
                                                         const TopoDS_Face& NewFace);

  //! Recompute PCurve of the edge on the NewFace
  Standard_EXPORT static void UpdateEdgeOnFace(const TopoDS_Edge& aEdgeToUpdate,
                                               const TopoDS_Face& OldFace,
                                               const TopoDS_Face& NewFace);

  Standard_EXPORT static bool IsDegEdgesTheSame(const TopoDS_Shape& anE1, const TopoDS_Shape& anE2);

  //! test if <oldFace> does not contain INTERNAL or EXTERNAL edges
  //! and remove such edges in case of its presence. The result is stored in <corrFace>
  Standard_EXPORT static void NormalizeFace(const TopoDS_Shape& oldFace, TopoDS_Shape& corrFace);

  //! test if UV representation of <oldFace> is good (i.e. face is closed in 2d).
  //! if face is not closed, this method will try to close such face and will
  //! return corrected edges in the <aMapOfCorrect2dEdges>. Parameter <aSourceShapes>
  //! used to fix the edge (or wires) which should be correct (Corrector used it as a
  //! start shapes). NOTE: Parameter corrFace doesn't mean anything. If you want to use
  //! this method, rebuild resulting face after by yourself using corrected edges.
  Standard_EXPORT static void CorrectFace2d(
    const TopoDS_Shape&                         oldFace,
    TopoDS_Shape&                               corrFace,
    const NCollection_IndexedMap<TopoDS_Shape>& aSourceShapes,
    NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>&
      aMapOfCorrect2dEdges);

  Standard_EXPORT static void CorrectTolerances(const TopoDS_Shape& aS,
                                                const double        aTolMax = 0.0001);

  Standard_EXPORT static void CorrectCurveOnSurface(const TopoDS_Shape& aS,
                                                    const double        aTolMax = 0.0001);

  Standard_EXPORT static void CorrectPointOnCurve(const TopoDS_Shape& aS,
                                                  const double        aTolMax = 0.0001);

  //! Checks if <theFace> has the properly closed in 2D boundary(ies)
  Standard_EXPORT static bool CheckFaceClosed2d(const TopoDS_Face& theFace);
};

