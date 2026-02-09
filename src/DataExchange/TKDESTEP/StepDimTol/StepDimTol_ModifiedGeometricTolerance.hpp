#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

enum StepDimTol_LimitCondition
{
  StepDimTol_MaximumMaterialCondition,
  StepDimTol_LeastMaterialCondition,
  StepDimTol_RegardlessOfFeatureSize
};

#include <StepDimTol_GeometricTolerance.hpp>
class TCollection_HAsciiString;
class StepDimTol_GeometricToleranceTarget;
class StepRepr_ShapeAspect;

class StepDimTol_ModifiedGeometricTolerance : public StepDimTol_GeometricTolerance
{

public:
  Standard_EXPORT StepDimTol_ModifiedGeometricTolerance();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& theGeometricTolerance_Name,
    const occ::handle<TCollection_HAsciiString>& theGeometricTolerance_Description,
    const occ::handle<Standard_Transient>&       theGeometricTolerance_Magnitude,
    const occ::handle<StepRepr_ShapeAspect>&     theGeometricTolerance_TolerancedShapeAspect,
    const StepDimTol_LimitCondition              theModifier);

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& theGeometricTolerance_Name,
    const occ::handle<TCollection_HAsciiString>& theGeometricTolerance_Description,
    const occ::handle<Standard_Transient>&       theGeometricTolerance_Magnitude,
    const StepDimTol_GeometricToleranceTarget&   theGeometricTolerance_TolerancedShapeAspect,
    const StepDimTol_LimitCondition              theModifier);

  Standard_EXPORT StepDimTol_LimitCondition Modifier() const;

  Standard_EXPORT void SetModifier(const StepDimTol_LimitCondition theModifier);

  DEFINE_STANDARD_RTTIEXT(StepDimTol_ModifiedGeometricTolerance, StepDimTol_GeometricTolerance)

private:
  StepDimTol_LimitCondition myModifier;
};
