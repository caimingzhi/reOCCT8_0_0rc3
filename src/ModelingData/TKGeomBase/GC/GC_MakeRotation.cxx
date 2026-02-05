#include <GC_MakeRotation.hpp>
#include <Geom_Transformation.hpp>
#include <gp_Dir.hpp>
#include <gp_Lin.hpp>
#include <gp_Pnt.hpp>
#include <StdFail_NotDone.hpp>

//=========================================================================
//   Creation d une rotation 3d de gp d angle Angle par rapport a une     +
//   droite Line.                                                         +
//=========================================================================
GC_MakeRotation::GC_MakeRotation(const gp_Lin& Line, const double Angle)
{
  TheRotation = new Geom_Transformation();
  TheRotation->SetRotation(gp_Ax1(Line.Location(), Line.Direction()), Angle);
}

//=========================================================================
//   Creation d une rotation 3d de gp d angle Angle par rapport a un      +
//   axe Axis.                                                            +
//=========================================================================

GC_MakeRotation::GC_MakeRotation(const gp_Ax1& Axis, const double Angle)
{
  TheRotation = new Geom_Transformation();
  TheRotation->SetRotation(Axis, Angle);
}

//=========================================================================
//   Creation d une rotation 3d de gp d angle Angle par rapport a une     +
//   droite issue du point Point et de direction Direc.                   +
//=========================================================================

GC_MakeRotation::GC_MakeRotation(const gp_Pnt& Point, const gp_Dir& Direc, const double Angle)
{
  TheRotation = new Geom_Transformation();
  TheRotation->SetRotation(gp_Ax1(Point, Direc), Angle);
}

const occ::handle<Geom_Transformation>& GC_MakeRotation::Value() const
{
  return TheRotation;
}
