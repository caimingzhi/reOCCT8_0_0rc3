#pragma once

#include <Graphic3d_Aspects.hpp>

class Graphic3d_AspectText3d : public Graphic3d_Aspects
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_AspectText3d, Graphic3d_Aspects)
public:
  Standard_EXPORT Graphic3d_AspectText3d();

  Standard_EXPORT Graphic3d_AspectText3d(
    const Quantity_Color&    theColor,
    const char*              theFont,
    double                   theExpansionFactor,
    double                   theSpace,
    Aspect_TypeOfStyleText   theStyle       = Aspect_TOST_NORMAL,
    Aspect_TypeOfDisplayText theDisplayType = Aspect_TODT_NORMAL);

  const Quantity_Color& Color() const { return myInteriorColor.GetRGB(); }

  const Quantity_ColorRGBA& ColorRGBA() const { return myInteriorColor; }

  void SetColor(const Quantity_Color& theColor) { myInteriorColor.SetRGB(theColor); }

  void SetColor(const Quantity_ColorRGBA& theColor) { myInteriorColor = theColor; }

  const TCollection_AsciiString& Font() const
  {
    if (myTextFont.IsNull())
    {
      return TCollection_AsciiString::EmptyString();
    }
    return myTextFont->String();
  }

  void SetFont(const TCollection_AsciiString& theFont)
  {
    if (!theFont.IsEmpty())
    {
      myTextFont = new TCollection_HAsciiString(theFont);
    }
    else
    {
      myTextFont.Nullify();
    }
  }

  void SetFont(const char* theFont) { SetFont(TCollection_AsciiString(theFont)); }

  Aspect_TypeOfStyleText Style() const { return myTextStyle; }

  void SetStyle(Aspect_TypeOfStyleText theStyle) { myTextStyle = theStyle; }

  Aspect_TypeOfDisplayText DisplayType() const { return myTextDisplayType; }

  void SetDisplayType(Aspect_TypeOfDisplayText theDisplayType)
  {
    myTextDisplayType = theDisplayType;
  }

  bool GetTextZoomable() const { return myIsTextZoomable; }

  float GetTextAngle() const { return myTextAngle; }

  void SetTextAngle(const double theAngle) { myTextAngle = (float)theAngle; }

  Font_FontAspect GetTextFontAspect() const { return myTextFontAspect; }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;
};
