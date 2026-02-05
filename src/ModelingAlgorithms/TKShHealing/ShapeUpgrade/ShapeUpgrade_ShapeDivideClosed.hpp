#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <ShapeUpgrade_ShapeDivide.hpp>
#include <Standard_Integer.hpp>
class TopoDS_Shape;

//! Divides all closed faces in the shape. Class
//! ShapeUpgrade_ClosedFaceDivide is used as divide tool.
class ShapeUpgrade_ShapeDivideClosed : public ShapeUpgrade_ShapeDivide
{
public:
  DEFINE_STANDARD_ALLOC

  //! Initialises tool with shape and default parameter.
  Standard_EXPORT ShapeUpgrade_ShapeDivideClosed(const TopoDS_Shape& S);

  //! Sets the number of cuts applied to divide closed faces.
  //! The number of resulting faces will be num+1.
  Standard_EXPORT void SetNbSplitPoints(const int num);
};
