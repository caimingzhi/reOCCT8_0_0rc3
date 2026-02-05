#include <gp_Pln.hpp>
#include <gp_XY.hpp>
#include <Plate_PinpointConstraint.hpp>
#include <Plate_PlaneConstraint.hpp>

Plate_PlaneConstraint::Plate_PlaneConstraint(const gp_XY&  point2d,
                                             const gp_Pln& pln,
                                             const int     iu,
                                             const int     iv)
    : myLSC(1, 1)
{
  gp_XYZ point = pln.Location().XYZ();
  myLSC.SetPPC(1, Plate_PinpointConstraint(point2d, point, iu, iv));
  gp_XYZ dir = pln.Axis().Direction().XYZ();
  dir.Normalize();
  myLSC.SetCoeff(1, 1, dir);
}
