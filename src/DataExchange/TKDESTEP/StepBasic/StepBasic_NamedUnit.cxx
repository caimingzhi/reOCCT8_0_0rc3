

#include <Standard_Type.hpp>
#include <StepBasic_DimensionalExponents.hpp>
#include <StepBasic_NamedUnit.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_NamedUnit, Standard_Transient)

StepBasic_NamedUnit::StepBasic_NamedUnit() = default;

void StepBasic_NamedUnit::Init(const occ::handle<StepBasic_DimensionalExponents>& aDimensions)
{

  dimensions = aDimensions;
}

void StepBasic_NamedUnit::SetDimensions(
  const occ::handle<StepBasic_DimensionalExponents>& aDimensions)
{
  dimensions = aDimensions;
}

occ::handle<StepBasic_DimensionalExponents> StepBasic_NamedUnit::Dimensions() const
{
  return dimensions;
}
