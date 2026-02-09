#pragma once

#include <Prs3d_ArrowAspect.hpp>

enum Prs3d_DimensionArrowOrientation
{
  Prs3d_DAO_Internal,
  Prs3d_DAO_External,
  Prs3d_DAO_Fit
};

enum Prs3d_DimensionTextHorizontalPosition
{
  Prs3d_DTHP_Left,
  Prs3d_DTHP_Right,
  Prs3d_DTHP_Center,
  Prs3d_DTHP_Fit
};

enum Prs3d_DimensionTextVerticalPosition
{
  Prs3d_DTVP_Above,
  Prs3d_DTVP_Below,
  Prs3d_DTVP_Center
};

#include <Prs3d_LineAspect.hpp>
#include <Prs3d_TextAspect.hpp>
#include <TCollection_AsciiString.hpp>

class Prs3d_DimensionAspect : public Prs3d_BasicAspect
{
  DEFINE_STANDARD_RTTIEXT(Prs3d_DimensionAspect, Prs3d_BasicAspect)
public:
  Standard_EXPORT Prs3d_DimensionAspect();

  const occ::handle<Prs3d_LineAspect>& LineAspect() const { return myLineAspect; }

  void SetLineAspect(const occ::handle<Prs3d_LineAspect>& theAspect) { myLineAspect = theAspect; }

  const occ::handle<Prs3d_TextAspect>& TextAspect() const { return myTextAspect; }

  void SetTextAspect(const occ::handle<Prs3d_TextAspect>& theAspect) { myTextAspect = theAspect; }

  bool IsText3d() const { return myIsText3d; }

  void MakeText3d(const bool isText3d) { myIsText3d = isText3d; }

  bool IsTextShaded() const { return myIsTextShaded; }

  void MakeTextShaded(const bool theIsTextShaded) { myIsTextShaded = theIsTextShaded; }

  bool IsArrows3d() const { return myIsArrows3d; }

  void MakeArrows3d(const bool theIsArrows3d) { myIsArrows3d = theIsArrows3d; }

  bool IsUnitsDisplayed() const { return myToDisplayUnits; }

  void MakeUnitsDisplayed(const bool theIsDisplayed) { myToDisplayUnits = theIsDisplayed; }

  void SetArrowOrientation(const Prs3d_DimensionArrowOrientation theArrowOrient)
  {
    myArrowOrientation = theArrowOrient;
  }

  Prs3d_DimensionArrowOrientation ArrowOrientation() const { return myArrowOrientation; }

  void SetTextVerticalPosition(const Prs3d_DimensionTextVerticalPosition thePosition)
  {
    myTextVPosition = thePosition;
  }

  Prs3d_DimensionTextVerticalPosition TextVerticalPosition() const { return myTextVPosition; }

  void SetTextHorizontalPosition(const Prs3d_DimensionTextHorizontalPosition thePosition)
  {
    myTextHPosition = thePosition;
  }

  Prs3d_DimensionTextHorizontalPosition TextHorizontalPosition() const { return myTextHPosition; }

  const occ::handle<Prs3d_ArrowAspect>& ArrowAspect() const { return myArrowAspect; }

  void SetArrowAspect(const occ::handle<Prs3d_ArrowAspect>& theAspect)
  {
    myArrowAspect = theAspect;
  }

  Standard_EXPORT void SetCommonColor(const Quantity_Color& theColor);

  void SetExtensionSize(const double theSize) { myExtensionSize = theSize; }

  double ExtensionSize() const { return myExtensionSize; }

  void SetArrowTailSize(const double theSize) { myArrowTailSize = theSize; }

  double ArrowTailSize() const { return myArrowTailSize; }

  void SetValueStringFormat(const TCollection_AsciiString& theFormat)
  {
    myValueStringFormat = theFormat;
  }

  const TCollection_AsciiString& ValueStringFormat() const { return myValueStringFormat; }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

protected:
  occ::handle<Prs3d_LineAspect>         myLineAspect;
  occ::handle<Prs3d_TextAspect>         myTextAspect;
  occ::handle<Prs3d_ArrowAspect>        myArrowAspect;
  TCollection_AsciiString               myValueStringFormat;
  double                                myExtensionSize;
  double                                myArrowTailSize;
  Prs3d_DimensionArrowOrientation       myArrowOrientation;
  Prs3d_DimensionTextHorizontalPosition myTextHPosition;
  Prs3d_DimensionTextVerticalPosition   myTextVPosition;
  bool                                  myToDisplayUnits;
  bool                                  myIsText3d;
  bool                                  myIsTextShaded;
  bool                                  myIsArrows3d;
};
