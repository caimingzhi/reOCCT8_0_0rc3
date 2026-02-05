#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TDF_Label.hpp>
#include <NCollection_Map.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>
class TNaming_NamedShape;
class TDF_Label;
class TopoDS_Shape;

class TNaming_NamingTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void CurrentShape(
    const NCollection_Map<TDF_Label>&                              Valid,
    const NCollection_Map<TDF_Label>&                              Forbiden,
    const occ::handle<TNaming_NamedShape>&                         NS,
    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& MS);

  Standard_EXPORT static void CurrentShapeFromShape(
    const NCollection_Map<TDF_Label>&                              Valid,
    const NCollection_Map<TDF_Label>&                              Forbiden,
    const TDF_Label&                                               Acces,
    const TopoDS_Shape&                                            S,
    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& MS);

  Standard_EXPORT static void BuildDescendants(const occ::handle<TNaming_NamedShape>& NS,
                                               NCollection_Map<TDF_Label>&            Labels);
};
