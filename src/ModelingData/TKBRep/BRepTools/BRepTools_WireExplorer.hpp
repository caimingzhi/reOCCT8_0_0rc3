#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Face.hpp>
#include <NCollection_Map.hpp>
#include <TopAbs_Orientation.hpp>
class TopoDS_Wire;

class BRepTools_WireExplorer
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepTools_WireExplorer();

  Standard_EXPORT BRepTools_WireExplorer(const TopoDS_Wire& W);

  Standard_EXPORT BRepTools_WireExplorer(const TopoDS_Wire& W, const TopoDS_Face& F);

  Standard_EXPORT void Init(const TopoDS_Wire& W);

  Standard_EXPORT void Init(const TopoDS_Wire& W, const TopoDS_Face& F);

  Standard_EXPORT void Init(const TopoDS_Wire& W,
                            const TopoDS_Face& F,
                            const double       UMin,
                            const double       UMax,
                            const double       VMin,
                            const double       VMax);

  Standard_EXPORT bool More() const;

  Standard_EXPORT void Next();

  Standard_EXPORT const TopoDS_Edge& Current() const;

  Standard_EXPORT TopAbs_Orientation Orientation() const;

  Standard_EXPORT const TopoDS_Vertex& CurrentVertex() const;

  Standard_EXPORT void Clear();

private:
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher> myMap;
  TopoDS_Edge                                                                                myEdge;
  TopoDS_Vertex                                          myVertex;
  TopoDS_Face                                            myFace;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> myDoubles;
  bool                                                   myReverse;
  double                                                 myTolU;
  double                                                 myTolV;
};
