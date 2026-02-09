#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Trsf.hpp>
#include <StepToTopoDS_Root.hpp>
#include <Message_ProgressRange.hpp>

class StepGeom_Axis2Placement3d;
class StepGeom_CartesianTransformationOperator3d;
class TopoDS_Shape;
class StepRepr_MappedItem;
class Transfer_TransientProcess;

class StepToTopoDS_MakeTransformed : public StepToTopoDS_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepToTopoDS_MakeTransformed();

  Standard_EXPORT bool Compute(const occ::handle<StepGeom_Axis2Placement3d>& Origin,
                               const occ::handle<StepGeom_Axis2Placement3d>& Target,
                               const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT bool Compute(
    const occ::handle<StepGeom_CartesianTransformationOperator3d>& Operator,
    const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT const gp_Trsf& Transformation() const;

  Standard_EXPORT bool Transform(TopoDS_Shape& shape) const;

  Standard_EXPORT TopoDS_Shape
    TranslateMappedItem(const occ::handle<StepRepr_MappedItem>&       mapit,
                        const occ::handle<Transfer_TransientProcess>& TP,
                        const StepData_Factors&      theLocalFactors = StepData_Factors(),
                        const Message_ProgressRange& theProgress     = Message_ProgressRange());

private:
  gp_Trsf theTrsf;
};
