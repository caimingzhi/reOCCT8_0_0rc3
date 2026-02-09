#include <gce_MakeRotation.hpp>
#include <gp_Dir.hpp>
#include <gp_Lin.hpp>
#include <gp_Pnt.hpp>
#include <gp_Trsf.hpp>

gce_MakeRotation::gce_MakeRotation(const gp_Lin& Line, const double Angle)
{
  TheRotation.SetRotation(gp_Ax1(Line.Position()), Angle);
}

gce_MakeRotation::gce_MakeRotation(const gp_Ax1& Axis, const double Angle)
{
  TheRotation.SetRotation(Axis, Angle);
}

gce_MakeRotation::gce_MakeRotation(const gp_Pnt& Point, const gp_Dir& Direc, const double Angle)
{
  TheRotation.SetRotation(gp_Ax1(Point, Direc), Angle);
}

const gp_Trsf& gce_MakeRotation::Value() const
{
  return TheRotation;
}

const gp_Trsf& gce_MakeRotation::Operator() const
{
  return TheRotation;
}

gce_MakeRotation::operator gp_Trsf() const
{
  return TheRotation;
}
