#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_NamedUnit.hpp>
class TCollection_HAsciiString;
class StepBasic_MeasureWithUnit;
class StepBasic_DimensionalExponents;

class StepBasic_ConversionBasedUnit : public StepBasic_NamedUnit
{

public:
  //! Returns a ConversionBasedUnit
  Standard_EXPORT StepBasic_ConversionBasedUnit();

  Standard_EXPORT void Init(const occ::handle<StepBasic_DimensionalExponents>& aDimensions,
                            const occ::handle<TCollection_HAsciiString>&       aName,
                            const occ::handle<Standard_Transient>&             aConversionFactor);

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& aName);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetConversionFactor(
    const occ::handle<Standard_Transient>& aConversionFactor);

  Standard_EXPORT occ::handle<Standard_Transient> ConversionFactor() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_ConversionBasedUnit, StepBasic_NamedUnit)

private:
  occ::handle<TCollection_HAsciiString> name;
  occ::handle<Standard_Transient>       conversionFactor;
};

