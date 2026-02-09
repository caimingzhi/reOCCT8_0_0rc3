#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Geom2dInt_IntConicCurveOfGInter.hpp>
class gp_Lin2d;
class BRepClass_Edge;
class gp_Dir2d;

class BRepClass_Intersector : public Geom2dInt_IntConicCurveOfGInter
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepClass_Intersector();

  Standard_EXPORT void Perform(const gp_Lin2d&       L,
                               const double          P,
                               const double          Tol,
                               const BRepClass_Edge& E);

  Standard_EXPORT void LocalGeometry(const BRepClass_Edge& E,
                                     const double          U,
                                     gp_Dir2d&             T,
                                     gp_Dir2d&             N,
                                     double&               C) const;
};
