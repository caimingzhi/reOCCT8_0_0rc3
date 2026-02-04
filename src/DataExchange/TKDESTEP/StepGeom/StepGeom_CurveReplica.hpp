#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_Curve.hpp>
class StepGeom_CartesianTransformationOperator;
class TCollection_HAsciiString;

class StepGeom_CurveReplica : public StepGeom_Curve
{

public:
  //! Returns a CurveReplica
  Standard_EXPORT StepGeom_CurveReplica();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                 aName,
    const occ::handle<StepGeom_Curve>&                           aParentCurve,
    const occ::handle<StepGeom_CartesianTransformationOperator>& aTransformation);

  Standard_EXPORT void SetParentCurve(const occ::handle<StepGeom_Curve>& aParentCurve);

  Standard_EXPORT occ::handle<StepGeom_Curve> ParentCurve() const;

  Standard_EXPORT void SetTransformation(
    const occ::handle<StepGeom_CartesianTransformationOperator>& aTransformation);

  Standard_EXPORT occ::handle<StepGeom_CartesianTransformationOperator> Transformation() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_CurveReplica, StepGeom_Curve)

private:
  occ::handle<StepGeom_Curve>                           parentCurve;
  occ::handle<StepGeom_CartesianTransformationOperator> transformation;
};

