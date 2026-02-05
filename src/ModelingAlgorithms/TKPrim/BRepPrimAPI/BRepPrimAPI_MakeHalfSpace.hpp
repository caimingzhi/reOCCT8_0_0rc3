#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Solid.hpp>
#include <BRepBuilderAPI_MakeShape.hpp>
class TopoDS_Face;
class gp_Pnt;
class TopoDS_Shell;

//! Describes functions to build half-spaces.
//! A half-space is an infinite solid, limited by a surface. It
//! is built from a face or a shell, which bounds it, and with
//! a reference point, which specifies the side of the
//! surface where the matter of the half-space is located.
//! A half-space is a tool commonly used in topological
//! operations to cut another shape.
//! A MakeHalfSpace object provides a framework for:
//! -   defining and implementing the construction of a half-space, and
//! -   consulting the result.
class BRepPrimAPI_MakeHalfSpace : public BRepBuilderAPI_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  //! Make a HalfSpace defined with a Face and a Point.
  Standard_EXPORT BRepPrimAPI_MakeHalfSpace(const TopoDS_Face& Face, const gp_Pnt& RefPnt);

  //! Make a HalfSpace defined with a Shell and a Point.
  Standard_EXPORT BRepPrimAPI_MakeHalfSpace(const TopoDS_Shell& Shell, const gp_Pnt& RefPnt);

  //! Returns the constructed half-space as a solid.
  Standard_EXPORT const TopoDS_Solid& Solid() const;
  Standard_EXPORT                     operator TopoDS_Solid() const;

private:
  TopoDS_Solid mySolid;
};
