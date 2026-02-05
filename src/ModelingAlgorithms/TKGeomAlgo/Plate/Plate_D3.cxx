#include <Plate_D3.hpp>

Plate_D3::Plate_D3(const gp_XYZ& duuu, const gp_XYZ& duuv, const gp_XYZ& duvv, const gp_XYZ& dvvv)
    : Duuu(duuu),
      Duuv(duuv),
      Duvv(duvv),
      Dvvv(dvvv)
{
}

Plate_D3::Plate_D3(const Plate_D3& ref)

  = default;
