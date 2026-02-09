#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepLib_MakeVertex.hpp>
#include <BRepBuilderAPI_MakeShape.hpp>
class gp_Pnt;
class TopoDS_Vertex;

class BRepBuilderAPI_MakeVertex : public BRepBuilderAPI_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepBuilderAPI_MakeVertex(const gp_Pnt& P);

  Standard_EXPORT const TopoDS_Vertex& Vertex();
  Standard_EXPORT                      operator TopoDS_Vertex();

private:
  BRepLib_MakeVertex myMakeVertex;
};
