#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>

class math_FunctionSample
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT math_FunctionSample(const double A, const double B, const int N);

  Standard_EXPORT virtual void Bounds(double& A, double& B) const;

  Standard_EXPORT int NbPoints() const;

  Standard_EXPORT virtual double GetParameter(const int Index) const;

private:
  double a;
  double b;
  int    n;
};
