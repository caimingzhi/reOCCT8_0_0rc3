#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopAbs_Orientation.hpp>
class TopoDS_Shape;

class BRepSweep_Tool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepSweep_Tool(const TopoDS_Shape& aShape);

  Standard_EXPORT int NbShapes() const;

  Standard_EXPORT int Index(const TopoDS_Shape& aShape) const;

  Standard_EXPORT TopoDS_Shape Shape(const int anIndex) const;

  Standard_EXPORT TopAbs_ShapeEnum Type(const TopoDS_Shape& aShape) const;

  Standard_EXPORT TopAbs_Orientation Orientation(const TopoDS_Shape& aShape) const;

  Standard_EXPORT void SetOrientation(TopoDS_Shape& aShape, const TopAbs_Orientation Or) const;

private:
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> myMap;
};
