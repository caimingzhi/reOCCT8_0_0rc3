

#define No_Standard_RangeError
#define No_Standard_OutOfRange
#define No_Standard_DimensionError

#include <math_FunctionSample.hpp>
#include <Standard_OutOfRange.hpp>

math_FunctionSample::math_FunctionSample(const double A, const double B, const int N)
    : a(A),
      b(B),
      n(N)
{
}

void math_FunctionSample::Bounds(double& A, double& B) const
{

  A = a;
  B = b;
}

int math_FunctionSample::NbPoints() const
{
  return n;
}

double math_FunctionSample::GetParameter(const int Index) const
{
  Standard_OutOfRange_Raise_if((Index <= 0) || (Index > n), " ");
  return ((n - Index) * a + (Index - 1) * b) / (n - 1);
}
