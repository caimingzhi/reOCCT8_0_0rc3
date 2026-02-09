#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToStep_Root.hpp>
#include <StepData_StepModel.hpp>
class StepGeom_Axis2Placement3d;
class gp_Ax2;
class gp_Ax3;
class gp_Trsf;
class Geom_Axis2Placement;

class GeomToStep_MakeAxis2Placement3d : public GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToStep_MakeAxis2Placement3d(
    const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT GeomToStep_MakeAxis2Placement3d(
    const gp_Ax2&           A,
    const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT GeomToStep_MakeAxis2Placement3d(
    const gp_Ax3&           A,
    const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT GeomToStep_MakeAxis2Placement3d(
    const gp_Trsf&          T,
    const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT GeomToStep_MakeAxis2Placement3d(
    const occ::handle<Geom_Axis2Placement>& A,
    const StepData_Factors&                 theLocalFactors = StepData_Factors());

  Standard_EXPORT const occ::handle<StepGeom_Axis2Placement3d>& Value() const;

private:
  occ::handle<StepGeom_Axis2Placement3d> theAxis2Placement3d;
};
