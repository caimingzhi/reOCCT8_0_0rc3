#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Macro.hpp>

#include <BRepMesh_CircleTool.hpp>
#include <BRepMesh_Triangle.hpp>
#include <BRepMesh_Edge.hpp>
#include <IMeshData_Types.hpp>
#include <BRepMesh_DataStructureOfDelaun.hpp>
#include <BRepMesh_GeomTool.hpp>
#include <Message_ProgressRange.hpp>

class Bnd_Box2d;
class BRepMesh_Vertex;

class BRepMesh_Delaun
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepMesh_Delaun(const occ::handle<BRepMesh_DataStructureOfDelaun>& theOldMesh,
                                  const int                                          theCellsCountU,
                                  const int                                          theCellsCountV,
                                  const bool                                         isFillCircles);

  Standard_EXPORT BRepMesh_Delaun(IMeshData::Array1OfVertexOfDelaun& theVertices);

  Standard_EXPORT BRepMesh_Delaun(const occ::handle<BRepMesh_DataStructureOfDelaun>& theOldMesh,
                                  IMeshData::Array1OfVertexOfDelaun&                 theVertices);

  Standard_EXPORT BRepMesh_Delaun(const occ::handle<BRepMesh_DataStructureOfDelaun>& theOldMesh,
                                  IMeshData::VectorOfInteger& theVertexIndices);

  Standard_EXPORT BRepMesh_Delaun(const occ::handle<BRepMesh_DataStructureOfDelaun>& theOldMesh,
                                  IMeshData::VectorOfInteger& theVertexIndices,
                                  const int                   theCellsCountU,
                                  const int                   theCellsCountV);

  Standard_EXPORT void Init(IMeshData::Array1OfVertexOfDelaun& theVertices);

  Standard_EXPORT void InitCirclesTool(const int theCellsCountU, const int theCellsCountV);

  Standard_EXPORT void RemoveVertex(const BRepMesh_Vertex& theVertex);

  Standard_EXPORT void AddVertices(IMeshData::VectorOfInteger&  theVerticesIndices,
                                   const Message_ProgressRange& theRange = Message_ProgressRange());

  Standard_EXPORT bool UseEdge(const int theEdge);

  const occ::handle<BRepMesh_DataStructureOfDelaun>& Result() const { return myMeshData; }

  void ProcessConstraints()
  {
    insertInternalEdges();

    frontierAdjust();
  }

  Handle(IMeshData::MapOfInteger) Frontier() const { return getEdgesByType(BRepMesh_Frontier); }

  Handle(IMeshData::MapOfInteger) InternalEdges() const { return getEdgesByType(BRepMesh_Fixed); }

  Handle(IMeshData::MapOfInteger) FreeEdges() const { return getEdgesByType(BRepMesh_Free); }

  const BRepMesh_Vertex& GetVertex(const int theIndex) const
  {
    return myMeshData->GetNode(theIndex);
  }

  const BRepMesh_Edge& GetEdge(const int theIndex) const { return myMeshData->GetLink(theIndex); }

  const BRepMesh_Triangle& GetTriangle(const int theIndex) const
  {
    return myMeshData->GetElement(theIndex);
  }

  const BRepMesh_CircleTool& Circles() const { return myCircles; }

  Standard_EXPORT bool Contains(const int              theTriangleId,
                                const BRepMesh_Vertex& theVertex,
                                const double           theSqTolerance,
                                int&                   theEdgeOn) const;

  inline void SetAuxVertices(const IMeshData::VectorOfInteger& theSupVert)
  {
    mySupVert = theSupVert;
  }

  Standard_EXPORT void RemoveAuxElements();

