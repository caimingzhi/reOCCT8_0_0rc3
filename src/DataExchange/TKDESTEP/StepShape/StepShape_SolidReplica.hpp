#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_SolidModel.hpp>
class StepGeom_CartesianTransformationOperator3d;
class TCollection_HAsciiString;

class StepShape_SolidReplica : public StepShape_SolidModel
{

public:
  //! Returns a SolidReplica
  Standard_EXPORT StepShape_SolidReplica();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                   aName,
    const occ::handle<StepShape_SolidModel>&                       aParentSolid,
    const occ::handle<StepGeom_CartesianTransformationOperator3d>& aTransformation);

  Standard_EXPORT void SetParentSolid(const occ::handle<StepShape_SolidModel>& aParentSolid);

  Standard_EXPORT occ::handle<StepShape_SolidModel> ParentSolid() const;

  Standard_EXPORT void SetTransformation(
    const occ::handle<StepGeom_CartesianTransformationOperator3d>& aTransformation);

  Standard_EXPORT occ::handle<StepGeom_CartesianTransformationOperator3d> Transformation() const;

  DEFINE_STANDARD_RTTIEXT(StepShape_SolidReplica, StepShape_SolidModel)

private:
  occ::handle<StepShape_SolidModel>                       parentSolid;
  occ::handle<StepGeom_CartesianTransformationOperator3d> transformation;
};

