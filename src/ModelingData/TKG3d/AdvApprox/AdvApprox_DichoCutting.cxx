#include <AdvApprox_DichoCutting.hpp>
#include <Precision.hpp>

AdvApprox_DichoCutting::AdvApprox_DichoCutting() = default;

bool AdvApprox_DichoCutting::Value(const double a, const double b, double& cuttingvalue) const
{
  // longueur minimum d'un intervalle pour F(U,V) : EPS1=1.e-9 (cf.MEPS1)
  constexpr double lgmin = 10 * Precision::PConfusion();
  cuttingvalue           = (a + b) / 2;
  return (std::abs(b - a) >= 2 * lgmin);
}
