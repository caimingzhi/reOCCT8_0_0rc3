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

class StepDimTol_GeometricToleranceWithDefinedAreaUnit
    : public StepDimTol_GeometricToleranceWithDefinedUnit
{

public:
  Standard_EXPORT StepDimTol_GeometricToleranceWithDefinedAreaUnit();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& theName,
                            const occ::handle<TCollection_HAsciiString>& theDescription,
                            const occ::handle<Standard_Transient>&       theMagnitude,
                            const StepDimTol_GeometricToleranceTarget&   theTolerancedShapeAspect,
                            const occ::handle<StepBasic_LengthMeasureWithUnit>& theUnitSize,
                            const StepDimTol_AreaUnitType                       theAreaType,
                            const bool theHasSecondUnitSize,
                            const occ::handle<StepBasic_LengthMeasureWithUnit>& theSecondUnitSize);

  inline StepDimTol_AreaUnitType AreaType() const { return myAreaType; }

  inline void SetAreaType(const StepDimTol_AreaUnitType theAreaType) { myAreaType = theAreaType; }

  inline occ::handle<StepBasic_LengthMeasureWithUnit> SecondUnitSize() const
  {
    return mySecondUnitSize;
  }

  inline void SetSecondUnitSize(
    const occ::handle<StepBasic_LengthMeasureWithUnit>& theSecondUnitSize)
  {
    mySecondUnitSize = theSecondUnitSize;
  }

  inline bool HasSecondUnitSize() const { return mySecondUnitSize.IsNull(); }

  DEFINE_STANDARD_RTTIEXT(StepDimTol_GeometricToleranceWithDefinedAreaUnit,
                          StepDimTol_GeometricToleranceWithDefinedUnit)

private:
  StepDimTol_AreaUnitType                      myAreaType;
  occ::handle<StepBasic_LengthMeasureWithUnit> mySecondUnitSize;
};
