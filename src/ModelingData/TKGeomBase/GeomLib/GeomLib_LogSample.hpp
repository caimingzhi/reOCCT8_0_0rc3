#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <math_FunctionSample.hpp>

class GeomLib_LogSample : public math_FunctionSample
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomLib_LogSample(const double A, const double B, const int N);

  Standard_EXPORT double GetParameter(const int Index) const override;

private:
  double myF;
  double myexp;
};
