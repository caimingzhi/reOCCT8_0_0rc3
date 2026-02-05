#include <GC_MakeScale.hpp>
#include <Geom_Transformation.hpp>
#include <gp_Pnt.hpp>
#include <StdFail_NotDone.hpp>

//=========================================================================
//   Creation d un homothetie de gp de centre Point et de rapport Scale.  +
//=========================================================================
GC_MakeScale::GC_MakeScale(const gp_Pnt& Point, const double Scale)
{
  TheScale = new Geom_Transformation();
  TheScale->SetScale(Point, Scale);
}

const occ::handle<Geom_Transformation>& GC_MakeScale::Value() const
{
  return TheScale;
}
