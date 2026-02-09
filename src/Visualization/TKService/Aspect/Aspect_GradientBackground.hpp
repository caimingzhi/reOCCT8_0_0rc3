#pragma once

#include <Aspect_GradientFillMethod.hpp>
#include <Aspect_Background.hpp>

class Aspect_GradientBackground : public Aspect_Background
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Aspect_GradientBackground();

  Standard_EXPORT Aspect_GradientBackground(
    const Quantity_Color&           theColor1,
    const Quantity_Color&           theColor2,
    const Aspect_GradientFillMethod theMethod = Aspect_GradientFillMethod_Horizontal);

  Standard_EXPORT void SetColors(
    const Quantity_Color&           theColor1,
    const Quantity_Color&           theColor2,
    const Aspect_GradientFillMethod theMethod = Aspect_GradientFillMethod_Horizontal);

  Standard_EXPORT void Colors(Quantity_Color& theColor1, Quantity_Color& theColor2) const;

  Standard_EXPORT Aspect_GradientFillMethod BgGradientFillMethod() const;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

private:
  Quantity_Color            MyColor2;
  Aspect_GradientFillMethod MyGradientMethod;
};
