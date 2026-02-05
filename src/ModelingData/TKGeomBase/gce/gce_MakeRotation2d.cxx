#include <gce_MakeRotation2d.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Trsf2d.hpp>

//=========================================================================
//   Creation d une rotation 2d de gp d angle Angle par rapport a un      +
//   point Point.                                                         +
//=========================================================================
gce_MakeRotation2d::gce_MakeRotation2d(const gp_Pnt2d& Point, const double Angle)
{
  TheRotation2d.SetRotation(Point, Angle);
}

const gp_Trsf2d& gce_MakeRotation2d::Value() const
{
  return TheRotation2d;
}

const gp_Trsf2d& gce_MakeRotation2d::Operator() const
{
  return TheRotation2d;
}

gce_MakeRotation2d::operator gp_Trsf2d() const
{
  return TheRotation2d;
}
