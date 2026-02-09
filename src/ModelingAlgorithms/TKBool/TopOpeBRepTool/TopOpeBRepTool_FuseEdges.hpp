#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_IndexedMap.hpp>
#include <NCollection_Map.hpp>
class TopoDS_Vertex;
class TopoDS_Edge;

class TopOpeBRepTool_FuseEdges
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepTool_FuseEdges(const TopoDS_Shape& theShape,
                                           const bool          PerformNow = false);

  Standard_EXPORT void AvoidEdges(
    const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& theMapEdg);

  Standard_EXPORT void Edges(
    NCollection_DataMap<int, NCollection_List<TopoDS_Shape>>& theMapLstEdg);

  Standard_EXPORT void ResultEdges(NCollection_DataMap<int, TopoDS_Shape>& theMapEdg);

  Standard_EXPORT void Faces(
    NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& theMapFac);

  Standard_EXPORT TopoDS_Shape& Shape();

  Standard_EXPORT int NbVertices();

  Standard_EXPORT void Perform();

private:
  Standard_EXPORT void BuildListEdges();

  Standard_EXPORT void BuildListResultEdges();

  Standard_EXPORT void BuildListConnexEdge(
    const TopoDS_Shape&                                     theEdge,
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theMapUniq,
    NCollection_List<TopoDS_Shape>&                         theLstEdg);

  Standard_EXPORT bool NextConnexEdge(const TopoDS_Vertex& theVertex,
                                      const TopoDS_Shape&  theEdge,
                                      TopoDS_Shape&        theEdgeConnex) const;

  Standard_EXPORT bool SameSupport(const TopoDS_Edge& E1, const TopoDS_Edge& E2) const;

  Standard_EXPORT bool UpdatePCurve(const TopoDS_Edge&                    theOldEdge,
                                    TopoDS_Edge&                          theNewEdge,
                                    const NCollection_List<TopoDS_Shape>& theLstEdg) const;

  TopoDS_Shape myShape;
  bool         myShapeDone;
  bool         myEdgesDone;
  bool         myResultEdgesDone;
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    myMapVerLstEdg;
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                                                           myMapEdgLstFac;
  NCollection_DataMap<int, NCollection_List<TopoDS_Shape>>                 myMapLstEdg;
  NCollection_DataMap<int, TopoDS_Shape>                                   myMapEdg;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myMapFaces;
  int                                                                      myNbConnexEdge;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>            myAvoidEdg;
};
