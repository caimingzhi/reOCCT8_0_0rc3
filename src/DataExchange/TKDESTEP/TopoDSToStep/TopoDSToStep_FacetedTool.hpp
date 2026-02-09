#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

enum TopoDSToStep_FacetedError
{
  TopoDSToStep_FacetedDone,
  TopoDSToStep_SurfaceNotPlane,
  TopoDSToStep_PCurveNotLinear
};

class TopoDS_Shape;

class TopoDSToStep_FacetedTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static TopoDSToStep_FacetedError CheckTopoDSShape(const TopoDS_Shape& SH);
};
