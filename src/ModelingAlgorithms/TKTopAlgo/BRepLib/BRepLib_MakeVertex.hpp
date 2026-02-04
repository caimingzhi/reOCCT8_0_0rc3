#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <BRepLib_MakeShape.hpp>
class gp_Pnt;
class TopoDS_Vertex;

//! Provides methods to build vertices.
class BRepLib_MakeVertex : public BRepLib_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepLib_MakeVertex(const gp_Pnt& P);

  Standard_EXPORT const TopoDS_Vertex& Vertex();
  Standard_EXPORT                      operator TopoDS_Vertex();
};

