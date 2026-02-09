

#include <StepGeom_CartesianTransformationOperator3d.hpp>
#include <StepShape_SolidReplica.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_SolidReplica, StepShape_SolidModel)

StepShape_SolidReplica::StepShape_SolidReplica() = default;

void StepShape_SolidReplica::Init(
  const occ::handle<TCollection_HAsciiString>&                   aName,
  const occ::handle<StepShape_SolidModel>&                       aParentSolid,
  const occ::handle<StepGeom_CartesianTransformationOperator3d>& aTransformation)
{

  parentSolid    = aParentSolid;
  transformation = aTransformation;

  StepRepr_RepresentationItem::Init(aName);
}

void StepShape_SolidReplica::SetParentSolid(const occ::handle<StepShape_SolidModel>& aParentSolid)
{
  parentSolid = aParentSolid;
}

occ::handle<StepShape_SolidModel> StepShape_SolidReplica::ParentSolid() const
{
  return parentSolid;
}

void StepShape_SolidReplica::SetTransformation(
  const occ::handle<StepGeom_CartesianTransformationOperator3d>& aTransformation)
{
  transformation = aTransformation;
}

occ::handle<StepGeom_CartesianTransformationOperator3d> StepShape_SolidReplica::Transformation()
  const
{
  return transformation;
}
