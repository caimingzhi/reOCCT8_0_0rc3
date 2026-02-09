#pragma once

#include <HLRBRep_TheCurveLocatorOfTheProjPCurOfCInter.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <HLRBRep_TypeDef.hpp>
#include <Standard_Real.hpp>
class HLRBRep_CurveTool;
class gp_Pnt2d;

class HLRBRep_TheProjPCurOfCInter
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static double FindParameter(const HLRBRep_CurvePtr& C,
                                              const gp_Pnt2d&         Pnt,
                                              const double            Tol);

  Standard_EXPORT static double FindParameter(const HLRBRep_CurvePtr& C,
                                              const gp_Pnt2d&         Pnt,
                                              const double            LowParameter,
                                              const double            HighParameter,
                                              const double            Tol);
};
