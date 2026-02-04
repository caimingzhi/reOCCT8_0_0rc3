#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class Geom_Plane;

//! This package provides basic building tools for other packages in ShapeHealing.
//! These tools are rather internal for ShapeHealing .
class ShapeBuild
{
public:
  DEFINE_STANDARD_ALLOC

  //! Rebuilds a shape with substitution of some components
  //! Returns a Geom_Surface which is the Plane XOY (Z positive)
  //! This allows to consider an UV space homologous to a 3D space,
  //! with this support surface
  Standard_EXPORT static occ::handle<Geom_Plane> PlaneXOY();
};

