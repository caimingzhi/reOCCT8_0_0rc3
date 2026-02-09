#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <BRepBuilderAPI_ModifyShape.hpp>

class TopoDS_Shape;

class BRepBuilderAPI_Copy : public BRepBuilderAPI_ModifyShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepBuilderAPI_Copy();

  Standard_EXPORT BRepBuilderAPI_Copy(const TopoDS_Shape& S,
                                      const bool          copyGeom = true,
                                      const bool          copyMesh = false);

  Standard_EXPORT void Perform(const TopoDS_Shape& S,
                               const bool          copyGeom = true,
                               const bool          copyMesh = false);
};
