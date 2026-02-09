#include <Geom2d_Line.hpp>
#include <Geom_Line.hpp>
#include <GeomToStep_MakeCartesianPoint.hpp>
#include <GeomToStep_MakeLine.hpp>
#include <GeomToStep_MakeVector.hpp>
#include <gp_Lin.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>
#include <StdFail_NotDone.hpp>
#include <StepData_Factors.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <StepGeom_Line.hpp>
#include <StepGeom_Vector.hpp>
#include <TCollection_HAsciiString.hpp>

GeomToStep_MakeLine::GeomToStep_MakeLine(const gp_Lin& L, const StepData_Factors& theLocalFactors)
{
#define Vec_gen gp_Vec
#include "GeomToStep_MakeLine_gen.hpp"
#undef Vec_gen
}

GeomToStep_MakeLine::GeomToStep_MakeLine(const gp_Lin2d& L, const StepData_Factors& theLocalFactors)
{
#define Vec_gen gp_Vec2d
#include "GeomToStep_MakeLine_gen.hpp"
#undef Vec_gen
}

GeomToStep_MakeLine::GeomToStep_MakeLine(const occ::handle<Geom_Line>& Gline,
                                         const StepData_Factors&       theLocalFactors)
{
  gp_Lin L;
  L = Gline->Lin();
#define Vec_gen gp_Vec
#include "GeomToStep_MakeLine_gen.hpp"
#undef Vec_gen
}

GeomToStep_MakeLine::GeomToStep_MakeLine(const occ::handle<Geom2d_Line>& Gline,
                                         const StepData_Factors&         theLocalFactors)
{
  gp_Lin2d L;
  L = Gline->Lin2d();
#define Vec_gen gp_Vec2d
#include "GeomToStep_MakeLine_gen.hpp"
#undef Vec_gen
}

const occ::handle<StepGeom_Line>& GeomToStep_MakeLine::Value() const
{
  StdFail_NotDone_Raise_if(!done, "GeomToStep_MakeLine::Value() - no result");
  return theLine;
}
