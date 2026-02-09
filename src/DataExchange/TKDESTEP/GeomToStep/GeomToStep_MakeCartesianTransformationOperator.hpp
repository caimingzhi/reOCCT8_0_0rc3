#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToStep_Root.hpp>
#include <StepData_StepModel.hpp>
#include <StepGeom_CartesianTransformationOperator3d.hpp>

class gp_Trsf;

class GeomToStep_MakeCartesianTransformationOperator : public GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToStep_MakeCartesianTransformationOperator(
    const gp_Trsf&          theTrsf,
    const StepData_Factors& theLocalFactors = StepData_Factors());

  inline const occ::handle<StepGeom_CartesianTransformationOperator3d>& Value() const
  {
    return myTrsfOp;
  }

private:
  occ::handle<StepGeom_CartesianTransformationOperator3d> myTrsfOp;
};
