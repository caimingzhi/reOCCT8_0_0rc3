

#include <StepGeom_CartesianTransformationOperator.hpp>
#include <StepGeom_CurveReplica.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_CurveReplica, StepGeom_Curve)

StepGeom_CurveReplica::StepGeom_CurveReplica() = default;

void StepGeom_CurveReplica::Init(
  const occ::handle<TCollection_HAsciiString>&                 aName,
  const occ::handle<StepGeom_Curve>&                           aParentCurve,
  const occ::handle<StepGeom_CartesianTransformationOperator>& aTransformation)
{

  parentCurve    = aParentCurve;
  transformation = aTransformation;

  StepRepr_RepresentationItem::Init(aName);
}

void StepGeom_CurveReplica::SetParentCurve(const occ::handle<StepGeom_Curve>& aParentCurve)
{
  parentCurve = aParentCurve;
}

occ::handle<StepGeom_Curve> StepGeom_CurveReplica::ParentCurve() const
{
  return parentCurve;
}

void StepGeom_CurveReplica::SetTransformation(
  const occ::handle<StepGeom_CartesianTransformationOperator>& aTransformation)
{
  transformation = aTransformation;
}

occ::handle<StepGeom_CartesianTransformationOperator> StepGeom_CurveReplica::Transformation() const
{
  return transformation;
}
