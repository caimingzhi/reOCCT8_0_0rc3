#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_Product.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_ProductCategory.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class StepBasic_Product;

class StepBasic_ProductRelatedProductCategory : public StepBasic_ProductCategory
{

public:
  //! Returns a ProductRelatedProductCategory
  Standard_EXPORT StepBasic_ProductRelatedProductCategory();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                            aName,
    const bool                                                              hasAdescription,
    const occ::handle<TCollection_HAsciiString>&                            aDescription,
    const occ::handle<NCollection_HArray1<occ::handle<StepBasic_Product>>>& aProducts);

  Standard_EXPORT void SetProducts(
    const occ::handle<NCollection_HArray1<occ::handle<StepBasic_Product>>>& aProducts);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepBasic_Product>>> Products() const;

  Standard_EXPORT occ::handle<StepBasic_Product> ProductsValue(const int num) const;

  Standard_EXPORT int NbProducts() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_ProductRelatedProductCategory, StepBasic_ProductCategory)

private:
  occ::handle<NCollection_HArray1<occ::handle<StepBasic_Product>>> products;
};
