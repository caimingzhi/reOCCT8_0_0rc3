#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <DrawDim_PlanarDimension.hpp>
class TopoDS_Face;
class Draw_Display;
class gp_Pnt;
class TopoDS_Edge;

class DrawDim_PlanarDistance : public DrawDim_PlanarDimension
{

public:
  Standard_EXPORT DrawDim_PlanarDistance(const TopoDS_Face&  plane,
                                         const TopoDS_Shape& point1,
                                         const TopoDS_Shape& point2);

  Standard_EXPORT DrawDim_PlanarDistance(const TopoDS_Shape& geom1, const TopoDS_Shape& geom2);

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  DEFINE_STANDARD_RTTIEXT(DrawDim_PlanarDistance, DrawDim_PlanarDimension)

private:
  Standard_EXPORT void Draw(const gp_Pnt& p, const TopoDS_Edge& e, Draw_Display& d) const;

  TopoDS_Shape myGeom1;
  TopoDS_Shape myGeom2;
};
