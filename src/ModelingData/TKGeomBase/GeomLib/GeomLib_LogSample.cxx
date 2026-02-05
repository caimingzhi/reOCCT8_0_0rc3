#include <GeomLib_LogSample.hpp>
#include <Standard_OutOfRange.hpp>

GeomLib_LogSample::GeomLib_LogSample(const double A, const double B, const int N)
    : math_FunctionSample(A, B, N)
{
  myF   = A - 1;
  myexp = std::log(B - A) / N;
}

double GeomLib_LogSample::GetParameter(const int Index) const
{
  int aN = NbPoints();

  if ((Index >= aN) || (Index <= 1))
  {
    double aA, aB;
    Bounds(aA, aB);
    if (Index == 1)
      return aA;
    else if (Index == aN)
      return aB;
    else
      throw Standard_OutOfRange("GeomLib_LogSample::GetParameter");
  }

  double v = myF + std::exp(myexp * Index);
  return v;
}
