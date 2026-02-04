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

//! Produces instances by Transformation of a basic item
class StepToTopoDS_MakeTransformed : public StepToTopoDS_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepToTopoDS_MakeTransformed();

  //! Computes a transformation to pass from an Origin placement to
  //! a Target placement. Returns True when done
  //! If not done, the transformation will by Identity
  Standard_EXPORT bool Compute(const occ::handle<StepGeom_Axis2Placement3d>& Origin,
                               const occ::handle<StepGeom_Axis2Placement3d>& Target,
                               const StepData_Factors& theLocalFactors = StepData_Factors());

  //! Computes a transformation defined by an operator 3D
  Standard_EXPORT bool Compute(
    const occ::handle<StepGeom_CartesianTransformationOperator3d>& Operator,
    const StepData_Factors& theLocalFactors = StepData_Factors());

  //! Returns the computed transformation (Identity if not yet or
  //! if failed)
  Standard_EXPORT const gp_Trsf& Transformation() const;

  //! Applies the computed transformation to a shape
  //! Returns False if the transformation is Identity
  Standard_EXPORT bool Transform(TopoDS_Shape& shape) const;

  //! Translates a MappedItem. More precisely
  //! A MappedItem has a MappingSource and a MappingTarget
  //! MappingSource has a MappedRepresentation and a MappingOrigin
  //! MappedRepresentation is the basic item to be instanced
  //! MappingOrigin is the starting placement
  //! MappingTarget is the final placement
  //!
  //! Hence, the transformation from MappingOrigin and MappingTarget
  //! is computed, the MappedRepr. is converted to a Shape, then
  //! transformed as an instance of this Shape
  Standard_EXPORT TopoDS_Shape
    TranslateMappedItem(const occ::handle<StepRepr_MappedItem>&       mapit,
                        const occ::handle<Transfer_TransientProcess>& TP,
                        const StepData_Factors&      theLocalFactors = StepData_Factors(),
                        const Message_ProgressRange& theProgress     = Message_ProgressRange());

private:
  gp_Trsf theTrsf;
};

