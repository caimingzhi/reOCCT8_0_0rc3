

#include <StepVisual_FillAreaStyle.hpp>
#include <StepVisual_FillStyleSelect.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_FillAreaStyle, Standard_Transient)

StepVisual_FillAreaStyle::StepVisual_FillAreaStyle() = default;

void StepVisual_FillAreaStyle::Init(
  const occ::handle<TCollection_HAsciiString>&                        aName,
  const occ::handle<NCollection_HArray1<StepVisual_FillStyleSelect>>& aFillStyles)
{

  name       = aName;
  fillStyles = aFillStyles;
}

void StepVisual_FillAreaStyle::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  name = aName;
}

occ::handle<TCollection_HAsciiString> StepVisual_FillAreaStyle::Name() const
{
  return name;
}

void StepVisual_FillAreaStyle::SetFillStyles(
  const occ::handle<NCollection_HArray1<StepVisual_FillStyleSelect>>& aFillStyles)
{
  fillStyles = aFillStyles;
}

occ::handle<NCollection_HArray1<StepVisual_FillStyleSelect>> StepVisual_FillAreaStyle::FillStyles()
  const
{
  return fillStyles;
}

StepVisual_FillStyleSelect StepVisual_FillAreaStyle::FillStylesValue(const int num) const
{
  return fillStyles->Value(num);
}

int StepVisual_FillAreaStyle::NbFillStyles() const
{
  return (fillStyles.IsNull() ? 0 : fillStyles->Length());
}
