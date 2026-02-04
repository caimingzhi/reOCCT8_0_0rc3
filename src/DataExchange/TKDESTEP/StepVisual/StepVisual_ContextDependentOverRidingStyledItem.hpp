#pragma once


#include <Standard.hpp>

#include <StepVisual_StyleContextSelect.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepVisual_OverRidingStyledItem.hpp>
#include <StepVisual_PresentationStyleAssignment.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class StepVisual_StyledItem;
class StepVisual_StyleContextSelect;

class StepVisual_ContextDependentOverRidingStyledItem : public StepVisual_OverRidingStyledItem
{

public:
  //! Returns a ContextDependentOverRidingStyledItem
  Standard_EXPORT StepVisual_ContextDependentOverRidingStyledItem();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aName,
    const occ::handle<NCollection_HArray1<occ::handle<StepVisual_PresentationStyleAssignment>>>&
                                                                           aStyles,
    const occ::handle<Standard_Transient>&                                 aItem,
    const occ::handle<StepVisual_StyledItem>&                              aOverRiddenStyle,
    const occ::handle<NCollection_HArray1<StepVisual_StyleContextSelect>>& aStyleContext);

  Standard_EXPORT void SetStyleContext(
    const occ::handle<NCollection_HArray1<StepVisual_StyleContextSelect>>& aStyleContext);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepVisual_StyleContextSelect>> StyleContext()
    const;

  Standard_EXPORT StepVisual_StyleContextSelect StyleContextValue(const int num) const;

  Standard_EXPORT int NbStyleContext() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_ContextDependentOverRidingStyledItem,
                          StepVisual_OverRidingStyledItem)

private:
  occ::handle<NCollection_HArray1<StepVisual_StyleContextSelect>> styleContext;
};

