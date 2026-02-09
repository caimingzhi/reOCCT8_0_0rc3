#pragma once

#include <Standard.hpp>

#include <StepDimTol_GeometricTolerance.hpp>

class StepBasic_LengthMeasureWithUnit;
class TCollection_HAsciiString;
class StepBasic_MeasureWithUnit;
class StepDimTol_GeometricToleranceTarget;
class StepRepr_ShapeAspect;

class StepDimTol_GeometricToleranceWithDefinedUnit : public StepDimTol_GeometricTolerance
{

public:
  Standard_EXPORT StepDimTol_GeometricToleranceWithDefinedUnit();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& theName,
                            const occ::handle<TCollection_HAsciiString>& theDescription,
                            const occ::handle<Standard_Transient>&       theMagnitude,
                            const occ::handle<StepRepr_ShapeAspect>&     theTolerancedShapeAspect,
                            const occ::handle<StepBasic_LengthMeasureWithUnit>& theUnitSize);

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& theName,
                            const occ::handle<TCollection_HAsciiString>& theDescription,
                            const occ::handle<Standard_Transient>&       theMagnitude,
                            const StepDimTol_GeometricToleranceTarget&   theTolerancedShapeAspect,
                            const occ::handle<StepBasic_LengthMeasureWithUnit>& theUnitSize);

  inline occ::handle<StepBasic_LengthMeasureWithUnit> UnitSize() const { return myUnitSize; }

  inline void SetUnitSize(const occ::handle<StepBasic_LengthMeasureWithUnit>& theUnitSize)
  {
    myUnitSize = theUnitSize;
  }

  DEFINE_STANDARD_RTTIEXT(StepDimTol_GeometricToleranceWithDefinedUnit,
                          StepDimTol_GeometricTolerance)

private:
  occ::handle<StepBasic_LengthMeasureWithUnit> myUnitSize;
};
