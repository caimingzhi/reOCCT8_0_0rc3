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

//! Representation of STEP entity ModifiedGeometricTolerance
class StepDimTol_ModifiedGeometricTolerance : public StepDimTol_GeometricTolerance
{

public:
  //! Empty constructor
  Standard_EXPORT StepDimTol_ModifiedGeometricTolerance();

  //! Initialize all fields (own and inherited) AP214
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& theGeometricTolerance_Name,
    const occ::handle<TCollection_HAsciiString>& theGeometricTolerance_Description,
    const occ::handle<Standard_Transient>&       theGeometricTolerance_Magnitude,
    const occ::handle<StepRepr_ShapeAspect>&     theGeometricTolerance_TolerancedShapeAspect,
    const StepDimTol_LimitCondition              theModifier);

  //! Initialize all fields (own and inherited) AP242
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& theGeometricTolerance_Name,
    const occ::handle<TCollection_HAsciiString>& theGeometricTolerance_Description,
    const occ::handle<Standard_Transient>&       theGeometricTolerance_Magnitude,
    const StepDimTol_GeometricToleranceTarget&   theGeometricTolerance_TolerancedShapeAspect,
    const StepDimTol_LimitCondition              theModifier);

  //! Returns field Modifier
  Standard_EXPORT StepDimTol_LimitCondition Modifier() const;

  //! Set field Modifier
  Standard_EXPORT void SetModifier(const StepDimTol_LimitCondition theModifier);

  DEFINE_STANDARD_RTTIEXT(StepDimTol_ModifiedGeometricTolerance, StepDimTol_GeometricTolerance)

private:
  StepDimTol_LimitCondition myModifier;
};
