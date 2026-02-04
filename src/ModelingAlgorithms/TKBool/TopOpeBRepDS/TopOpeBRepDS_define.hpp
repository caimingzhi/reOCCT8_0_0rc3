#pragma once


#include <TopAbs_ShapeEnum.hpp>

#include <TopAbs_Orientation.hpp>

#include <TopAbs_State.hpp>

#include <TopoDS_Shape.hpp>

#include <TopTools_ShapeMapHasher.hpp>

#include <NCollection_Map.hpp>

#include <NCollection_List.hpp>

#include <NCollection_IndexedMap.hpp>

#include <NCollection_DataMap.hpp>

#include <Standard_Integer.hpp>

#include <NCollection_IndexedDataMap.hpp>

#include <TopoDS_Face.hpp>

#include <TopoDS_Edge.hpp>

#include <TopoDS_Vertex.hpp>

#include <TCollection_AsciiString.hpp>

#include <TopOpeBRepDS_Interference.hpp>

#include <TopOpeBRepDS_ShapeShapeInterference.hpp>
#include <TopOpeBRepDS_CurvePointInterference.hpp>
#include <TopOpeBRepDS_EdgeVertexInterference.hpp>
#include <TopOpeBRepDS_FaceEdgeInterference.hpp>
#include <TopOpeBRepDS_InterferenceIterator.hpp>
#include <TopOpeBRepDS_HDataStructure.hpp>
#include <TopOpeBRepDS_PDataStructure.hpp>
#include <TopOpeBRepDS_DataStructure.hpp>
#include <TopOpeBRepDS_Kind.hpp>
#include <TopOpeBRepDS_Config.hpp>
#include <TopOpeBRepDS_Transition.hpp>

#define MDSlioloi NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator
#define MDSloi NCollection_List<occ::handle<TopOpeBRepDS_Interference>>
#define MDShi occ::handle<TopOpeBRepDS_Interference>
#define MDShssi occ::handle<TopOpeBRepDS_ShapeShapeInterference>
#define MDShcpi occ::handle<TopOpeBRepDS_CurvePointInterference>
#define MDScpi TopOpeBRepDS_CurvePointInterference
#define MDShevi occ::handle<TopOpeBRepDS_EdgeVertexInterference>
#define MDSevi TopOpeBRepDS_EdgeVertexInterference
#define MDShfei occ::handle<TopOpeBRepDS_FaceEdgeInterference>
#define MDShsci occ::handle<TopOpeBRepDS_SurfaceCurveInterference>
#define MDScux TopOpeBRepDS_CurveExplorer
#define MDScud TopOpeBRepDS_CurveData
#define MDScu TopOpeBRepDS_Curve
#define MDSpox TopOpeBRepDS_PointExplorer
#define MDSpod TopOpeBRepDS_PointData
#define MDSpo TopOpeBRepDS_Point
#define MDSii TopOpeBRepDS_InterferenceIterator
#define MDShds occ::handle<TopOpeBRepDS_HDataStructure>
#define MDSds TopOpeBRepDS_DataStructure
#define MDSpds TopOpeBRepDS_PDataStructure
#define MDSk TopOpeBRepDS_Kind
#define MDSc TopOpeBRepDS_Config
#define MDSt TopOpeBRepDS_Transition

#define MDSsd TopOpeBRepDS_ShapeData
#define MDSmosd                                                                                    \
  NCollection_IndexedDataMap<TopoDS_Shape, TopOpeBRepDS_ShapeData, TopTools_ShapeMapHasher>
#define MDSitl TopOpeBRepDS_InterferenceTool

