#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepVisual_LayeredItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class StepVisual_LayeredItem;

class StepVisual_PresentationLayerAssignment : public Standard_Transient
{

public:
  //! Returns a PresentationLayerAssignment
  Standard_EXPORT StepVisual_PresentationLayerAssignment();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                    aName,
    const occ::handle<TCollection_HAsciiString>&                    aDescription,
    const occ::handle<NCollection_HArray1<StepVisual_LayeredItem>>& aAssignedItems);

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& aName);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& aDescription);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  Standard_EXPORT void SetAssignedItems(
    const occ::handle<NCollection_HArray1<StepVisual_LayeredItem>>& aAssignedItems);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepVisual_LayeredItem>> AssignedItems() const;

  Standard_EXPORT StepVisual_LayeredItem AssignedItemsValue(const int num) const;

  Standard_EXPORT int NbAssignedItems() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_PresentationLayerAssignment, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>                    name;
  occ::handle<TCollection_HAsciiString>                    description;
  occ::handle<NCollection_HArray1<StepVisual_LayeredItem>> assignedItems;
};
