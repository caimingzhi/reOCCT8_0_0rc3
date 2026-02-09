

#include <StepBasic_ProductCategory.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ProductCategory, Standard_Transient)

StepBasic_ProductCategory::StepBasic_ProductCategory() = default;

void StepBasic_ProductCategory::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                     const bool                                   hasAdescription,
                                     const occ::handle<TCollection_HAsciiString>& aDescription)
{

  name           = aName;
  hasDescription = hasAdescription;
  description    = aDescription;
}

void StepBasic_ProductCategory::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  name = aName;
}

occ::handle<TCollection_HAsciiString> StepBasic_ProductCategory::Name() const
{
  return name;
}

void StepBasic_ProductCategory::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  description    = aDescription;
  hasDescription = true;
}

void StepBasic_ProductCategory::UnSetDescription()
{
  hasDescription = false;
  description.Nullify();
}

occ::handle<TCollection_HAsciiString> StepBasic_ProductCategory::Description() const
{
  return description;
}

bool StepBasic_ProductCategory::HasDescription() const
{
  return hasDescription;
}
