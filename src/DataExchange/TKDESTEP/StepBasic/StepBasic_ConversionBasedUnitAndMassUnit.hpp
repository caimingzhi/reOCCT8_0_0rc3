#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_ConversionBasedUnit.hpp>
class StepBasic_MassUnit;
class StepBasic_DimensionalExponents;
class TCollection_HAsciiString;
class StepBasic_MeasureWithUnit;

class StepBasic_ConversionBasedUnitAndMassUnit : public StepBasic_ConversionBasedUnit
{

public:
  //! Returns a ConversionBasedUnitAndLengthUnit
  Standard_EXPORT StepBasic_ConversionBasedUnitAndMassUnit();

  Standard_EXPORT void Init(const occ::handle<StepBasic_DimensionalExponents>& aDimensions,
                            const occ::handle<TCollection_HAsciiString>&       aName,
                            const occ::handle<Standard_Transient>&             aConversionFactor);

  Standard_EXPORT void SetMassUnit(const occ::handle<StepBasic_MassUnit>& aMassUnit);

  Standard_EXPORT occ::handle<StepBasic_MassUnit> MassUnit() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_ConversionBasedUnitAndMassUnit, StepBasic_ConversionBasedUnit)

private:
  occ::handle<StepBasic_MassUnit> massUnit;
};

