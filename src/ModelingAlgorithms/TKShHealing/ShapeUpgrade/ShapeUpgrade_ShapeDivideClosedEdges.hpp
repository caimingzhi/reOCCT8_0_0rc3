#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <ShapeUpgrade_ShapeDivide.hpp>
#include <Standard_Integer.hpp>
class TopoDS_Shape;

class ShapeUpgrade_ShapeDivideClosedEdges : public ShapeUpgrade_ShapeDivide
{
public:
  DEFINE_STANDARD_ALLOC

  //! Initialises tool with shape and default parameter.
  Standard_EXPORT ShapeUpgrade_ShapeDivideClosedEdges(const TopoDS_Shape& S);

  //! Sets the number of cuts applied to divide closed edges.
  //! The number of resulting faces will be num+1.
  Standard_EXPORT void SetNbSplitPoints(const int num);
};

