#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_RepresentationItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;

//! Added for Dimensional Tolerances
class StepRepr_CompoundRepresentationItem : public StepRepr_RepresentationItem
{

public:
  Standard_EXPORT StepRepr_CompoundRepresentationItem();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                                      aName,
    const occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>& item_element);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>
                  ItemElement() const;

  Standard_EXPORT int NbItemElement() const;

  Standard_EXPORT void SetItemElement(
    const occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>& item_element);

  Standard_EXPORT occ::handle<StepRepr_RepresentationItem> ItemElementValue(const int num) const;

  Standard_EXPORT void SetItemElementValue(
    const int                                       num,
    const occ::handle<StepRepr_RepresentationItem>& anelement);

  DEFINE_STANDARD_RTTIEXT(StepRepr_CompoundRepresentationItem, StepRepr_RepresentationItem)

private:
  occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> theItemElement;
};

