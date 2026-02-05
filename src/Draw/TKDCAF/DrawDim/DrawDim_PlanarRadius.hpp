#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <DrawDim_PlanarDimension.hpp>
class TopoDS_Face;
class Draw_Display;

class DrawDim_PlanarRadius : public DrawDim_PlanarDimension
{

public:
  Standard_EXPORT DrawDim_PlanarRadius(const TopoDS_Face& plane, const TopoDS_Shape& circle);

  Standard_EXPORT DrawDim_PlanarRadius(const TopoDS_Shape& circle);

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  DEFINE_STANDARD_RTTIEXT(DrawDim_PlanarRadius, DrawDim_PlanarDimension)

private:
  TopoDS_Shape myCircle;
};
