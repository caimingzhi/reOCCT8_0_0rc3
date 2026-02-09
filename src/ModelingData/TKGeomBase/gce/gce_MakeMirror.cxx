#include <gce_MakeMirror.hpp>
#include <gp_Dir.hpp>
#include <gp_Pln.hpp>
#include <gp_Pnt.hpp>
#include <gp_Trsf.hpp>

gce_MakeMirror::gce_MakeMirror(const gp_Pnt& Point)
{
  TheMirror.SetMirror(Point);
}

gce_MakeMirror::gce_MakeMirror(const gp_Ax1& Axis)
{
  TheMirror.SetMirror(Axis);
}

gce_MakeMirror::gce_MakeMirror(const gp_Lin& Line)
{
  TheMirror.SetMirror(gp_Ax1(Line.Location(), Line.Direction()));
}

gce_MakeMirror::gce_MakeMirror(const gp_Pnt& Point, const gp_Dir& Direc)
{
  TheMirror.SetMirror(gp_Ax1(Point, Direc));
}

gce_MakeMirror::gce_MakeMirror(const gp_Ax2& Plane)
{
  TheMirror.SetMirror(Plane);
}

gce_MakeMirror::gce_MakeMirror(const gp_Pln& Plane)
{
  TheMirror.SetMirror(Plane.Position().Ax2());
}

const gp_Trsf& gce_MakeMirror::Value() const
{
  return TheMirror;
}

const gp_Trsf& gce_MakeMirror::Operator() const
{
  return TheMirror;
}

gce_MakeMirror::operator gp_Trsf() const
{
  return TheMirror;
}
