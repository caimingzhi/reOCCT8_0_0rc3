

#include <Standard_Type.hpp>
#include <StepBasic_DimensionalExponents.hpp>
#include <StepBasic_LengthUnit.hpp>
#include <StepBasic_SiUnitAndLengthUnit.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_SiUnitAndLengthUnit, StepBasic_SiUnit)

StepBasic_SiUnitAndLengthUnit::StepBasic_SiUnitAndLengthUnit() = default;

void StepBasic_SiUnitAndLengthUnit::Init(const bool                 hasAprefix,
                                         const StepBasic_SiPrefix   aPrefix,
                                         const StepBasic_SiUnitName aName)
{

  lengthUnit = new StepBasic_LengthUnit();
  occ::handle<StepBasic_DimensionalExponents> aDimensions;
  aDimensions.Nullify();
  lengthUnit->Init(aDimensions);

  StepBasic_SiUnit::Init(hasAprefix, aPrefix, aName);
}

void StepBasic_SiUnitAndLengthUnit::SetLengthUnit(
  const occ::handle<StepBasic_LengthUnit>& aLengthUnit)
{
  lengthUnit = aLengthUnit;
}

occ::handle<StepBasic_LengthUnit> StepBasic_SiUnitAndLengthUnit::LengthUnit() const
{
  return lengthUnit;
}
