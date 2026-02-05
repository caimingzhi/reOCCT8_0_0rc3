#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <Standard_OStream.hpp>

//! defines a Cube node of VRML specifying geometry shapes.
//! This node represents a cuboid aligned with the coordinate axes.
//! By default, the cube is centred at (0,0,0) and measures 2 units
//! in each dimension, from -1 to +1.
//! A cube's width is its extent along its object-space X axis, its height is
//! its extent along the object-space Y axis, and its depth is its extent along its
//! object-space Z axis.
class Vrml_Cube
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Vrml_Cube(const double aWidth  = 2,
                            const double aHeight = 2,
                            const double aDepth  = 2);

  Standard_EXPORT void SetWidth(const double aWidth);

  Standard_EXPORT double Width() const;

  Standard_EXPORT void SetHeight(const double aHeight);

  Standard_EXPORT double Height() const;

  Standard_EXPORT void SetDepth(const double aDepth);

  Standard_EXPORT double Depth() const;

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream) const;

private:
  double myWidth;
  double myHeight;
  double myDepth;
};
