#pragma once


#include <IntPatch_CSFunction.hpp>

class Adaptor3d_HSurfaceTool;
class IntPatch_HCurve2dTool;
class math_FunctionSetRoot;

class IntPatch_CurvIntSurf
{
public:
  DEFINE_STANDARD_ALLOC

  //! compute the solution point with the close point
  //! MarginCoef is the coefficient for extension of UV bounds.
  //! Ex., UFirst -= MarginCoef*(ULast-UFirst)
  Standard_EXPORT IntPatch_CurvIntSurf(const double               U,
                                       const double               V,
                                       const double               W,
                                       const IntPatch_CSFunction& F,
                                       const double               TolTangency,
                                       const double               MarginCoef = 0.0);

  //! initialize the parameters to compute the solution
  Standard_EXPORT IntPatch_CurvIntSurf(const IntPatch_CSFunction& F, const double TolTangency);

  //! compute the solution
  //! it's possible to write to optimize:
  //! IntImp_IntCS inter(S1,C1,Toltangency)
  //! math_FunctionSetRoot rsnld(Inter.function())
  //! while ...{
  //! u=...
  //! v=...
  //! w=...
  //! inter.Perform(u,v,w,rsnld)
  //! }
  //! or
  //! IntImp_IntCS inter(Toltangency)
  //! inter.SetSurface(S);
  //! math_FunctionSetRoot rsnld(Inter.function())
  //! while ...{
  //! C=...
  //! inter.SetCurve(C);
  //! u=...
  //! v=...
  //! w=...
  //! inter.Perform(u,v,w,rsnld)
  //! }
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

  //! Returns TRUE if the creation completed without failure.
  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT bool IsEmpty() const;

  //! returns the intersection point
  //! The exception NotDone is raised if IsDone is false.
  //! The exception DomainError is raised if IsEmpty is true.
  Standard_EXPORT const gp_Pnt& Point() const;

  Standard_EXPORT double ParameterOnCurve() const;

  Standard_EXPORT void ParameterOnSurface(double& U, double& V) const;

  //! return the math function which
  //! is used to compute the intersection
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

