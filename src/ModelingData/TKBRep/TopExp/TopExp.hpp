#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_Map.hpp>
#include <TopoDS_Vertex.hpp>
#include <Standard_Boolean.hpp>

class TopoDS_Shape;
class TopoDS_Edge;
class TopoDS_Wire;

class TopExp
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void MapShapes(
    const TopoDS_Shape&                                            S,
    const TopAbs_ShapeEnum                                         T,
    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& M);

  Standard_EXPORT static void MapShapes(
    const TopoDS_Shape&                                            S,
    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& M,
    const bool                                                     cumOri = true,
    const bool                                                     cumLoc = true);

  Standard_EXPORT static void MapShapes(const TopoDS_Shape&                                     S,
                                        NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& M,
                                        const bool cumOri = true,
                                        const bool cumLoc = true);

  Standard_EXPORT static void MapShapesAndAncestors(
    const TopoDS_Shape&                                  S,
    const TopAbs_ShapeEnum                               TS,
    const TopAbs_ShapeEnum                               TA,
    NCollection_IndexedDataMap<TopoDS_Shape,
                               NCollection_List<TopoDS_Shape>,
                               TopTools_ShapeMapHasher>& M);

  Standard_EXPORT static void MapShapesAndUniqueAncestors(
    const TopoDS_Shape&                                  S,
    const TopAbs_ShapeEnum                               TS,
    const TopAbs_ShapeEnum                               TA,
    NCollection_IndexedDataMap<TopoDS_Shape,
                               NCollection_List<TopoDS_Shape>,
                               TopTools_ShapeMapHasher>& M,
    const bool                                           useOrientation = false);

  Standard_EXPORT static TopoDS_Vertex FirstVertex(const TopoDS_Edge& E, const bool CumOri = false);

  Standard_EXPORT static TopoDS_Vertex LastVertex(const TopoDS_Edge& E, const bool CumOri = false);

  Standard_EXPORT static void Vertices(const TopoDS_Edge& E,
                                       TopoDS_Vertex&     Vfirst,
                                       TopoDS_Vertex&     Vlast,
                                       const bool         CumOri = false);

  Standard_EXPORT static void Vertices(const TopoDS_Wire& W,
                                       TopoDS_Vertex&     Vfirst,
                                       TopoDS_Vertex&     Vlast);

  Standard_EXPORT static bool CommonVertex(const TopoDS_Edge& E1,
                                           const TopoDS_Edge& E2,
                                           TopoDS_Vertex&     V);
};
