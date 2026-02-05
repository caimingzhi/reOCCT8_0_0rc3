#include <GC_MakeMirror.hpp>
#include <Geom_Transformation.hpp>
#include <gp_Dir.hpp>
#include <gp_Pln.hpp>
#include <gp_Pnt.hpp>
#include <StdFail_NotDone.hpp>

//=========================================================================
//   Creation d une symetrie de Geom par rapport a un point.              +
//=========================================================================
GC_MakeMirror::GC_MakeMirror(const gp_Pnt& Point)
{
  TheMirror = new Geom_Transformation();
  TheMirror->SetMirror(Point);
}

//=========================================================================
//   Creation d une symetrie de Geom par rapport a une droite.            +
//=========================================================================

GC_MakeMirror::GC_MakeMirror(const gp_Ax1& Axis)
{
  TheMirror = new Geom_Transformation();
  TheMirror->SetMirror(Axis);
}

//=========================================================================
//   Creation d une symetrie de Geom par rapport a une droite.            +
//=========================================================================

GC_MakeMirror::GC_MakeMirror(const gp_Lin& Line)
{
  TheMirror = new Geom_Transformation();
  TheMirror->SetMirror(gp_Ax1(Line.Location(), Line.Direction()));
}

//=========================================================================
//   Creation d une symetrie 3d de Geom par rapport a une droite definie  +
//   par un point et une direction.                                       +
//=========================================================================

GC_MakeMirror::GC_MakeMirror(const gp_Pnt& Point, const gp_Dir& Direc)
{
  TheMirror = new Geom_Transformation();
  TheMirror->SetMirror(gp_Ax1(Point, Direc));
}

//=========================================================================
//   Creation d une symetrie 3d de Geom par rapport a un plan defini par  +
//   un Ax2 (Normale au plan et axe x du plan).                           +
//=========================================================================

GC_MakeMirror::GC_MakeMirror(const gp_Ax2& Plane)
{
  TheMirror = new Geom_Transformation();
  TheMirror->SetMirror(Plane);
}

//=========================================================================
//   Creation d une symetrie 3d de gp par rapport a un plan Plane.        +
//=========================================================================

GC_MakeMirror::GC_MakeMirror(const gp_Pln& Plane)
{
  TheMirror = new Geom_Transformation();
  TheMirror->SetMirror(Plane.Position().Ax2());
}

const occ::handle<Geom_Transformation>& GC_MakeMirror::Value() const
{
  return TheMirror;
}
