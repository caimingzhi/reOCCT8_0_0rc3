#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepBasic_Product;

class StepBasic_ProductDefinitionFormation : public Standard_Transient
{

public:
  //! Returns a ProductDefinitionFormation
  Standard_EXPORT StepBasic_ProductDefinitionFormation();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aId,
                            const occ::handle<TCollection_HAsciiString>& aDescription,
                            const occ::handle<StepBasic_Product>&        aOfProduct);

  Standard_EXPORT void SetId(const occ::handle<TCollection_HAsciiString>& aId);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Id() const;

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& aDescription);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  Standard_EXPORT void SetOfProduct(const occ::handle<StepBasic_Product>& aOfProduct);

  Standard_EXPORT occ::handle<StepBasic_Product> OfProduct() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_ProductDefinitionFormation, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> id;
  occ::handle<TCollection_HAsciiString> description;
  occ::handle<StepBasic_Product>        ofProduct;
};

