#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <BRepBuilderAPI_MakeShape.hpp>
class TopoDS_Face;
class TopoDS_Shell;
class TopoDS_Solid;

class BRepPrimAPI_MakeOneAxis : public BRepBuilderAPI_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT virtual void* OneAxis() = 0;

  Standard_EXPORT void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  Standard_EXPORT const TopoDS_Face& Face();
  Standard_EXPORT                    operator TopoDS_Face();

  Standard_EXPORT const TopoDS_Shell& Shell();
  Standard_EXPORT                     operator TopoDS_Shell();

  Standard_EXPORT const TopoDS_Solid& Solid();
  Standard_EXPORT                     operator TopoDS_Solid();
};
