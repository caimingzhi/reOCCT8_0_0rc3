#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <BRepBuilderAPI_ModifyShape.hpp>

class TopoDS_Shape;

//! Duplication of a shape.
//! A Copy object provides a framework for:
//! -   defining the construction of a duplicate shape,
//! -   implementing the construction algorithm, and
//! -   consulting the result.
class BRepBuilderAPI_Copy : public BRepBuilderAPI_ModifyShape
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructs an empty copy framework. Use the function
  //! Perform to copy shapes.
  Standard_EXPORT BRepBuilderAPI_Copy();

  //! Constructs a copy framework and copies the shape S.
  //! Use the function Shape to access the result.
  //! If copyMesh is True, triangulation contained in original shape will be
  //! copied along with geometry (by default, triangulation gets lost).
  //! If copyGeom is False, only topological objects will be copied, while
  //! geometry and triangulation will be shared with original shape.
  //! Note: the constructed framework can be reused to copy
  //! other shapes: just specify them with the function Perform.
  Standard_EXPORT BRepBuilderAPI_Copy(const TopoDS_Shape& S,
                                      const bool          copyGeom = true,
                                      const bool          copyMesh = false);

  //! Copies the shape S.
  //! Use the function Shape to access the result.
  //! If copyMesh is True, triangulation contained in original shape will be
  //! copied along with geometry (by default, triangulation gets lost).
  //! If copyGeom is False, only topological objects will be copied, while
  //! geometry and triangulation will be shared with original shape.
  Standard_EXPORT void Perform(const TopoDS_Shape& S,
                               const bool          copyGeom = true,
                               const bool          copyMesh = false);
};
