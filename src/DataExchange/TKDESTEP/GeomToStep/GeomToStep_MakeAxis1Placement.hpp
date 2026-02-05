#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <StepData_Factors.hpp>

#include <GeomToStep_Root.hpp>

class StepGeom_Axis1Placement;
class gp_Ax1;
class gp_Ax2d;
class Geom_Axis1Placement;
class Geom2d_AxisPlacement;

//! This class implements the mapping between classes
//! Axis1Placement from Geom and Ax1 from gp, and the class
//! Axis1Placement from StepGeom which describes an
//! Axis1Placement from Prostep.
class GeomToStep_MakeAxis1Placement : public GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToStep_MakeAxis1Placement(
    const gp_Ax1&           A,
    const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT GeomToStep_MakeAxis1Placement(
    const gp_Ax2d&          A,
    const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT GeomToStep_MakeAxis1Placement(
    const occ::handle<Geom_Axis1Placement>& A,
    const StepData_Factors&                 theLocalFactors = StepData_Factors());

  Standard_EXPORT GeomToStep_MakeAxis1Placement(
    const occ::handle<Geom2d_AxisPlacement>& A,
    const StepData_Factors&                  theLocalFactors = StepData_Factors());

  Standard_EXPORT const occ::handle<StepGeom_Axis1Placement>& Value() const;

private:
  occ::handle<StepGeom_Axis1Placement> theAxis1Placement;
};
