

#include <StepBasic_Product.hpp>
#include <StepBasic_ProductDefinitionFormation.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ProductDefinitionFormation, Standard_Transient)

StepBasic_ProductDefinitionFormation::StepBasic_ProductDefinitionFormation() = default;

void StepBasic_ProductDefinitionFormation::Init(
  const occ::handle<TCollection_HAsciiString>& aId,
  const occ::handle<TCollection_HAsciiString>& aDescription,
  const occ::handle<StepBasic_Product>&        aOfProduct)
{

  id          = aId;
  description = aDescription;
  ofProduct   = aOfProduct;
}

void StepBasic_ProductDefinitionFormation::SetId(const occ::handle<TCollection_HAsciiString>& aId)
{
  id = aId;
}

occ::handle<TCollection_HAsciiString> StepBasic_ProductDefinitionFormation::Id() const
{
  return id;
}

void StepBasic_ProductDefinitionFormation::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  description = aDescription;
}

occ::handle<TCollection_HAsciiString> StepBasic_ProductDefinitionFormation::Description() const
{
  return description;
}

void StepBasic_ProductDefinitionFormation::SetOfProduct(
  const occ::handle<StepBasic_Product>& aOfProduct)
{
  ofProduct = aOfProduct;
}

occ::handle<StepBasic_Product> StepBasic_ProductDefinitionFormation::OfProduct() const
{
  return ofProduct;
}
