#pragma once

#include <Standard.hpp>

#include <Standard_Boolean.hpp>

enum StepDimTol_AreaUnitType
{
  StepDimTol_Circular,
  StepDimTol_Rectangular,
  StepDimTol_Square
};

#include <StepDimTol_GeometricToleranceWithDefinedUnit.hpp>

class StepBasic_LengthMeasureWithUnit;
class TCollection_HAsciiString;
class StepBasic_MeasureWithUnit;
class StepDimTol_GeometricToleranceTarget;

//! Representation of STEP entity GeometricToleranceWithDefinedAreaUnit
class StepDimTol_GeometricToleranceWithDefinedAreaUnit
    : public StepDimTol_GeometricToleranceWithDefinedUnit
{

public:
  //! Empty constructor
  Standard_EXPORT StepDimTol_GeometricToleranceWithDefinedAreaUnit();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& theName,
                            const occ::handle<TCollection_HAsciiString>& theDescription,
                            const occ::handle<Standard_Transient>&       theMagnitude,
                            const StepDimTol_GeometricToleranceTarget&   theTolerancedShapeAspect,
                            const occ::handle<StepBasic_LengthMeasureWithUnit>& theUnitSize,
                            const StepDimTol_AreaUnitType                       theAreaType,
                            const bool theHasSecondUnitSize,
                            const occ::handle<StepBasic_LengthMeasureWithUnit>& theSecondUnitSize);

  //! Returns field AreaType
  inline StepDimTol_AreaUnitType AreaType() const { return myAreaType; }

  //! Set field AreaType
  inline void SetAreaType(const StepDimTol_AreaUnitType theAreaType) { myAreaType = theAreaType; }

  //! Returns field SecondUnitSize
  inline occ::handle<StepBasic_LengthMeasureWithUnit> SecondUnitSize() const
  {
    return mySecondUnitSize;
  }

  //! Set field SecondUnitSize
  inline void SetSecondUnitSize(
    const occ::handle<StepBasic_LengthMeasureWithUnit>& theSecondUnitSize)
  {
    mySecondUnitSize = theSecondUnitSize;
  }

  //! Indicates if SecondUnitSize field exist
  inline bool HasSecondUnitSize() const { return mySecondUnitSize.IsNull(); }

  DEFINE_STANDARD_RTTIEXT(StepDimTol_GeometricToleranceWithDefinedAreaUnit,
                          StepDimTol_GeometricToleranceWithDefinedUnit)

private:
  StepDimTol_AreaUnitType                      myAreaType;
  occ::handle<StepBasic_LengthMeasureWithUnit> mySecondUnitSize;
};
