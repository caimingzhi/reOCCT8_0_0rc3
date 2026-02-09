#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <NCollection_Array1.hpp>
#include <math_FunctionWithDerivative.hpp>

class CSLib_NormalPolyDef : public math_FunctionWithDerivative
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT CSLib_NormalPolyDef(int theK0, const NCollection_Array1<double>& theLi);

  Standard_EXPORT bool Value(const double theX, double& theF) override;

  Standard_EXPORT bool Derivative(const double theX, double& theD) override;

  Standard_EXPORT bool Values(const double theX, double& theF, double& theD) override;

private:
  int                        myK0;
  NCollection_Array1<double> myTABli;
};
