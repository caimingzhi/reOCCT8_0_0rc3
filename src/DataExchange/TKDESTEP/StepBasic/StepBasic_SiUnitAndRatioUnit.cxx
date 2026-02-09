

#include <Standard_Type.hpp>
#include <StepBasic_DimensionalExponents.hpp>
#include <StepBasic_RatioUnit.hpp>
#include <StepBasic_SiUnitAndRatioUnit.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_SiUnitAndRatioUnit, StepBasic_SiUnit)

StepBasic_SiUnitAndRatioUnit::StepBasic_SiUnitAndRatioUnit() = default;

void StepBasic_SiUnitAndRatioUnit::Init(const bool                 hasAprefix,
                                        const StepBasic_SiPrefix   aPrefix,
                                        const StepBasic_SiUnitName aName)
{

  StepBasic_SiUnit::Init(hasAprefix, aPrefix, aName);

  ratioUnit = new StepBasic_RatioUnit();
  occ::handle<StepBasic_DimensionalExponents> aDimensions;
  aDimensions.Nullify();
  ratioUnit->Init(aDimensions);
}

void StepBasic_SiUnitAndRatioUnit::SetRatioUnit(const occ::handle<StepBasic_RatioUnit>& aRatioUnit)
{
  ratioUnit = aRatioUnit;
}

occ::handle<StepBasic_RatioUnit> StepBasic_SiUnitAndRatioUnit::RatioUnit() const
{
  return ratioUnit;
}
