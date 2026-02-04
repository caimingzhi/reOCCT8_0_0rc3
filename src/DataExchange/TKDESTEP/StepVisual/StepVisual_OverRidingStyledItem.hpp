#pragma once


#include <Standard.hpp>

#include <StepVisual_StyledItem.hpp>
#include <StepVisual_PresentationStyleAssignment.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class TCollection_HAsciiString;

class StepVisual_OverRidingStyledItem : public StepVisual_StyledItem
{

public:
  //! Returns a OverRidingStyledItem
  Standard_EXPORT StepVisual_OverRidingStyledItem();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aName,
    const occ::handle<NCollection_HArray1<occ::handle<StepVisual_PresentationStyleAssignment>>>&
                                              aStyles,
    const occ::handle<Standard_Transient>&    aItem,
    const occ::handle<StepVisual_StyledItem>& aOverRiddenStyle);

  Standard_EXPORT void SetOverRiddenStyle(
    const occ::handle<StepVisual_StyledItem>& aOverRiddenStyle);

  Standard_EXPORT occ::handle<StepVisual_StyledItem> OverRiddenStyle() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_OverRidingStyledItem, StepVisual_StyledItem)

private:
  occ::handle<StepVisual_StyledItem> overRiddenStyle;
};

