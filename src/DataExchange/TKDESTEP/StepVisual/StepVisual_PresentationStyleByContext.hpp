#pragma once

#include <Standard.hpp>

#include <StepVisual_StyleContextSelect.hpp>
#include <StepVisual_PresentationStyleAssignment.hpp>
#include <StepVisual_PresentationStyleSelect.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

class StepVisual_PresentationStyleByContext : public StepVisual_PresentationStyleAssignment
{

public:
  //! Returns a PresentationStyleByContext
  Standard_EXPORT StepVisual_PresentationStyleByContext();

  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<StepVisual_PresentationStyleSelect>>& aStyles,
    const StepVisual_StyleContextSelect&                                        aStyleContext);

  Standard_EXPORT void SetStyleContext(const StepVisual_StyleContextSelect& aStyleContext);

  Standard_EXPORT StepVisual_StyleContextSelect StyleContext() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_PresentationStyleByContext,
                          StepVisual_PresentationStyleAssignment)

private:
  StepVisual_StyleContextSelect styleContext;
};
