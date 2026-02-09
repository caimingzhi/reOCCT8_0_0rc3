#include <gce_MakeScale2d.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Trsf2d.hpp>

gce_MakeScale2d::gce_MakeScale2d(const gp_Pnt2d& Point, const double Scale)
{
  TheScale2d.SetScale(Point, Scale);
}

const gp_Trsf2d& gce_MakeScale2d::Value() const
{
  return TheScale2d;
}

const gp_Trsf2d& gce_MakeScale2d::Operator() const
{
  return TheScale2d;
}

gce_MakeScale2d::operator gp_Trsf2d() const
{
  return TheScale2d;
}
