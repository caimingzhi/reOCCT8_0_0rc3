#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
class TopoDS_Edge;
class TopoDS_Vertex;
class TopoDS_Shape;

class BRepTools_Quilt
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepTools_Quilt();

  Standard_EXPORT void Bind(const TopoDS_Edge& Eold, const TopoDS_Edge& Enew);

  Standard_EXPORT void Bind(const TopoDS_Vertex& Vold, const TopoDS_Vertex& Vnew);

  Standard_EXPORT void Add(const TopoDS_Shape& S);

  Standard_EXPORT bool IsCopied(const TopoDS_Shape& S) const;

  Standard_EXPORT const TopoDS_Shape& Copy(const TopoDS_Shape& S) const;

  Standard_EXPORT TopoDS_Shape Shells() const;

private:
  NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myBounds;
  bool                                                                            hasCopy;
};
