#include <GCE2d_MakeRotation.hpp>
#include <Geom2d_Transformation.hpp>
#include <gp_Pnt2d.hpp>

GCE2d_MakeRotation::GCE2d_MakeRotation(const gp_Pnt2d& Point, const double Angle)
{
  TheRotation = new Geom2d_Transformation();
  TheRotation->SetRotation(Point, Angle);
}

const occ::handle<Geom2d_Transformation>& GCE2d_MakeRotation::Value() const
{
  return TheRotation;
}
