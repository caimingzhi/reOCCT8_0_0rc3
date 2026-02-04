#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Face.hpp>
#include <DrawDim_Dimension.hpp>
class Draw_Display;

class DrawDim_Angle : public DrawDim_Dimension
{

public:
  Standard_EXPORT DrawDim_Angle(const TopoDS_Face& plane1, const TopoDS_Face& plane2);

  Standard_EXPORT const TopoDS_Face& Plane1() const;

  Standard_EXPORT void Plane1(const TopoDS_Face& plane);

  Standard_EXPORT const TopoDS_Face& Plane2() const;

  Standard_EXPORT void Plane2(const TopoDS_Face& plane);

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  DEFINE_STANDARD_RTTIEXT(DrawDim_Angle, DrawDim_Dimension)

private:
  TopoDS_Face myPlane1;
  TopoDS_Face myPlane2;
};

