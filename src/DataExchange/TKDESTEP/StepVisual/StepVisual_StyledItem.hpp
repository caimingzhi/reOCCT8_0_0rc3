#pragma once


#include <Standard.hpp>

#include <StepVisual_PresentationStyleAssignment.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepVisual_StyledItemTarget.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class StepVisual_PresentationStyleAssignment;

class StepVisual_StyledItem : public StepRepr_RepresentationItem
{

public:
  //! Returns a StyledItem
  StepVisual_StyledItem() = default;

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aName,
    const occ::handle<NCollection_HArray1<occ::handle<StepVisual_PresentationStyleAssignment>>>&
                                           aStyles,
    const occ::handle<Standard_Transient>& aItem);

  Standard_EXPORT void SetStyles(
    const occ::handle<NCollection_HArray1<occ::handle<StepVisual_PresentationStyleAssignment>>>&
      aStyles);

  const occ::handle<NCollection_HArray1<occ::handle<StepVisual_PresentationStyleAssignment>>>&
    Styles() const
  {
    return myStyles;
  }

  const occ::handle<StepVisual_PresentationStyleAssignment>& StylesValue(const int num) const
  {
    return myStyles->Value(num);
  }

  int NbStyles() const { return myStyles.IsNull() ? 0 : myStyles->Length(); }

  Standard_EXPORT void SetItem(const occ::handle<StepRepr_RepresentationItem>& aItem);

  const occ::handle<StepRepr_RepresentationItem>& Item() const { return myReprItem; }

  Standard_EXPORT void SetItem(const StepVisual_StyledItemTarget& aItem);

  Standard_EXPORT StepVisual_StyledItemTarget ItemAP242() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_StyledItem, StepRepr_RepresentationItem)

private:
  occ::handle<NCollection_HArray1<occ::handle<StepVisual_PresentationStyleAssignment>>> myStyles;
  //! May be StepRepr_RepresentationItem for AP214(203) and StepVisual_StyledItemTarget for AP242
  occ::handle<Standard_Transient> myItem;
  //! This is downcasted from myItem
  occ::handle<StepRepr_RepresentationItem> myReprItem;
};

