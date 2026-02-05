#pragma once

#include <Standard.hpp>

#include <StepBasic_LengthMeasureWithUnit.hpp>
#include <StepDimTol_GeometricTolerance.hpp>

class TCollection_HAsciiString;
class StepBasic_MeasureWithUnit;
class StepDimTol_GeometricToleranceTarget;

//! Representation of STEP entity UnequallyDisposedGeometricTolerance
class StepDimTol_UnequallyDisposedGeometricTolerance : public StepDimTol_GeometricTolerance
{

public:
  //! Empty constructor
  Standard_EXPORT StepDimTol_UnequallyDisposedGeometricTolerance();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& theName,
                            const occ::handle<TCollection_HAsciiString>& theDescription,
                            const occ::handle<Standard_Transient>&       theMagnitude,
                            const StepDimTol_GeometricToleranceTarget&   theTolerancedShapeAspect,
                            const occ::handle<StepBasic_LengthMeasureWithUnit>& theDisplacement);

  //! Returns field Displacement
  inline occ::handle<StepBasic_LengthMeasureWithUnit> Displacement() const
  {
    return myDisplacement;
  }

  //! Set field Displacement
  inline void SetDisplacement(const occ::handle<StepBasic_LengthMeasureWithUnit>& theDisplacement)
  {
    myDisplacement = theDisplacement;
  }

  DEFINE_STANDARD_RTTIEXT(StepDimTol_UnequallyDisposedGeometricTolerance,
                          StepDimTol_GeometricTolerance)

private:
  occ::handle<StepBasic_LengthMeasureWithUnit> myDisplacement;
};
