

#include <StepBasic_ProductRelatedProductCategory.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ProductRelatedProductCategory, StepBasic_ProductCategory)

StepBasic_ProductRelatedProductCategory::StepBasic_ProductRelatedProductCategory() = default;

void StepBasic_ProductRelatedProductCategory::Init(
  const occ::handle<TCollection_HAsciiString>&                            aName,
  const bool                                                              hasAdescription,
  const occ::handle<TCollection_HAsciiString>&                            aDescription,
  const occ::handle<NCollection_HArray1<occ::handle<StepBasic_Product>>>& aProducts)
{

  products = aProducts;

  StepBasic_ProductCategory::Init(aName, hasAdescription, aDescription);
}

void StepBasic_ProductRelatedProductCategory::SetProducts(
  const occ::handle<NCollection_HArray1<occ::handle<StepBasic_Product>>>& aProducts)
{
  products = aProducts;
}

occ::handle<NCollection_HArray1<occ::handle<StepBasic_Product>>>
  StepBasic_ProductRelatedProductCategory::Products() const
{
  return products;
}

occ::handle<StepBasic_Product> StepBasic_ProductRelatedProductCategory::ProductsValue(
  const int num) const
{
  return products->Value(num);
}

int StepBasic_ProductRelatedProductCategory::NbProducts() const
{
  if (products.IsNull())
    return 0;
  return products->Length();
}
