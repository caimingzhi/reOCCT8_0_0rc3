#include <GC_MakeTranslation.hpp>
#include <Geom_Transformation.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <StdFail_NotDone.hpp>

//=========================================================================
//   Creation of a 3D Geom translation of translation vector Vec.         +
//=========================================================================
GC_MakeTranslation::GC_MakeTranslation(const gp_Vec& Vec)
{
  TheTranslation = new Geom_Transformation();
  TheTranslation->SetTranslation(Vec);
}

//=========================================================================
//    Creation of a 3D Geom translation of translation vector connecting  +
//    Point1 and Point2.                                                  +
//=========================================================================

GC_MakeTranslation::GC_MakeTranslation(const gp_Pnt& Point1, const gp_Pnt& Point2)
{
  TheTranslation = new Geom_Transformation();
  TheTranslation->SetTranslation(Point1, Point2);
}

const occ::handle<Geom_Transformation>& GC_MakeTranslation::Value() const
{
  return TheTranslation;
}
