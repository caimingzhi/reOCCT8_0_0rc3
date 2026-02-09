#pragma once

#include <IntPatch_CSFunction.hpp>

class Adaptor3d_HSurfaceTool;
class IntPatch_HCurve2dTool;
class math_FunctionSetRoot;

class IntPatch_CurvIntSurf
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntPatch_CurvIntSurf(const double               U,
                                       const double               V,
                                       const double               W,
                                       const IntPatch_CSFunction& F,
                                       const double               TolTangency,
                                       const double               MarginCoef = 0.0);

  Standard_EXPORT IntPatch_CurvIntSurf(const IntPatch_CSFunction& F, const double TolTangency);

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

  Standard_EXPORT IntPatch_CSFunction& Function();

private:
  bool                done;
  bool                empty;
  IntPatch_CSFunction myFunction;
  double              w;
  double              u;
  double              v;
  double              tol;
};
