#pragma once

#include <Standard.hpp>

#include <StepAP214_AutoDesignPresentedItemSelect.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepVisual_PresentedItem.hpp>
#include <Standard_Integer.hpp>
class StepAP214_AutoDesignPresentedItemSelect;

class StepAP214_AutoDesignPresentedItem : public StepVisual_PresentedItem
{

public:
  //! Returns a AutoDesignPresentedItem
  Standard_EXPORT StepAP214_AutoDesignPresentedItem();

  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<StepAP214_AutoDesignPresentedItemSelect>>& aItems);

  Standard_EXPORT void SetItems(
    const occ::handle<NCollection_HArray1<StepAP214_AutoDesignPresentedItemSelect>>& aItems);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepAP214_AutoDesignPresentedItemSelect>> Items()
    const;

  Standard_EXPORT StepAP214_AutoDesignPresentedItemSelect ItemsValue(const int num) const;

  Standard_EXPORT int NbItems() const;

  DEFINE_STANDARD_RTTIEXT(StepAP214_AutoDesignPresentedItem, StepVisual_PresentedItem)

private:
  occ::handle<NCollection_HArray1<StepAP214_AutoDesignPresentedItemSelect>> items;
};
