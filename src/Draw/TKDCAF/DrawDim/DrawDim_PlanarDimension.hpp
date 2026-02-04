#pragma once


#include <Standard.hpp>

#include <TopoDS_Face.hpp>
#include <DrawDim_Dimension.hpp>

//! Dimensions between point, line and circle ON a plane
class DrawDim_PlanarDimension : public DrawDim_Dimension
{

public:
  Standard_EXPORT void SetPlane(const TopoDS_Face& plane);

  Standard_EXPORT TopoDS_Face GetPlane() const;

  DEFINE_STANDARD_RTTIEXT(DrawDim_PlanarDimension, DrawDim_Dimension)

protected:
  TopoDS_Face myPlane;
};

