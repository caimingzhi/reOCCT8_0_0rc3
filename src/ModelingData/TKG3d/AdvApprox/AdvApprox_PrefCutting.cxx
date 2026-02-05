#include <AdvApprox_PrefCutting.hpp>
#include <Precision.hpp>

AdvApprox_PrefCutting::AdvApprox_PrefCutting(const NCollection_Array1<double>& CutPnts)
    : myPntOfCutting(1, CutPnts.Length())
{
  myPntOfCutting = CutPnts;
}

bool AdvApprox_PrefCutting::Value(const double a, const double b, double& cuttingvalue) const
{
  //  longueur minimum d'un intervalle parametrique : PConfusion()
  //                                    pour F(U,V) : EPS1=1.e-9 (cf.MMEPS1)
  constexpr double lgmin = 10 * Precision::PConfusion();
  int              i;
  double           cut, mil = (a + b) / 2, dist = std::abs((a - b) / 2);
  cut = mil;
  for (i = myPntOfCutting.Lower(); i <= myPntOfCutting.Upper(); i++)
  {
    if ((dist - lgmin) > std::abs(mil - myPntOfCutting.Value(i)))
    {
      cut  = myPntOfCutting.Value(i);
      dist = std::abs(mil - myPntOfCutting.Value(i));
    }
  }
  cuttingvalue = cut;
  return (std::abs(cut - a) >= lgmin && std::abs(b - cut) >= lgmin);
}
