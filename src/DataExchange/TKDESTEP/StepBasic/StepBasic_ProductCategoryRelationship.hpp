#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepBasic_ProductCategory;

//! Representation of STEP entity ProductCategoryRelationship
class StepBasic_ProductCategoryRelationship : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepBasic_ProductCategoryRelationship();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&  aName,
                            const bool                                    hasDescription,
                            const occ::handle<TCollection_HAsciiString>&  aDescription,
                            const occ::handle<StepBasic_ProductCategory>& aCategory,
                            const occ::handle<StepBasic_ProductCategory>& aSubCategory);

  //! Returns field Name
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  //! Set field Name
  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& Name);

  //! Returns field Description
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  //! Set field Description
  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& Description);

  //! Returns True if optional field Description is defined
  Standard_EXPORT bool HasDescription() const;

  //! Returns field Category
  Standard_EXPORT occ::handle<StepBasic_ProductCategory> Category() const;

  //! Set field Category
  Standard_EXPORT void SetCategory(const occ::handle<StepBasic_ProductCategory>& Category);

  //! Returns field SubCategory
  Standard_EXPORT occ::handle<StepBasic_ProductCategory> SubCategory() const;

  //! Set field SubCategory
  Standard_EXPORT void SetSubCategory(const occ::handle<StepBasic_ProductCategory>& SubCategory);

  DEFINE_STANDARD_RTTIEXT(StepBasic_ProductCategoryRelationship, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>  theName;
  occ::handle<TCollection_HAsciiString>  theDescription;
  occ::handle<StepBasic_ProductCategory> theCategory;
  occ::handle<StepBasic_ProductCategory> theSubCategory;
  bool                                   defDescription;
};

