#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <math_FunctionSetWithDerivatives.hpp>
#include <math_Vector.hpp>

class math_Matrix;
class gp_Pnt2d;

class ProjLib_PrjFunc : public math_FunctionSetWithDerivatives
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ProjLib_PrjFunc(const Adaptor3d_Curve*   C,
                                  const double             FixVal,
                                  const Adaptor3d_Surface* S,
                                  const int                Fix);

  Standard_EXPORT int NbVariables() const override;

  Standard_EXPORT int NbEquations() const override;

  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F) override;

  Standard_EXPORT bool Derivatives(const math_Vector& X, math_Matrix& D) override;

  Standard_EXPORT bool Values(const math_Vector& X, math_Vector& F, math_Matrix& D) override;

  Standard_EXPORT gp_Pnt2d Solution() const;

private:
  const Adaptor3d_Curve*   myCurve;
  const Adaptor3d_Surface* mySurface;
  double                   myt;
  double                   myU;
  double                   myV;
  int                      myFix;
  double                   myNorm;
};
