#pragma once

#include <Standard.hpp>

#include <StepVisual_InvisibilityContext.hpp>
#include <StepVisual_Invisibility.hpp>
#include <StepVisual_InvisibleItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

class StepVisual_ContextDependentInvisibility : public StepVisual_Invisibility
{

public:
  //! Returns a ContextDependentInvisibility
  Standard_EXPORT StepVisual_ContextDependentInvisibility();

  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<StepVisual_InvisibleItem>>& aInvisibleItems,
    const StepVisual_InvisibilityContext&                             aPresentationContext);

  Standard_EXPORT void SetPresentationContext(
    const StepVisual_InvisibilityContext& aPresentationContext);

  Standard_EXPORT StepVisual_InvisibilityContext PresentationContext() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_ContextDependentInvisibility, StepVisual_Invisibility)

private:
  StepVisual_InvisibilityContext presentationContext;
};
