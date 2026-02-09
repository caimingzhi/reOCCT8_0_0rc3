

#include <Standard_Type.hpp>
#include <StepBasic_DimensionalExponents.hpp>
#include <StepBasic_MassUnit.hpp>
#include <StepBasic_SiUnitAndMassUnit.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_SiUnitAndMassUnit, StepBasic_SiUnit)

StepBasic_SiUnitAndMassUnit::StepBasic_SiUnitAndMassUnit() = default;

void StepBasic_SiUnitAndMassUnit::Init(const bool                 hasAprefix,
                                       const StepBasic_SiPrefix   aPrefix,
                                       const StepBasic_SiUnitName aName)
{

  massUnit = new StepBasic_MassUnit();
  occ::handle<StepBasic_DimensionalExponents> aDimensions;
  aDimensions.Nullify();
  massUnit->Init(aDimensions);

  StepBasic_SiUnit::Init(hasAprefix, aPrefix, aName);
}

void StepBasic_SiUnitAndMassUnit::SetMassUnit(const occ::handle<StepBasic_MassUnit>& aMassUnit)
{
  massUnit = aMassUnit;
}

occ::handle<StepBasic_MassUnit> StepBasic_SiUnitAndMassUnit::MassUnit() const
{
  return massUnit;
}
