#include <Plate_D1.hpp>
#include <Plate_GtoCConstraint.hpp>

Plate_D1::Plate_D1(const gp_XYZ& du, const gp_XYZ& dv)
    : Du(du),
      Dv(dv)
{
}

Plate_D1::Plate_D1(const Plate_D1& ref)

  = default;
