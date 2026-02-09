#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class ShapeFix_Shape;
class ShapeFix_EdgeProjAux;

class ShapeAlgo_ToolContainer : public Standard_Transient
{

public:
  Standard_EXPORT ShapeAlgo_ToolContainer();

  Standard_EXPORT virtual occ::handle<ShapeFix_Shape> FixShape() const;

  Standard_EXPORT virtual occ::handle<ShapeFix_EdgeProjAux> EdgeProjAux() const;

  DEFINE_STANDARD_RTTIEXT(ShapeAlgo_ToolContainer, Standard_Transient)
};
