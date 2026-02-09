

#include <StepVisual_PresentationLayerAssignment.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_PresentationLayerAssignment, Standard_Transient)

StepVisual_PresentationLayerAssignment::StepVisual_PresentationLayerAssignment() = default;

void StepVisual_PresentationLayerAssignment::Init(
  const occ::handle<TCollection_HAsciiString>&                    aName,
  const occ::handle<TCollection_HAsciiString>&                    aDescription,
  const occ::handle<NCollection_HArray1<StepVisual_LayeredItem>>& aAssignedItems)
{

  name          = aName;
  description   = aDescription;
  assignedItems = aAssignedItems;
}

void StepVisual_PresentationLayerAssignment::SetName(
  const occ::handle<TCollection_HAsciiString>& aName)
{
  name = aName;
}

occ::handle<TCollection_HAsciiString> StepVisual_PresentationLayerAssignment::Name() const
{
  return name;
}

void StepVisual_PresentationLayerAssignment::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  description = aDescription;
}

occ::handle<TCollection_HAsciiString> StepVisual_PresentationLayerAssignment::Description() const
{
  return description;
}

void StepVisual_PresentationLayerAssignment::SetAssignedItems(
  const occ::handle<NCollection_HArray1<StepVisual_LayeredItem>>& aAssignedItems)
{
  assignedItems = aAssignedItems;
}

occ::handle<NCollection_HArray1<StepVisual_LayeredItem>> StepVisual_PresentationLayerAssignment::
  AssignedItems() const
{
  return assignedItems;
}

StepVisual_LayeredItem StepVisual_PresentationLayerAssignment::AssignedItemsValue(
  const int num) const
{
  return assignedItems->Value(num);
}

int StepVisual_PresentationLayerAssignment::NbAssignedItems() const
{
  return assignedItems.IsNull() ? 0 : assignedItems->Length();
}
