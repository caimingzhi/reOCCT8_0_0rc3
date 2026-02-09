#pragma once

#include <Adaptor3d_Surface.hpp>
#include <IntCurveSurface_TheCSFunctionOfHInter.hpp>

class Adaptor3d_HSurfaceTool;
class IntCurveSurface_TheHCurveTool;
class IntCurveSurface_TheCSFunctionOfHInter;
class math_FunctionSetRoot;

class IntCurveSurface_TheExactHInter
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntCurveSurface_TheExactHInter(const double                                 U,
                                                 const double                                 V,
                                                 const double                                 W,
                                                 const IntCurveSurface_TheCSFunctionOfHInter& F,
                                                 const double TolTangency,
                                                 const double MarginCoef = 0.0);

  Standard_EXPORT IntCurveSurface_TheExactHInter(const IntCurveSurface_TheCSFunctionOfHInter& F,
                                                 const double TolTangency);

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

  Standard_EXPORT IntCurveSurface_TheCSFunctionOfHInter& Function();

private:
  bool                                  done;
  bool                                  empty;
  IntCurveSurface_TheCSFunctionOfHInter myFunction;
  double                                w;
  double                                u;
  double                                v;
  double                                tol;
};
