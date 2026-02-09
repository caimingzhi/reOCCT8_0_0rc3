#pragma once

#include <Standard.hpp>

#include <StepBasic_LengthMeasureWithUnit.hpp>
#include <StepDimTol_GeometricToleranceWithModifiers.hpp>
#include <StepDimTol_GeometricToleranceModifier.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

class TCollection_HAsciiString;
class StepBasic_MeasureWithUnit;
class StepDimTol_GeometricToleranceTarget;

class StepDimTol_GeometricToleranceWithMaximumTolerance
    : public StepDimTol_GeometricToleranceWithModifiers
{

public:
  Standard_EXPORT StepDimTol_GeometricToleranceWithMaximumTolerance();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& theName,
    const occ::handle<TCollection_HAsciiString>& theDescription,
    const occ::handle<Standard_Transient>&       theMagnitude,
    const StepDimTol_GeometricToleranceTarget&   theTolerancedShapeAspect,
    const occ::handle<NCollection_HArray1<StepDimTol_GeometricToleranceModifier>>& theModifiers,
    const occ::handle<StepBasic_LengthMeasureWithUnit>&                            theUnitSize);

  inline occ::handle<StepBasic_LengthMeasureWithUnit> MaximumUpperTolerance() const
  {
    return myMaximumUpperTolerance;
  }

  inline void SetMaximumUpperTolerance(
    const occ::handle<StepBasic_LengthMeasureWithUnit>& theMaximumUpperTolerance)
  {
    myMaximumUpperTolerance = theMaximumUpperTolerance;
  }

  DEFINE_STANDARD_RTTIEXT(StepDimTol_GeometricToleranceWithMaximumTolerance,
                          StepDimTol_GeometricToleranceWithModifiers)

private:
  occ::handle<StepBasic_LengthMeasureWithUnit> myMaximumUpperTolerance;
};
