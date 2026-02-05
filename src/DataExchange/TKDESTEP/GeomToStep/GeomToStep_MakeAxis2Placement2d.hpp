#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToStep_Root.hpp>

class StepGeom_Axis2Placement2d;
class gp_Ax2;
class gp_Ax22d;

//! This class implements the mapping between classes
//! Axis2Placement from Geom and Ax2, Ax22d from gp, and the class
//! Axis2Placement2d from StepGeom which describes an
//! axis2_placement_2d from Prostep.
class GeomToStep_MakeAxis2Placement2d : public GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToStep_MakeAxis2Placement2d(
    const gp_Ax2&           A,
    const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT GeomToStep_MakeAxis2Placement2d(
    const gp_Ax22d&         A,
    const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT const occ::handle<StepGeom_Axis2Placement2d>& Value() const;

private:
  occ::handle<StepGeom_Axis2Placement2d> theAxis2Placement2d;
};
