#include <gce_MakeScale.hpp>
#include <gp_Pnt.hpp>
#include <gp_Trsf.hpp>

gce_MakeScale::gce_MakeScale(const gp_Pnt& Point, const double Scale)
{
  TheScale.SetScale(Point, Scale);
}

const gp_Trsf& gce_MakeScale::Value() const
{
  return TheScale;
}

const gp_Trsf& gce_MakeScale::Operator() const
{
  return TheScale;
}

gce_MakeScale::operator gp_Trsf() const
{
  return TheScale;
}
