

#include <StepGeom_CartesianTransformationOperator.hpp>
#include <StepGeom_PointReplica.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_PointReplica, StepGeom_Point)

StepGeom_PointReplica::StepGeom_PointReplica() = default;

void StepGeom_PointReplica::Init(
  const occ::handle<TCollection_HAsciiString>&                 aName,
  const occ::handle<StepGeom_Point>&                           aParentPt,
  const occ::handle<StepGeom_CartesianTransformationOperator>& aTransformation)
{

  parentPt       = aParentPt;
  transformation = aTransformation;

  StepRepr_RepresentationItem::Init(aName);
}

void StepGeom_PointReplica::SetParentPt(const occ::handle<StepGeom_Point>& aParentPt)
{
  parentPt = aParentPt;
}

occ::handle<StepGeom_Point> StepGeom_PointReplica::ParentPt() const
{
  return parentPt;
}

void StepGeom_PointReplica::SetTransformation(
  const occ::handle<StepGeom_CartesianTransformationOperator>& aTransformation)
{
  transformation = aTransformation;
}

occ::handle<StepGeom_CartesianTransformationOperator> StepGeom_PointReplica::Transformation() const
{
  return transformation;
}
