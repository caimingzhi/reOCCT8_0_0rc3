#include <gce_MakeMirror2d.hpp>
#include <gp_Ax2d.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Trsf2d.hpp>

gce_MakeMirror2d::gce_MakeMirror2d(const gp_Pnt2d& Point)
{
  TheMirror2d.SetMirror(Point);
}

gce_MakeMirror2d::gce_MakeMirror2d(const gp_Ax2d& Axis)
{
  TheMirror2d.SetMirror(Axis);
}

gce_MakeMirror2d::gce_MakeMirror2d(const gp_Lin2d& Line)
{
  TheMirror2d.SetMirror(gp_Ax2d(Line.Location(), Line.Direction()));
}

gce_MakeMirror2d::gce_MakeMirror2d(const gp_Pnt2d& Point, const gp_Dir2d& Direc)
{
  TheMirror2d.SetMirror(gp_Ax2d(Point, Direc));
}

const gp_Trsf2d& gce_MakeMirror2d::Value() const
{
  return TheMirror2d;
}

const gp_Trsf2d& gce_MakeMirror2d::Operator() const
{
  return TheMirror2d;
}

gce_MakeMirror2d::operator gp_Trsf2d() const
{
  return TheMirror2d;
}
