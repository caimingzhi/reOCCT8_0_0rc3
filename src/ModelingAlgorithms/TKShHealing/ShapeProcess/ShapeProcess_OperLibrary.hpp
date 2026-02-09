#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
class TopoDS_Shape;
class ShapeProcess_ShapeContext;
class BRepTools_Modification;
class ShapeExtend_MsgRegistrator;

class ShapeProcess_OperLibrary
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Init();

  Standard_EXPORT static TopoDS_Shape ApplyModifier(
    const TopoDS_Shape&                                                       S,
    const occ::handle<ShapeProcess_ShapeContext>&                             context,
    const occ::handle<BRepTools_Modification>&                                M,
    NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& map,
    const occ::handle<ShapeExtend_MsgRegistrator>&                            msg = nullptr,
    bool theMutableInput                                                          = false);
};
