#pragma once

#include <Aspect_GradientFillMethod.hpp>
#include <Aspect_Background.hpp>

//! This class allows the definition of a window gradient background.
class Aspect_GradientBackground : public Aspect_Background
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates a window gradient background.
  //! Default color is Quantity_NOC_BLACK.
  //! Default fill method is Aspect_GradientFillMethod_None.
  Standard_EXPORT Aspect_GradientBackground();

  //! Creates a window gradient background with two colours.
  Standard_EXPORT Aspect_GradientBackground(
    const Quantity_Color&           theColor1,
    const Quantity_Color&           theColor2,
    const Aspect_GradientFillMethod theMethod = Aspect_GradientFillMethod_Horizontal);

  //! Modifies the colours of the window gradient background.
  Standard_EXPORT void SetColors(
    const Quantity_Color&           theColor1,
    const Quantity_Color&           theColor2,
    const Aspect_GradientFillMethod theMethod = Aspect_GradientFillMethod_Horizontal);

  //! Returns colours of the window gradient background.
  Standard_EXPORT void Colors(Quantity_Color& theColor1, Quantity_Color& theColor2) const;

  //! Returns the current gradient background fill mode.
  Standard_EXPORT Aspect_GradientFillMethod BgGradientFillMethod() const;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

private:
  Quantity_Color            MyColor2;
  Aspect_GradientFillMethod MyGradientMethod;
};
