#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class ShapeFix_Shape;
class ShapeFix_EdgeProjAux;

//! Returns tools used by AlgoContainer
class ShapeAlgo_ToolContainer : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT ShapeAlgo_ToolContainer();

  //! Returns ShapeFix_Shape
  Standard_EXPORT virtual occ::handle<ShapeFix_Shape> FixShape() const;

  //! Returns ShapeFix_EdgeProjAux
  Standard_EXPORT virtual occ::handle<ShapeFix_EdgeProjAux> EdgeProjAux() const;

  DEFINE_STANDARD_RTTIEXT(ShapeAlgo_ToolContainer, Standard_Transient)
};

