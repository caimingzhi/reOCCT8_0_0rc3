#pragma once

#include <Standard.hpp>

#include <StepBasic_LengthMeasureWithUnit.hpp>
#include <StepDimTol_GeometricTolerance.hpp>

class TCollection_HAsciiString;
class StepBasic_MeasureWithUnit;
class StepDimTol_GeometricToleranceTarget;

class StepDimTol_UnequallyDisposedGeometricTolerance : public StepDimTol_GeometricTolerance
{

public:
  Standard_EXPORT StepDimTol_UnequallyDisposedGeometricTolerance();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& theName,
                            const occ::handle<TCollection_HAsciiString>& theDescription,
                            const occ::handle<Standard_Transient>&       theMagnitude,
                            const StepDimTol_GeometricToleranceTarget&   theTolerancedShapeAspect,
                            const occ::handle<StepBasic_LengthMeasureWithUnit>& theDisplacement);

  inline occ::handle<StepBasic_LengthMeasureWithUnit> Displacement() const
  {
    return myDisplacement;
  }

  inline void SetDisplacement(const occ::handle<StepBasic_LengthMeasureWithUnit>& theDisplacement)
  {
    myDisplacement = theDisplacement;
  }

  DEFINE_STANDARD_RTTIEXT(StepDimTol_UnequallyDisposedGeometricTolerance,
                          StepDimTol_GeometricTolerance)

private:
  occ::handle<StepBasic_LengthMeasureWithUnit> myDisplacement;
};
