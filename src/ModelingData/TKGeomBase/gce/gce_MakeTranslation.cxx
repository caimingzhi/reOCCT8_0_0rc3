#include <gce_MakeTranslation.hpp>
#include <gp_Pnt.hpp>
#include <gp_Trsf.hpp>
#include <gp_Vec.hpp>

//=========================================================================
//   Creation d une translation 3d de gp de vecteur de translation Vec.   +
//=========================================================================
gce_MakeTranslation::gce_MakeTranslation(const gp_Vec& Vec)
{
  TheTranslation.SetTranslation(Vec);
}

//=========================================================================
//   Creation d une translation 3d de gp de vecteur de translation le     +
//   vecteur reliant Point1 a Point2.                                     +
//=========================================================================

gce_MakeTranslation::gce_MakeTranslation(const gp_Pnt& Point1, const gp_Pnt& Point2)
{
  TheTranslation.SetTranslation(gp_Vec(Point1, Point2));
}

const gp_Trsf& gce_MakeTranslation::Value() const
{
  return TheTranslation;
}

const gp_Trsf& gce_MakeTranslation::Operator() const
{
  return TheTranslation;
}

gce_MakeTranslation::operator gp_Trsf() const
{
  return TheTranslation;
}
