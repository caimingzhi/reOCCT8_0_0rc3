#include <GCE2d_MakeMirror.hpp>
#include <Geom2d_Transformation.hpp>
#include <gp_Ax2d.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Pnt2d.hpp>

GCE2d_MakeMirror::GCE2d_MakeMirror(const gp_Pnt2d& Point)
{
  TheMirror = new Geom2d_Transformation();
  TheMirror->SetMirror(Point);
}

GCE2d_MakeMirror::GCE2d_MakeMirror(const gp_Ax2d& Axis)
{
  TheMirror = new Geom2d_Transformation();
  TheMirror->SetMirror(Axis);
}

GCE2d_MakeMirror::GCE2d_MakeMirror(const gp_Lin2d& Line)
{
  TheMirror = new Geom2d_Transformation();
  TheMirror->SetMirror(gp_Ax2d(Line.Location(), Line.Direction()));
}

GCE2d_MakeMirror::GCE2d_MakeMirror(const gp_Pnt2d& Point, const gp_Dir2d& Direc)
{
  TheMirror = new Geom2d_Transformation();
  TheMirror->SetMirror(gp_Ax2d(Point, Direc));
}

const occ::handle<Geom2d_Transformation>& GCE2d_MakeMirror::Value() const
{
  return TheMirror;
}
