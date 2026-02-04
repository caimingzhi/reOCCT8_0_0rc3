#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Shape.hpp>
#include <TopOpeBRepBuild_VertexInfo.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_List.hpp>
class TopoDS_Wire;

class TopOpeBRepBuild_Tools2d
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void MakeMapOfShapeVertexInfo(
    const TopoDS_Wire& aWire,
    NCollection_IndexedDataMap<TopoDS_Shape, TopOpeBRepBuild_VertexInfo, TopTools_ShapeMapHasher>&
      aMap);

  Standard_EXPORT static void DumpMapOfShapeVertexInfo(
    const NCollection_IndexedDataMap<TopoDS_Shape,
                                     TopOpeBRepBuild_VertexInfo,
                                     TopTools_ShapeMapHasher>& aMap);

  Standard_EXPORT static void Path(const TopoDS_Wire&              aWire,
                                   NCollection_List<TopoDS_Shape>& aResList);
};

