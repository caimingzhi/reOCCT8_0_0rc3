#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Shape.hpp>
#include <DrawDim_PlanarDimension.hpp>
class TopoDS_Face;
class Draw_Display;

class DrawDim_PlanarAngle : public DrawDim_PlanarDimension
{

public:
  Standard_EXPORT DrawDim_PlanarAngle(const TopoDS_Face&  plane,
                                      const TopoDS_Shape& line1,
                                      const TopoDS_Shape& line2);

  Standard_EXPORT DrawDim_PlanarAngle(const TopoDS_Shape& line1, const TopoDS_Shape& line2);

  Standard_EXPORT void Sector(const bool inverted, const bool reversed);

  Standard_EXPORT void Position(const double value);

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  DEFINE_STANDARD_RTTIEXT(DrawDim_PlanarAngle, DrawDim_PlanarDimension)

private:
  TopoDS_Shape myLine1;
  TopoDS_Shape myLine2;
  bool         myIsReversed;
  bool         myIsInverted;
  double       myPosition;
};
