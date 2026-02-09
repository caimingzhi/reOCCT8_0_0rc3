#include <GCE2d_MakeScale.hpp>
#include <Geom2d_Transformation.hpp>
#include <gp_Pnt2d.hpp>

GCE2d_MakeScale::GCE2d_MakeScale(const gp_Pnt2d& Point, const double Scale)
{
  TheScale = new Geom2d_Transformation();
  TheScale->SetScale(Point, Scale);
}

const occ::handle<Geom2d_Transformation>& GCE2d_MakeScale::Value() const
{
  return TheScale;
}
