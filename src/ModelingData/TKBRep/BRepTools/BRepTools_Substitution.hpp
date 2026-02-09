#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
class TopoDS_Shape;

class BRepTools_Substitution
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepTools_Substitution();

  Standard_EXPORT void Clear();

  Standard_EXPORT void Substitute(const TopoDS_Shape&                   OldShape,
                                  const NCollection_List<TopoDS_Shape>& NewShapes);

  Standard_EXPORT void Build(const TopoDS_Shape& S);

  Standard_EXPORT bool IsCopied(const TopoDS_Shape& S) const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Copy(const TopoDS_Shape& S) const;

private:
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher> myMap;
};
