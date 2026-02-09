#pragma once

#include <Graphic3d_AspectText3d.hpp>
#include <Graphic3d_TextPath.hpp>
#include <Graphic3d_HorizontalTextAlignment.hpp>
#include <Graphic3d_VerticalTextAlignment.hpp>
#include <Prs3d_BasicAspect.hpp>

class Prs3d_TextAspect : public Prs3d_BasicAspect
{
  DEFINE_STANDARD_RTTIEXT(Prs3d_TextAspect, Prs3d_BasicAspect)
public:
  Standard_EXPORT Prs3d_TextAspect();

  Standard_EXPORT Prs3d_TextAspect(const occ::handle<Graphic3d_AspectText3d>& theAspect);

  void SetColor(const Quantity_Color& theColor) { myTextAspect->SetColor(theColor); }

  void SetFont(const char* theFont) { myTextAspect->SetFont(theFont); }

  void SetHeight(const double theHeight) { myHeight = theHeight; }

  void SetAngle(const double theAngle) { myTextAspect->SetTextAngle(theAngle); }

  double Height() const { return myHeight; }

  double Angle() const { return myTextAspect->GetTextAngle(); }

  void SetHorizontalJustification(const Graphic3d_HorizontalTextAlignment theJustification)
  {
    myHorizontalJustification = theJustification;
  }

  void SetVerticalJustification(const Graphic3d_VerticalTextAlignment theJustification)
  {
    myVerticalJustification = theJustification;
  }

  void SetOrientation(const Graphic3d_TextPath theOrientation) { myOrientation = theOrientation; }

  Graphic3d_HorizontalTextAlignment HorizontalJustification() const
  {
    return myHorizontalJustification;
  }

  Graphic3d_VerticalTextAlignment VerticalJustification() const { return myVerticalJustification; }

  Graphic3d_TextPath Orientation() const { return myOrientation; }

  const occ::handle<Graphic3d_AspectText3d>& Aspect() const { return myTextAspect; }

  void SetAspect(const occ::handle<Graphic3d_AspectText3d>& theAspect) { myTextAspect = theAspect; }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

protected:
  occ::handle<Graphic3d_AspectText3d> myTextAspect;
  double                              myHeight;
  Graphic3d_HorizontalTextAlignment   myHorizontalJustification;
  Graphic3d_VerticalTextAlignment     myVerticalJustification;
  Graphic3d_TextPath                  myOrientation;
};
