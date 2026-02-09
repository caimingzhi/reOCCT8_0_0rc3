#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

class IntCurve_PConic;
class gp_Pnt2d;

class IntCurve_ProjectOnPConicTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static double FindParameter(const IntCurve_PConic& C,
                                              const gp_Pnt2d&        Pnt,
                                              const double           Tol);

  Standard_EXPORT static double FindParameter(const IntCurve_PConic& C,
                                              const gp_Pnt2d&        Pnt,
                                              const double           LowParameter,
                                              const double           HighParameter,
                                              const double           Tol);
};
