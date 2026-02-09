

#include <StepRepr_Representation.hpp>
#include <StepRepr_RepresentationContext.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_Representation, Standard_Transient)

StepRepr_Representation::StepRepr_Representation() = default;

void StepRepr_Representation::Init(
  const occ::handle<TCollection_HAsciiString>&                                      aName,
  const occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>& aItems,
  const occ::handle<StepRepr_RepresentationContext>&                                aContextOfItems)
{

  name           = aName;
  items          = aItems;
  contextOfItems = aContextOfItems;
}

void StepRepr_Representation::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  name = aName;
}

occ::handle<TCollection_HAsciiString> StepRepr_Representation::Name() const
{
  return name;
}

void StepRepr_Representation::SetItems(
  const occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>& aItems)
{
  items = aItems;
}

occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> StepRepr_Representation::
  Items() const
{
  return items;
}

occ::handle<StepRepr_RepresentationItem> StepRepr_Representation::ItemsValue(const int num) const
{
  return items->Value(num);
}

int StepRepr_Representation::NbItems() const
{
  if (items.IsNull())
    return 0;
  return items->Length();
}

void StepRepr_Representation::SetContextOfItems(
  const occ::handle<StepRepr_RepresentationContext>& aContextOfItems)
{
  contextOfItems = aContextOfItems;
}

occ::handle<StepRepr_RepresentationContext> StepRepr_Representation::ContextOfItems() const
{
  return contextOfItems;
}
