#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class TNaming_UsedShapes;
class TNaming_NamedShape;
class Standard_ConstructionError;
class TDF_Label;
class TopoDS_Shape;

class TNaming_Builder
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TNaming_Builder(const TDF_Label& aLabel);

  Standard_EXPORT void Generated(const TopoDS_Shape& newShape);

  Standard_EXPORT void Generated(const TopoDS_Shape& oldShape, const TopoDS_Shape& newShape);

  Standard_EXPORT void Delete(const TopoDS_Shape& oldShape);

  Standard_EXPORT void Modify(const TopoDS_Shape& oldShape, const TopoDS_Shape& newShape);

  Standard_EXPORT void Select(const TopoDS_Shape& aShape, const TopoDS_Shape& inShape);

  Standard_EXPORT occ::handle<TNaming_NamedShape> NamedShape() const;

private:
  occ::handle<TNaming_UsedShapes> myShapes;
  occ::handle<TNaming_NamedShape> myAtt;
};
