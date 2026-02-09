#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopAbs_ShapeEnum.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
class TopoDS_Shape;

class TopOpeBRepTool_AncestorsTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void MakeAncestors(
    const TopoDS_Shape&                                  S,
    const TopAbs_ShapeEnum                               TS,
    const TopAbs_ShapeEnum                               TA,
    NCollection_IndexedDataMap<TopoDS_Shape,
                               NCollection_List<TopoDS_Shape>,
                               TopTools_ShapeMapHasher>& M);
};
