

#include <StepVisual_Colour.hpp>
#include <StepVisual_FillAreaStyleColour.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_FillAreaStyleColour, Standard_Transient)

StepVisual_FillAreaStyleColour::StepVisual_FillAreaStyleColour() = default;

void StepVisual_FillAreaStyleColour::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                          const occ::handle<StepVisual_Colour>&        aFillColour)
{

  name       = aName;
  fillColour = aFillColour;
}

void StepVisual_FillAreaStyleColour::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  name = aName;
}

occ::handle<TCollection_HAsciiString> StepVisual_FillAreaStyleColour::Name() const
{
  return name;
}

void StepVisual_FillAreaStyleColour::SetFillColour(
  const occ::handle<StepVisual_Colour>& aFillColour)
{
  fillColour = aFillColour;
}

occ::handle<StepVisual_Colour> StepVisual_FillAreaStyleColour::FillColour() const
{
  return fillColour;
}
