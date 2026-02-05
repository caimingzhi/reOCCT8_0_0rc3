#include <Plate_SampledCurveConstraint.hpp>
#include <Plate_PinpointConstraint.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_DimensionMismatch.hpp>

static inline double B0(double t)
{
  double s = t;
  if (s < 0.)
    s = -s;
  s = 1. - s;
  if (s < 0.)
    s = 0;
  return s;
}

Plate_SampledCurveConstraint::Plate_SampledCurveConstraint(
  const NCollection_Sequence<Plate_PinpointConstraint>& SOPPC,
  const int                                             n)
    : myLXYZC(n, SOPPC.Length())
{
  int m = SOPPC.Length();

  if (n > m)
    throw Standard_DimensionMismatch();
  for (int index = 1; index <= m; index++)
    myLXYZC.SetPPC(index, SOPPC(index));

  double ratio = double(n + 1) / double(m + 1);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
    {
      myLXYZC.SetCoeff(i, j, B0(ratio * j - i));
    }
}
