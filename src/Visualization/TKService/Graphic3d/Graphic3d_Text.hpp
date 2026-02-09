#pragma once

#include <gp_Ax2.hpp>

#include <Font_TextFormatter.hpp>
#include <Graphic3d_HorizontalTextAlignment.hpp>
#include <Graphic3d_VerticalTextAlignment.hpp>
#include <NCollection_String.hpp>
#include <Standard_Type.hpp>
#include <Standard_Transient.hpp>
#include <TCollection_AsciiString.hpp>

class Graphic3d_Text : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_Text, Standard_Transient)

public:
  Standard_EXPORT Graphic3d_Text(const float theHeight);

  ~Graphic3d_Text() override = default;

  const NCollection_String& Text() const { return myText; }

  void SetText(const NCollection_String& theText) { myText = theText; }

  void SetText(const TCollection_AsciiString& theText) { myText = theText.ToCString(); }

  void SetText(const char* theText) { myText = theText; }

  const occ::handle<Font_TextFormatter>& TextFormatter() const { return myFormatter; }

  void SetTextFormatter(const occ::handle<Font_TextFormatter>& theFormatter)
  {
    myFormatter = theFormatter;
  }

  const gp_Pnt& Position() const { return myOrientation.Location(); }

  void SetPosition(const gp_Pnt& thePoint) { myOrientation.SetLocation(thePoint); }

  const gp_Ax2& Orientation() const { return myOrientation; }

  bool HasPlane() const { return myHasPlane; }

  Standard_EXPORT void SetOrientation(const gp_Ax2& theOrientation);

  Standard_EXPORT void ResetOrientation();

  bool HasOwnAnchorPoint() const { return myHasOwnAnchor; }

  void SetOwnAnchorPoint(const bool theHasOwnAnchor) { myHasOwnAnchor = theHasOwnAnchor; }

  float Height() const { return myHeight; }

  void SetHeight(const float theHeight) { myHeight = theHeight; }

  Graphic3d_HorizontalTextAlignment HorizontalAlignment() const { return myHAlign; }

  void SetHorizontalAlignment(const Graphic3d_HorizontalTextAlignment theJustification)
  {
    myHAlign = theJustification;
  }

  Graphic3d_VerticalTextAlignment VerticalAlignment() const { return myVAlign; }

  void SetVerticalAlignment(const Graphic3d_VerticalTextAlignment theJustification)
  {
    myVAlign = theJustification;
  }

protected:
  occ::handle<Font_TextFormatter> myFormatter;

  NCollection_String myText;
  gp_Ax2             myOrientation;

  float                             myHeight;
  Graphic3d_HorizontalTextAlignment myHAlign;
  Graphic3d_VerticalTextAlignment   myVAlign;

  bool myHasPlane;
  bool myHasOwnAnchor;
};