private:
  enum ReplaceFlag
  {
    Replace,
    InsertAfter,
    InsertBefore
  };

  typedef NCollection_DataMap<int, IMeshData::MapOfInteger> DataMapOfMap;

  void initCirclesTool(const Bnd_Box2d& theBox, const int theCellsCountU, const int theCellsCountV);

  void fillBndBox(IMeshData::SequenceOfBndB2d& theBoxes,
                  const BRepMesh_Vertex&       theV1,
                  const BRepMesh_Vertex&       theV2);

  Handle(IMeshData::MapOfInteger) getEdgesByType(const BRepMesh_DegreeOfFreedom theEdgeType) const;

  void perform(IMeshData::VectorOfInteger& theVertexIndices,
               const int                   theCellsCountU = -1,
               const int                   theCellsCountV = -1);

  void superMesh(const Bnd_Box2d& theBox);

  void compute(IMeshData::VectorOfInteger& theVertexIndices);

  void frontierAdjust();

  bool meshLeftPolygonOf(const int                       theEdgeIndex,
                         const bool                      isForward,
                         Handle(IMeshData::MapOfInteger) theSkipped = nullptr);

  int findNextPolygonLink(const int&                             theFirstNode,
                          const int&                             thePivotNode,
                          const BRepMesh_Vertex&                 thePivotVertex,
                          const gp_Vec2d&                        theRefLinkDir,
                          const IMeshData::SequenceOfBndB2d&     theBoxes,
                          const IMeshData::SequenceOfInteger&    thePolygon,
                          const Handle(IMeshData::MapOfInteger)& theSkipped,
                          const bool&                            isSkipLeprous,
                          IMeshData::MapOfInteger&               theLeprousLinks,
                          IMeshData::MapOfInteger&               theDeadLinks,
                          int&                                   theNextPivotNode,
                          gp_Vec2d&                              theNextLinkDir,
                          Bnd_B2d&                               theNextLinkBndBox);

  bool checkIntersection(const BRepMesh_Edge&                theLink,
                         const IMeshData::SequenceOfInteger& thePolygon,
                         const IMeshData::SequenceOfBndB2d&  thePolyBoxes,
                         const bool                          isConsiderEndPointTouch,
                         const bool                          isConsiderPointOnEdge,
                         const bool                          isSkipLastEdge,
                         Bnd_B2d&                            theLinkBndBox) const;

  void meshPolygon(IMeshData::SequenceOfInteger&   thePolygon,
                   IMeshData::SequenceOfBndB2d&    thePolyBoxes,
                   Handle(IMeshData::MapOfInteger) theSkipped = nullptr);

  void decomposeSimplePolygon(IMeshData::SequenceOfInteger& thePolygon,
                              IMeshData::SequenceOfBndB2d&  thePolyBoxes,
                              IMeshData::SequenceOfInteger& thePolygonCut,
                              IMeshData::SequenceOfBndB2d&  thePolyBoxesCut);

  bool meshElementaryPolygon(const IMeshData::SequenceOfInteger& thePolygon);

  void createTriangles(const int theVertexIndex, IMeshData::MapOfIntegerInteger& thePoly);

  void addTriangle(const int (&theEdgesId)[3],
                   const bool (&theEdgesOri)[3],
                   const int (&theNodesId)[3]);

  void deleteTriangle(const int theIndex, IMeshData::MapOfIntegerInteger& theLoopEdges);

  void getOrientedNodes(const BRepMesh_Edge& theEdge, const bool isForward, int* theNodes) const;

  void processLoop(const int                           theLinkFrom,
                   const int                           theLinkTo,
                   const IMeshData::SequenceOfInteger& thePolygon,
                   const IMeshData::SequenceOfBndB2d&  thePolyBoxes);

  int createAndReplacePolygonLink(const int                     theNodes[],
                                  const gp_Pnt2d                thePnts[],
                                  const int                     theRootIndex,
                                  const ReplaceFlag             theReplaceFlag,
                                  IMeshData::SequenceOfInteger& thePolygon,
                                  IMeshData::SequenceOfBndB2d&  thePolyBoxes);

  void createTrianglesOnNewVertices(IMeshData::VectorOfInteger&  theVertexIndices,
                                    const Message_ProgressRange& theRange);

  void cleanupMesh();

  bool isBoundToFrontier(const int theRefNodeId, const int theRefLinkId);

  void cleanupPolygon(const IMeshData::SequenceOfInteger& thePolygon,
                      const IMeshData::SequenceOfBndB2d&  thePolyBoxes);

  bool isVertexInsidePolygon(const int&                        theVertexId,
                             const IMeshData::VectorOfInteger& thePolygonVertices) const;

  void killTrianglesAroundVertex(const int                           theZombieNodeId,
                                 const IMeshData::VectorOfInteger&   thePolyVertices,
                                 const IMeshData::MapOfInteger&      thePolyVerticesFindMap,
                                 const IMeshData::SequenceOfInteger& thePolygon,
                                 const IMeshData::SequenceOfBndB2d&  thePolyBoxes,
                                 IMeshData::MapOfInteger&            theSurvivedLinks,
                                 IMeshData::MapOfIntegerInteger&     theLoopEdges,
                                 IMeshData::VectorOfInteger&         theVictimNodes);

  void killTrianglesOnIntersectingLinks(const int&                          theLinkToCheckId,
                                        const BRepMesh_Edge&                theLinkToCheck,
                                        const int&                          theEndPoint,
                                        const IMeshData::SequenceOfInteger& thePolygon,
                                        const IMeshData::SequenceOfBndB2d&  thePolyBoxes,
                                        IMeshData::MapOfInteger&            theSurvivedLinks,
                                        IMeshData::MapOfIntegerInteger&     theLoopEdges);

  void killLinkTriangles(const int& theLinkId, IMeshData::MapOfIntegerInteger& theLoopEdges);

  double calculateDist(const gp_XY            theVEdges[3],
                       const gp_XY            thePoints[3],
                       const BRepMesh_Vertex& theVertex,
                       double                 theDistance[3],
                       double                 theSqModulus[3],
                       int&                   theEdgeOn) const;

  BRepMesh_GeomTool::IntFlag intSegSeg(const BRepMesh_Edge& theEdge1,
                                       const BRepMesh_Edge& theEdge2,
                                       const bool           isConsiderEndPointTouch,
                                       const bool           isConsiderPointOnEdge,
                                       gp_Pnt2d&            theIntPnt) const;

  double polyArea(const IMeshData::SequenceOfInteger& thePolygon,
                  const int                           theStartIndex,
                  const int                           theEndIndex) const;

  void insertInternalEdges();

  bool isSupVertex(const int theVertexIdx) const
  {
    for (IMeshData::VectorOfInteger::Iterator aIt(mySupVert); aIt.More(); aIt.Next())
    {
      if (theVertexIdx == aIt.Value())
      {
        return true;
      }
    }

    return false;
  }

private:
  occ::handle<BRepMesh_DataStructureOfDelaun> myMeshData;
  BRepMesh_CircleTool                         myCircles;
  IMeshData::VectorOfInteger                  mySupVert;
  bool                                        myInitCircles;
  BRepMesh_Triangle                           mySupTrian;
};
