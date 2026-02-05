#include <Aspect_Background.hpp>
#include <Aspect_Window.hpp>
#include <Aspect_WindowDefinitionError.hpp>
#include <Quantity_Color.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Aspect_Window, Standard_Transient)

//-Aliases
//-Global data definitions
//-Destructors
//-Constructors
Aspect_Window::Aspect_Window()
    : MyBackgroundFillMethod(Aspect_FM_NONE)
{
}

Aspect_Background Aspect_Window::Background() const
{
  return MyBackground;
}

Aspect_FillMethod Aspect_Window::BackgroundFillMethod() const
{
  return MyBackgroundFillMethod;
}

Aspect_GradientBackground Aspect_Window::GradientBackground() const
{
  return MyGradientBackground;
}

bool Aspect_Window::IsVirtual() const
{
  return MyIsVirtual;
}

void Aspect_Window::SetVirtual(const bool theVirtual)
{
  MyIsVirtual = theVirtual;
}

void Aspect_Window::SetBackground(const Aspect_Background& theBackground)
{
  SetBackground(theBackground.Color());
}

void Aspect_Window::SetBackground(const Quantity_Color& theColor)
{
  MyBackground.SetColor(theColor);
}

void Aspect_Window::SetBackground(const Aspect_GradientBackground& theBackground)
{
  Quantity_Color aFirstColor, aSecondColor;
  theBackground.Colors(aFirstColor, aSecondColor);
  SetBackground(aFirstColor, aSecondColor, theBackground.BgGradientFillMethod());
}

void Aspect_Window::SetBackground(const Quantity_Color&           theFirstColor,
                                  const Quantity_Color&           theSecondColor,
                                  const Aspect_GradientFillMethod theFillMethod)
{
  MyGradientBackground.SetColors(theFirstColor, theSecondColor, theFillMethod);
}

//=================================================================================================

void Aspect_Window::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &MyBackground)
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &MyGradientBackground)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, MyBackgroundFillMethod)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, MyIsVirtual)
}
