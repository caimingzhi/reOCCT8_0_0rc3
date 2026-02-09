#pragma once

#include <Standard.hpp>

#include <StepVisual_PresentationStyleSelect.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class StepVisual_PresentationStyleSelect;

class StepVisual_PresentationStyleAssignment : public Standard_Transient
{

public:
  Standard_EXPORT StepVisual_PresentationStyleAssignment();

  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<StepVisual_PresentationStyleSelect>>& aStyles);

  Standard_EXPORT void SetStyles(
    const occ::handle<NCollection_HArray1<StepVisual_PresentationStyleSelect>>& aStyles);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepVisual_PresentationStyleSelect>> Styles()
    const;

  Standard_EXPORT StepVisual_PresentationStyleSelect StylesValue(const int num) const;

  Standard_EXPORT int NbStyles() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_PresentationStyleAssignment, Standard_Transient)

private:
  occ::handle<NCollection_HArray1<StepVisual_PresentationStyleSelect>> styles;
};
