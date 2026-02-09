#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopAbs_ShapeEnum.hpp>
class TopoDS_Shape;

class ShapeFix_ShapeTolerance
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ShapeFix_ShapeTolerance();

  Standard_EXPORT bool LimitTolerance(const TopoDS_Shape&    shape,
                                      const double           tmin,
                                      const double           tmax = 0.0,
                                      const TopAbs_ShapeEnum styp = TopAbs_SHAPE) const;

  Standard_EXPORT void SetTolerance(const TopoDS_Shape&    shape,
                                    const double           preci,
                                    const TopAbs_ShapeEnum styp = TopAbs_SHAPE) const;
};
