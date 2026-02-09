#include <GCE2d_MakeTranslation.hpp>
#include <Geom2d_Transformation.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>

GCE2d_MakeTranslation::GCE2d_MakeTranslation(const gp_Vec2d& Vec)
{
  TheTranslation = new Geom2d_Transformation();
  TheTranslation->SetTranslation(Vec);
}

GCE2d_MakeTranslation::GCE2d_MakeTranslation(const gp_Pnt2d& Point1, const gp_Pnt2d& Point2)
{
  TheTranslation = new Geom2d_Transformation();
  TheTranslation->SetTranslation(Point1, Point2);
}

const occ::handle<Geom2d_Transformation>& GCE2d_MakeTranslation::Value() const
{
  return TheTranslation;
}
