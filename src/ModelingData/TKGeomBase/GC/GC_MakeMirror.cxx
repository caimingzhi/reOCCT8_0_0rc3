#include <GC_MakeMirror.hpp>
#include <Geom_Transformation.hpp>
#include <gp_Dir.hpp>
#include <gp_Pln.hpp>
#include <gp_Pnt.hpp>
#include <StdFail_NotDone.hpp>

GC_MakeMirror::GC_MakeMirror(const gp_Pnt& Point)
{
  TheMirror = new Geom_Transformation();
  TheMirror->SetMirror(Point);
}

GC_MakeMirror::GC_MakeMirror(const gp_Ax1& Axis)
{
  TheMirror = new Geom_Transformation();
  TheMirror->SetMirror(Axis);
}

GC_MakeMirror::GC_MakeMirror(const gp_Lin& Line)
{
  TheMirror = new Geom_Transformation();
  TheMirror->SetMirror(gp_Ax1(Line.Location(), Line.Direction()));
}

GC_MakeMirror::GC_MakeMirror(const gp_Pnt& Point, const gp_Dir& Direc)
{
  TheMirror = new Geom_Transformation();
  TheMirror->SetMirror(gp_Ax1(Point, Direc));
}

GC_MakeMirror::GC_MakeMirror(const gp_Ax2& Plane)
{
  TheMirror = new Geom_Transformation();
  TheMirror->SetMirror(Plane);
}

GC_MakeMirror::GC_MakeMirror(const gp_Pln& Plane)
{
  TheMirror = new Geom_Transformation();
  TheMirror->SetMirror(Plane.Position().Ax2());
}

const occ::handle<Geom_Transformation>& GC_MakeMirror::Value() const
{
  return TheMirror;
}
