#include <StepBasic_ProductCategory.hpp>
#include <StepBasic_ProductCategoryRelationship.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ProductCategoryRelationship, Standard_Transient)

StepBasic_ProductCategoryRelationship::StepBasic_ProductCategoryRelationship()
{
  defDescription = false;
}

void StepBasic_ProductCategoryRelationship::Init(
  const occ::handle<TCollection_HAsciiString>&  aName,
  const bool                                    hasDescription,
  const occ::handle<TCollection_HAsciiString>&  aDescription,
  const occ::handle<StepBasic_ProductCategory>& aCategory,
  const occ::handle<StepBasic_ProductCategory>& aSubCategory)
{

  theName = aName;

  defDescription = hasDescription;
  if (defDescription)
  {
    theDescription = aDescription;
  }
  else
    theDescription.Nullify();

  theCategory = aCategory;

  theSubCategory = aSubCategory;
}

occ::handle<TCollection_HAsciiString> StepBasic_ProductCategoryRelationship::Name() const
{
  return theName;
}

void StepBasic_ProductCategoryRelationship::SetName(
  const occ::handle<TCollection_HAsciiString>& aName)
{
  theName = aName;
}

occ::handle<TCollection_HAsciiString> StepBasic_ProductCategoryRelationship::Description() const
{
  return theDescription;
}

void StepBasic_ProductCategoryRelationship::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  theDescription = aDescription;
}

bool StepBasic_ProductCategoryRelationship::HasDescription() const
{
  return defDescription;
}

occ::handle<StepBasic_ProductCategory> StepBasic_ProductCategoryRelationship::Category() const
{
  return theCategory;
}

void StepBasic_ProductCategoryRelationship::SetCategory(
  const occ::handle<StepBasic_ProductCategory>& aCategory)
{
  theCategory = aCategory;
}

occ::handle<StepBasic_ProductCategory> StepBasic_ProductCategoryRelationship::SubCategory() const
{
  return theSubCategory;
}

void StepBasic_ProductCategoryRelationship::SetSubCategory(
  const occ::handle<StepBasic_ProductCategory>& aSubCategory)
{
  theSubCategory = aSubCategory;
}
