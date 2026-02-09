#pragma once

#include <Geom2dInt_TheCurveLocatorOfTheProjPCurOfGInter.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

class Adaptor2d_Curve2d;
class Geom2dInt_Geom2dCurveTool;
class gp_Pnt2d;

class Geom2dInt_TheProjPCurOfGInter
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static double FindParameter(const Adaptor2d_Curve2d& C,
                                              const gp_Pnt2d&          Pnt,
                                              const double             Tol);

  Standard_EXPORT static double FindParameter(const Adaptor2d_Curve2d& C,
                                              const gp_Pnt2d&          Pnt,
                                              const double             LowParameter,
                                              const double             HighParameter,
                                              const double             Tol);
};
