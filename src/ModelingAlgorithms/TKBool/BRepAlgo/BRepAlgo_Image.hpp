#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Boolean.hpp>
#include <TopAbs_ShapeEnum.hpp>
class TopoDS_Shape;

class BRepAlgo_Image
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepAlgo_Image();

  Standard_EXPORT void SetRoot(const TopoDS_Shape& S);

  Standard_EXPORT void Bind(const TopoDS_Shape& OldS, const TopoDS_Shape& NewS);

  Standard_EXPORT void Bind(const TopoDS_Shape& OldS, const NCollection_List<TopoDS_Shape>& NewS);

  Standard_EXPORT void Add(const TopoDS_Shape& OldS, const TopoDS_Shape& NewS);

  Standard_EXPORT void Add(const TopoDS_Shape& OldS, const NCollection_List<TopoDS_Shape>& NewS);

  Standard_EXPORT void Clear();

  Standard_EXPORT void Remove(const TopoDS_Shape& S);

  Standard_EXPORT void RemoveRoot(const TopoDS_Shape& Root);

  Standard_EXPORT void ReplaceRoot(const TopoDS_Shape& OldRoot, const TopoDS_Shape& NewRoot);

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Roots() const;

  Standard_EXPORT bool IsImage(const TopoDS_Shape& S) const;

  Standard_EXPORT const TopoDS_Shape& ImageFrom(const TopoDS_Shape& S) const;

  Standard_EXPORT const TopoDS_Shape& Root(const TopoDS_Shape& S) const;

  Standard_EXPORT bool HasImage(const TopoDS_Shape& S) const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Image(const TopoDS_Shape& S) const;

  Standard_EXPORT void LastImage(const TopoDS_Shape& S, NCollection_List<TopoDS_Shape>& L) const;

  Standard_EXPORT void Compact();

  Standard_EXPORT void Filter(const TopoDS_Shape& S, const TopAbs_ShapeEnum ShapeType);

private:
  NCollection_List<TopoDS_Shape>                                                             roots;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>                   up;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher> down;
};
