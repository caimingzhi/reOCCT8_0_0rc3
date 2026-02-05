#include <Plate_PinpointConstraint.hpp>

Plate_PinpointConstraint::Plate_PinpointConstraint()
{
  pnt2d = gp_XY(0, 0);
  value = gp_XYZ(0, 0, 0);
  idu   = 0;
  idv   = 0;
}

Plate_PinpointConstraint::Plate_PinpointConstraint(const gp_XY&  point2d,
                                                   const gp_XYZ& ImposedValue,
                                                   const int     iu,
                                                   const int     iv)
{
  pnt2d = point2d;
  value = ImposedValue;
  idu   = iu;
  idv   = iv;
}
