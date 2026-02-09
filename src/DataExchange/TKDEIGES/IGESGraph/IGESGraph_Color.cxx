#include <IGESGraph_Color.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESGraph_Color, IGESData_ColorEntity)

namespace
{

  constexpr double SQRT_3 = 1.7320508075688772935;
}

IGESGraph_Color::IGESGraph_Color() = default;

void IGESGraph_Color::Init(const double                                 red,
                           const double                                 green,
                           const double                                 blue,
                           const occ::handle<TCollection_HAsciiString>& aColorName)
{
  theRed       = red;
  theGreen     = green;
  theBlue      = blue;
  theColorName = aColorName;
  InitTypeAndForm(314, 0);
}

void IGESGraph_Color::RGBIntensity(double& Red, double& Green, double& Blue) const
{
  Red   = theRed;
  Green = theGreen;
  Blue  = theBlue;
}

void IGESGraph_Color::CMYIntensity(double& Cyan, double& Magenta, double& Yellow) const
{
  Cyan    = 100.0 - theRed;
  Magenta = 100.0 - theGreen;
  Yellow  = 100.0 - theBlue;
}

void IGESGraph_Color::HLSPercentage(double& Hue, double& Lightness, double& Saturation) const
{
  Hue        = ((1.0 / (2.0 * M_PI))
         * (std::atan(((2 * theRed) - theGreen - theBlue) / (SQRT_3 * (theGreen - theBlue)))));
  Lightness  = ((1.0 / 3.0) * (theRed + theGreen + theBlue));
  Saturation = (std::sqrt((theRed * theRed) + (theGreen * theGreen) + (theBlue * theBlue)
                          - (theRed * theGreen) - (theRed * theBlue) - (theBlue * theGreen)));
}

bool IGESGraph_Color::HasColorName() const
{
  return (!theColorName.IsNull());
}

occ::handle<TCollection_HAsciiString> IGESGraph_Color::ColorName() const
{
  return theColorName;
}
