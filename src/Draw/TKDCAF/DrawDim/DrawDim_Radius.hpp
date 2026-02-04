#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Face.hpp>
#include <DrawDim_Dimension.hpp>
class Draw_Display;

class DrawDim_Radius : public DrawDim_Dimension
{

public:
  Standard_EXPORT DrawDim_Radius(const TopoDS_Face& cylinder);

  Standard_EXPORT const TopoDS_Face& Cylinder() const;

  Standard_EXPORT void Cylinder(const TopoDS_Face& face);

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  DEFINE_STANDARD_RTTIEXT(DrawDim_Radius, DrawDim_Dimension)

private:
  TopoDS_Face myCylinder;
};

