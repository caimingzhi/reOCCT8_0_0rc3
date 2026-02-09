

#include <StepVisual_PreDefinedItem.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_PreDefinedItem, Standard_Transient)

StepVisual_PreDefinedItem::StepVisual_PreDefinedItem() = default;

void StepVisual_PreDefinedItem::Init(const occ::handle<TCollection_HAsciiString>& aName)
{

  name = aName;
}

void StepVisual_PreDefinedItem::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  name = aName;
}

occ::handle<TCollection_HAsciiString> StepVisual_PreDefinedItem::Name() const
{
  return name;
}
