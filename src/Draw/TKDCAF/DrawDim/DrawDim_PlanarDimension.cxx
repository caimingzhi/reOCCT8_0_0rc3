#include <Draw_Interpretor.hpp>
#include <DrawDim_PlanarDimension.hpp>
#include <Standard_Type.hpp>
#include <TopoDS_Face.hpp>

IMPLEMENT_STANDARD_RTTIEXT(DrawDim_PlanarDimension, DrawDim_Dimension)

void DrawDim_PlanarDimension::SetPlane(const TopoDS_Face& plane)
{
  myPlane = plane;
}

TopoDS_Face DrawDim_PlanarDimension::GetPlane() const
{
  return myPlane;
}
