#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <math_MultipleVarFunctionWithGradient.hpp>
#include <Adaptor3d_Surface.hpp>

#include <Standard_Boolean.hpp>

template <typename T>
class math_VectorBase;
using math_Vector = math_VectorBase<double>;

class Extrema_FuncPSDist : public math_MultipleVarFunctionWithGradient
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Extrema_FuncPSDist(const Adaptor3d_Surface& theS, const gp_Pnt& theP);

  Standard_EXPORT int NbVariables() const override;

  Standard_EXPORT bool Value(const math_Vector& X, double& F) override;

  Standard_EXPORT bool Gradient(const math_Vector& X, math_Vector& G) override;

  Standard_EXPORT bool Values(const math_Vector& X, double& F, math_Vector& G) override;

private:
  bool IsInside(const math_Vector& X);

  const Extrema_FuncPSDist& operator=(const Extrema_FuncPSDist&) = delete;
  Extrema_FuncPSDist(const Extrema_FuncPSDist&)                  = delete;

  const Adaptor3d_Surface& mySurf;
  const gp_Pnt&            myP;
};
