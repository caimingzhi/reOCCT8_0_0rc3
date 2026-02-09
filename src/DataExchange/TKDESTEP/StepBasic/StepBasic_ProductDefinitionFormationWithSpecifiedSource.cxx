

#include <StepBasic_Product.hpp>
#include <StepBasic_ProductDefinitionFormationWithSpecifiedSource.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ProductDefinitionFormationWithSpecifiedSource,
                           StepBasic_ProductDefinitionFormation)

StepBasic_ProductDefinitionFormationWithSpecifiedSource::
  StepBasic_ProductDefinitionFormationWithSpecifiedSource() = default;

void StepBasic_ProductDefinitionFormationWithSpecifiedSource::Init(
  const occ::handle<TCollection_HAsciiString>& aId,
  const occ::handle<TCollection_HAsciiString>& aDescription,
  const occ::handle<StepBasic_Product>&        aOfProduct,
  const StepBasic_Source                       aMakeOrBuy)
{

  makeOrBuy = aMakeOrBuy;

  StepBasic_ProductDefinitionFormation::Init(aId, aDescription, aOfProduct);
}

void StepBasic_ProductDefinitionFormationWithSpecifiedSource::SetMakeOrBuy(
  const StepBasic_Source aMakeOrBuy)
{
  makeOrBuy = aMakeOrBuy;
}

StepBasic_Source StepBasic_ProductDefinitionFormationWithSpecifiedSource::MakeOrBuy() const
{
  return makeOrBuy;
}
