#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <BRepBuilderAPI_MakeShape.hpp>
class TopoDS_Face;
class TopoDS_Shell;
class TopoDS_Solid;

//! The abstract class MakeOneAxis is the root class of
//! algorithms used to construct rotational primitives.
class BRepPrimAPI_MakeOneAxis : public BRepBuilderAPI_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  //! The inherited commands should provide the algorithm.
  //! Returned as a pointer.
  Standard_EXPORT virtual void* OneAxis() = 0;

  //! Stores the solid in myShape.
  Standard_EXPORT void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  //! Returns the lateral face of the rotational primitive.
  Standard_EXPORT const TopoDS_Face& Face();
  Standard_EXPORT                    operator TopoDS_Face();

  //! Returns the constructed rotational primitive as a shell.
  Standard_EXPORT const TopoDS_Shell& Shell();
  Standard_EXPORT                     operator TopoDS_Shell();

  //! Returns the constructed rotational primitive as a solid.
  Standard_EXPORT const TopoDS_Solid& Solid();
  Standard_EXPORT                     operator TopoDS_Solid();
};
