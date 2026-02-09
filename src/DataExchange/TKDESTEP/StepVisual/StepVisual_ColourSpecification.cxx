

#include <StepVisual_ColourSpecification.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_ColourSpecification, StepVisual_Colour)

StepVisual_ColourSpecification::StepVisual_ColourSpecification() = default;

void StepVisual_ColourSpecification::Init(const occ::handle<TCollection_HAsciiString>& aName)
{

  name = aName;
}

void StepVisual_ColourSpecification::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  name = aName;
}

occ::handle<TCollection_HAsciiString> StepVisual_ColourSpecification::Name() const
{
  return name;
}
