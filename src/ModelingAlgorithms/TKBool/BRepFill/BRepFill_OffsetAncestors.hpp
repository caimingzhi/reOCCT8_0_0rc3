#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
class BRepFill_OffsetWire;
class TopoDS_Edge;
class TopoDS_Shape;

class BRepFill_OffsetAncestors
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepFill_OffsetAncestors();

  Standard_EXPORT BRepFill_OffsetAncestors(BRepFill_OffsetWire& Paral);

  Standard_EXPORT void Perform(BRepFill_OffsetWire& Paral);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT bool HasAncestor(const TopoDS_Edge& S1) const;

  Standard_EXPORT const TopoDS_Shape& Ancestor(const TopoDS_Edge& S1) const;

private:
  bool                                                                     myIsPerform;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myMap;
};
