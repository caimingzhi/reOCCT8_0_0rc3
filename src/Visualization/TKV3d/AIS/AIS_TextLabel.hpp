#pragma once

#include <AIS_InteractiveObject.hpp>

#include <gp_Pnt.hpp>
#include <gp_Ax2.hpp>
#include <Graphic3d_VerticalTextAlignment.hpp>
#include <Graphic3d_HorizontalTextAlignment.hpp>
#include <Font_FontAspect.hpp>
#include <TCollection_ExtendedString.hpp>

class Font_TextFormatter;

class AIS_TextLabel : public AIS_InteractiveObject
{
public:
  Standard_EXPORT AIS_TextLabel();

  bool AcceptDisplayMode(const int theMode) const override { return theMode == 0; }

  Standard_EXPORT void SetColor(const Quantity_Color& theColor) override;

  Standard_EXPORT void SetTransparency(const double theValue) override;

  void UnsetTransparency() override { SetTransparency(0.0); }

  void SetMaterial(const Graphic3d_MaterialAspect&) override {}

  Standard_EXPORT void SetText(const TCollection_ExtendedString& theText);

  Standard_EXPORT void SetPosition(const gp_Pnt& thePosition);

  Standard_EXPORT void SetHJustification(const Graphic3d_HorizontalTextAlignment theHJust);

  Standard_EXPORT void SetVJustification(const Graphic3d_VerticalTextAlignment theVJust);

  Standard_EXPORT void SetAngle(const double theAngle);

  Standard_EXPORT void SetZoomable(const bool theIsZoomable);

  Standard_EXPORT void SetHeight(const double theHeight);

  Standard_EXPORT void SetFontAspect(const Font_FontAspect theFontAspect);

  Standard_EXPORT void SetFont(const char* theFont);

  Standard_EXPORT void SetOrientation3D(const gp_Ax2& theOrientation);

  Standard_EXPORT void UnsetOrientation3D();

  Standard_EXPORT const gp_Pnt& Position() const;

  const TCollection_ExtendedString& Text() const { return myText; }

  Standard_EXPORT const TCollection_AsciiString& FontName() const;

  Standard_EXPORT Font_FontAspect FontAspect() const;

  Standard_EXPORT const gp_Ax2& Orientation3D() const;

  Standard_EXPORT bool HasOrientation3D() const;

  Standard_EXPORT void SetFlipping(const bool theIsFlipping);

  Standard_EXPORT bool HasFlipping() const;

  bool HasOwnAnchorPoint() const { return myHasOwnAnchorPoint; }

  void SetOwnAnchorPoint(const bool theOwnAnchorPoint) { myHasOwnAnchorPoint = theOwnAnchorPoint; }

  Standard_EXPORT void SetDisplayType(const Aspect_TypeOfDisplayText theDisplayType);

  Standard_EXPORT void SetColorSubTitle(const Quantity_Color& theColor);

  const occ::handle<Font_TextFormatter>& TextFormatter() const { return myFormatter; }

  void SetTextFormatter(const occ::handle<Font_TextFormatter>& theFormatter)
  {
    myFormatter = theFormatter;
  }

protected:
  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& theprsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSelection,
                                        const int                               theMode) override;

  Standard_EXPORT bool calculateLabelParams(const gp_Pnt& thePosition,
                                            gp_Pnt&       theCenterOfLabel,
                                            double&       theWidth,
                                            double&       theHeight) const;

  Standard_EXPORT gp_Trsf calculateLabelTrsf(const gp_Pnt& thePosition,
                                             gp_Pnt&       theCenterOfLabel) const;

protected:
  occ::handle<Font_TextFormatter> myFormatter;

  TCollection_ExtendedString myText;
  gp_Ax2                     myOrientation3D;
  bool                       myHasOrientation3D;
  bool                       myHasOwnAnchorPoint;
  bool                       myHasFlipping;

public:
  DEFINE_STANDARD_RTTIEXT(AIS_TextLabel, AIS_InteractiveObject)
};
