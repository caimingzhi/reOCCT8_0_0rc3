#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Face.hpp>
#include <DrawDim_Dimension.hpp>
class Draw_Display;

class DrawDim_Distance : public DrawDim_Dimension
{

public:
  Standard_EXPORT DrawDim_Distance(const TopoDS_Face& plane1, const TopoDS_Face& plane2);

  Standard_EXPORT DrawDim_Distance(const TopoDS_Face& plane1);

  Standard_EXPORT const TopoDS_Face& Plane1() const;

  Standard_EXPORT void Plane1(const TopoDS_Face& face);

  Standard_EXPORT const TopoDS_Face& Plane2() const;

  Standard_EXPORT void Plane2(const TopoDS_Face& face);

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  DEFINE_STANDARD_RTTIEXT(DrawDim_Distance, DrawDim_Dimension)

private:
  TopoDS_Face myPlane1;
  TopoDS_Face myPlane2;
};

