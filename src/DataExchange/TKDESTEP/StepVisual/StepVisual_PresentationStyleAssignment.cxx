

#include <StepVisual_PresentationStyleAssignment.hpp>
#include <StepVisual_PresentationStyleSelect.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_PresentationStyleAssignment, Standard_Transient)

StepVisual_PresentationStyleAssignment::StepVisual_PresentationStyleAssignment() = default;

void StepVisual_PresentationStyleAssignment::Init(
  const occ::handle<NCollection_HArray1<StepVisual_PresentationStyleSelect>>& aStyles)
{

  styles = aStyles;
}

void StepVisual_PresentationStyleAssignment::SetStyles(
  const occ::handle<NCollection_HArray1<StepVisual_PresentationStyleSelect>>& aStyles)
{
  styles = aStyles;
}

occ::handle<NCollection_HArray1<StepVisual_PresentationStyleSelect>>
  StepVisual_PresentationStyleAssignment::Styles() const
{
  return styles;
}

StepVisual_PresentationStyleSelect StepVisual_PresentationStyleAssignment::StylesValue(
  const int num) const
{
  return styles->Value(num);
}

int StepVisual_PresentationStyleAssignment::NbStyles() const
{
  return (styles.IsNull()) ? 0 : styles->Length();
}
