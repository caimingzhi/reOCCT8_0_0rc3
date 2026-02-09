

#include <StepGeom_CartesianTransformationOperator3d.hpp>
#include <StepGeom_SurfaceReplica.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_SurfaceReplica, StepGeom_Surface)

StepGeom_SurfaceReplica::StepGeom_SurfaceReplica() = default;

void StepGeom_SurfaceReplica::Init(
  const occ::handle<TCollection_HAsciiString>&                   aName,
  const occ::handle<StepGeom_Surface>&                           aParentSurface,
  const occ::handle<StepGeom_CartesianTransformationOperator3d>& aTransformation)
{

  parentSurface  = aParentSurface;
  transformation = aTransformation;

  StepRepr_RepresentationItem::Init(aName);
}

void StepGeom_SurfaceReplica::SetParentSurface(const occ::handle<StepGeom_Surface>& aParentSurface)
{
  parentSurface = aParentSurface;
}

occ::handle<StepGeom_Surface> StepGeom_SurfaceReplica::ParentSurface() const
{
  return parentSurface;
}

void StepGeom_SurfaceReplica::SetTransformation(
  const occ::handle<StepGeom_CartesianTransformationOperator3d>& aTransformation)
{
  transformation = aTransformation;
}

occ::handle<StepGeom_CartesianTransformationOperator3d> StepGeom_SurfaceReplica::Transformation()
  const
{
  return transformation;
}
