#include <Aspect_GradientBackground.hpp>

Aspect_GradientBackground::Aspect_GradientBackground()
{

  Quantity_Color Black(Quantity_NOC_BLACK);

  SetColor(Black);
  MyColor2         = Black;
  MyGradientMethod = Aspect_GradientFillMethod_None;
}

Aspect_GradientBackground::Aspect_GradientBackground(const Quantity_Color&           AColor1,
                                                     const Quantity_Color&           AColor2,
                                                     const Aspect_GradientFillMethod AMethod)
{
  SetColor(AColor1);
  MyColor2         = AColor2;
  MyGradientMethod = AMethod;
}

void Aspect_GradientBackground::SetColors(const Quantity_Color&           AColor1,
                                          const Quantity_Color&           AColor2,
                                          const Aspect_GradientFillMethod AMethod)
{
  SetColor(AColor1);
  MyColor2         = AColor2;
  MyGradientMethod = AMethod;
}

void Aspect_GradientBackground::Colors(Quantity_Color& AColor1, Quantity_Color& AColor2) const
{
  AColor1 = Color();
  AColor2 = MyColor2;
}

Aspect_GradientFillMethod Aspect_GradientBackground::BgGradientFillMethod() const
{
  return MyGradientMethod;
}

//=================================================================================================

void Aspect_GradientBackground::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_CLASS_BEGIN(theOStream, Aspect_GradientBackground)

  Quantity_Color aColor = Color();
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &aColor)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &MyColor2)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, MyGradientMethod)
}
