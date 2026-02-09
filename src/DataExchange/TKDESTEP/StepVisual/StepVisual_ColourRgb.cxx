

#include <StepVisual_ColourRgb.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_ColourRgb, StepVisual_ColourSpecification)

StepVisual_ColourRgb::StepVisual_ColourRgb() = default;

void StepVisual_ColourRgb::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                const double                                 aRed,
                                const double                                 aGreen,
                                const double                                 aBlue)
{

  red   = aRed;
  green = aGreen;
  blue  = aBlue;

  StepVisual_ColourSpecification::Init(aName);
}

void StepVisual_ColourRgb::SetRed(const double aRed)
{
  red = aRed;
}

double StepVisual_ColourRgb::Red() const
{
  return red;
}

void StepVisual_ColourRgb::SetGreen(const double aGreen)
{
  green = aGreen;
}

double StepVisual_ColourRgb::Green() const
{
  return green;
}

void StepVisual_ColourRgb::SetBlue(const double aBlue)
{
  blue = aBlue;
}

double StepVisual_ColourRgb::Blue() const
{
  return blue;
}
