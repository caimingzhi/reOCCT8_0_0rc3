#include <Geom2d_AxisPlacement.hpp>
#include <Geom_Axis1Placement.hpp>
#include <GeomToStep_MakeAxis1Placement.hpp>
#include <GeomToStep_MakeCartesianPoint.hpp>
#include <GeomToStep_MakeDirection.hpp>
#include <gp_Ax1.hpp>
#include <gp_Ax2d.hpp>
#include <StdFail_NotDone.hpp>
#include <StepData_Factors.hpp>
#include <StepGeom_Axis1Placement.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <StepGeom_Direction.hpp>
#include <TCollection_HAsciiString.hpp>

GeomToStep_MakeAxis1Placement::GeomToStep_MakeAxis1Placement(
  const gp_Ax1&           A,
  const StepData_Factors& theLocalFactors)
{
#include "GeomToStep_MakeAxis1Placement_gen.hpp"
}

GeomToStep_MakeAxis1Placement::GeomToStep_MakeAxis1Placement(
  const gp_Ax2d&          A,
  const StepData_Factors& theLocalFactors)
{
#include "GeomToStep_MakeAxis1Placement_gen.hpp"
}

GeomToStep_MakeAxis1Placement::GeomToStep_MakeAxis1Placement(
  const occ::handle<Geom_Axis1Placement>& Axis1,
  const StepData_Factors&                 theLocalFactors)
{
  gp_Ax1 A;
  A = Axis1->Ax1();
#include "GeomToStep_MakeAxis1Placement_gen.hpp"
}

GeomToStep_MakeAxis1Placement::GeomToStep_MakeAxis1Placement(
  const occ::handle<Geom2d_AxisPlacement>& Axis1,
  const StepData_Factors&                  theLocalFactors)
{
  gp_Ax2d A;
  A = Axis1->Ax2d();
#include "GeomToStep_MakeAxis1Placement_gen.hpp"
}

const occ::handle<StepGeom_Axis1Placement>& GeomToStep_MakeAxis1Placement::Value() const
{
  StdFail_NotDone_Raise_if(!done, "GeomToStep_MakeAxis1Placement::Value() - no result");
  return theAxis1Placement;
}
