#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <HLRBRep_TheCSFunctionOfInterCSurf.hpp>
class StdFail_NotDone;
class Standard_DomainError;
class HLRBRep_SurfaceTool;
class gp_Lin;
class HLRBRep_LineTool;
class HLRBRep_TheCSFunctionOfInterCSurf;
class math_FunctionSetRoot;
class gp_Pnt;

class HLRBRep_TheExactInterCSurf
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT HLRBRep_TheExactInterCSurf(const double                             U,
                                             const double                             V,
                                             const double                             W,
                                             const HLRBRep_TheCSFunctionOfInterCSurf& F,
                                             const double                             TolTangency,
                                             const double MarginCoef = 0.0);

  Standard_EXPORT HLRBRep_TheExactInterCSurf(const HLRBRep_TheCSFunctionOfInterCSurf& F,
                                             const double                             TolTangency);

  Standard_EXPORT void Perform(const double          U,
                               const double          V,
                               const double          W,
                               math_FunctionSetRoot& Rsnld,
                               const double          u0,
                               const double          v0,
                               const double          u1,
                               const double          v1,
                               const double          w0,
                               const double          w1);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT bool IsEmpty() const;

  Standard_EXPORT const gp_Pnt& Point() const;

  Standard_EXPORT double ParameterOnCurve() const;

  Standard_EXPORT void ParameterOnSurface(double& U, double& V) const;

  Standard_EXPORT HLRBRep_TheCSFunctionOfInterCSurf& Function();

private:
  bool                              done;
  bool                              empty;
  HLRBRep_TheCSFunctionOfInterCSurf myFunction;
  double                            w;
  double                            u;
  double                            v;
  double                            tol;
};
