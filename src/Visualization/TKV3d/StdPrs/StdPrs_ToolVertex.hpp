#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

class TopoDS_Vertex;

class StdPrs_ToolVertex
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Coord(const TopoDS_Vertex& aPoint, double& X, double& Y, double& Z);
};
