#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

class TopoDS_Vertex;
class gp_Pnt;

class ShapeBuild_Vertex
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopoDS_Vertex CombineVertex(const TopoDS_Vertex& V1,
                                              const TopoDS_Vertex& V2,
                                              const double         tolFactor = 1.0001) const;

  Standard_EXPORT TopoDS_Vertex CombineVertex(const gp_Pnt& pnt1,
                                              const gp_Pnt& pnt2,
                                              const double  tol1,
                                              const double  tol2,
                                              const double  tolFactor = 1.0001) const;
};
