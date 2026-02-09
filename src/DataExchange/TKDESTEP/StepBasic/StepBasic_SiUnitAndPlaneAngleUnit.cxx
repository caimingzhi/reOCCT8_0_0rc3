

#include <Standard_Type.hpp>
#include <StepBasic_DimensionalExponents.hpp>
#include <StepBasic_PlaneAngleUnit.hpp>
#include <StepBasic_SiUnitAndPlaneAngleUnit.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_SiUnitAndPlaneAngleUnit, StepBasic_SiUnit)

StepBasic_SiUnitAndPlaneAngleUnit::StepBasic_SiUnitAndPlaneAngleUnit() = default;

void StepBasic_SiUnitAndPlaneAngleUnit::Init(const bool                 hasAprefix,
                                             const StepBasic_SiPrefix   aPrefix,
                                             const StepBasic_SiUnitName aName)
{

  planeAngleUnit = new StepBasic_PlaneAngleUnit();
  occ::handle<StepBasic_DimensionalExponents> aDimensions;
  aDimensions.Nullify();
  planeAngleUnit->Init(aDimensions);

  StepBasic_SiUnit::Init(hasAprefix, aPrefix, aName);
}

void StepBasic_SiUnitAndPlaneAngleUnit::SetPlaneAngleUnit(
  const occ::handle<StepBasic_PlaneAngleUnit>& aPlaneAngleUnit)
{
  planeAngleUnit = aPlaneAngleUnit;
}

occ::handle<StepBasic_PlaneAngleUnit> StepBasic_SiUnitAndPlaneAngleUnit::PlaneAngleUnit() const
{
  return planeAngleUnit;
}
