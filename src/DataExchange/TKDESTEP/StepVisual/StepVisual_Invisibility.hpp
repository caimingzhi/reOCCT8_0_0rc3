#pragma once


#include <Standard.hpp>

#include <StepVisual_InvisibleItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class StepVisual_InvisibleItem;

class StepVisual_Invisibility : public Standard_Transient
{

public:
  //! Returns a Invisibility
  Standard_EXPORT StepVisual_Invisibility();

  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<StepVisual_InvisibleItem>>& aInvisibleItems);

  Standard_EXPORT void SetInvisibleItems(
    const occ::handle<NCollection_HArray1<StepVisual_InvisibleItem>>& aInvisibleItems);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepVisual_InvisibleItem>> InvisibleItems() const;

  Standard_EXPORT StepVisual_InvisibleItem InvisibleItemsValue(const int num) const;

  Standard_EXPORT int NbInvisibleItems() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_Invisibility, Standard_Transient)

private:
  occ::handle<NCollection_HArray1<StepVisual_InvisibleItem>> invisibleItems;
};

