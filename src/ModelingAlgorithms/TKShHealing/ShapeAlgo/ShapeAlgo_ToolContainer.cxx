#include <ShapeAlgo_ToolContainer.hpp>
#include <ShapeFix_EdgeProjAux.hpp>
#include <ShapeFix_Shape.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ShapeAlgo_ToolContainer, Standard_Transient)

//=================================================================================================

ShapeAlgo_ToolContainer::ShapeAlgo_ToolContainer() = default;

//=================================================================================================

occ::handle<ShapeFix_Shape> ShapeAlgo_ToolContainer::FixShape() const
{
  return new ShapeFix_Shape;
}

//=================================================================================================

occ::handle<ShapeFix_EdgeProjAux> ShapeAlgo_ToolContainer::EdgeProjAux() const
{
  return new ShapeFix_EdgeProjAux;
}
