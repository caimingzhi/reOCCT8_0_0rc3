#include <Plate_D2.hpp>

Plate_D2::Plate_D2(const gp_XYZ& duu, const gp_XYZ& duv, const gp_XYZ& dvv)
    : Duu(duu),
      Duv(duv),
      Dvv(dvv)
{
}

Plate_D2::Plate_D2(const Plate_D2& ref)

  = default;
