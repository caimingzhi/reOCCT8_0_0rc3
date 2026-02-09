#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_Point.hpp>
class StepGeom_CartesianTransformationOperator;
class TCollection_HAsciiString;

class StepGeom_PointReplica : public StepGeom_Point
{

public:
  Standard_EXPORT StepGeom_PointReplica();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                 aName,
    const occ::handle<StepGeom_Point>&                           aParentPt,
    const occ::handle<StepGeom_CartesianTransformationOperator>& aTransformation);

  Standard_EXPORT void SetParentPt(const occ::handle<StepGeom_Point>& aParentPt);

  Standard_EXPORT occ::handle<StepGeom_Point> ParentPt() const;

  Standard_EXPORT void SetTransformation(
    const occ::handle<StepGeom_CartesianTransformationOperator>& aTransformation);

  Standard_EXPORT occ::handle<StepGeom_CartesianTransformationOperator> Transformation() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_PointReplica, StepGeom_Point)

private:
  occ::handle<StepGeom_Point>                           parentPt;
  occ::handle<StepGeom_CartesianTransformationOperator> transformation;
};
