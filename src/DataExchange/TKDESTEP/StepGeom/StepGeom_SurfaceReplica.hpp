#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_Surface.hpp>
class StepGeom_CartesianTransformationOperator3d;
class TCollection_HAsciiString;

class StepGeom_SurfaceReplica : public StepGeom_Surface
{

public:
  Standard_EXPORT StepGeom_SurfaceReplica();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                   aName,
    const occ::handle<StepGeom_Surface>&                           aParentSurface,
    const occ::handle<StepGeom_CartesianTransformationOperator3d>& aTransformation);

  Standard_EXPORT void SetParentSurface(const occ::handle<StepGeom_Surface>& aParentSurface);

  Standard_EXPORT occ::handle<StepGeom_Surface> ParentSurface() const;

  Standard_EXPORT void SetTransformation(
    const occ::handle<StepGeom_CartesianTransformationOperator3d>& aTransformation);

  Standard_EXPORT occ::handle<StepGeom_CartesianTransformationOperator3d> Transformation() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_SurfaceReplica, StepGeom_Surface)

private:
  occ::handle<StepGeom_Surface>                           parentSurface;
  occ::handle<StepGeom_CartesianTransformationOperator3d> transformation;
};
