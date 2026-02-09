#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_List.hpp>
class TopoDS_Edge;
class TopoDS_Shape;

class ShapeFix_EdgeConnect
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ShapeFix_EdgeConnect();

  Standard_EXPORT void Add(const TopoDS_Edge& aFirst, const TopoDS_Edge& aSecond);

  Standard_EXPORT void Add(const TopoDS_Shape& aShape);

  Standard_EXPORT void Build();

  Standard_EXPORT void Clear();

private:
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myVertices;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    myLists;
};
