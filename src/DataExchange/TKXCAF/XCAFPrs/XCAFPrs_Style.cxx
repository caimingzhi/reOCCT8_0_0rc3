#include <XCAFPrs_Style.hpp>

#include <Standard_Dump.hpp>

//=================================================================================================

XCAFPrs_Style::XCAFPrs_Style()
    : myHasColorSurf(false),
      myHasColorCurv(false),
      myIsVisible(true)
{
}

//=================================================================================================

void XCAFPrs_Style::SetColorSurf(const Quantity_ColorRGBA& theColor)
{
  myColorSurf    = theColor;
  myHasColorSurf = true;
}

//=================================================================================================

void XCAFPrs_Style::UnSetColorSurf()
{
  myHasColorSurf = false;
  myColorSurf.ChangeRGB().SetValues(Quantity_NOC_YELLOW);
  myColorSurf.SetAlpha(1.0f);
}

//=================================================================================================

void XCAFPrs_Style::SetColorCurv(const Quantity_Color& theColor)
{
  myColorCurv    = theColor;
  myHasColorCurv = true;
}

//=================================================================================================

void XCAFPrs_Style::UnSetColorCurv()
{
  myHasColorCurv = false;
  myColorCurv.SetValues(Quantity_NOC_YELLOW);
}

//=================================================================================================

void XCAFPrs_Style::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_CLASS_BEGIN(theOStream, XCAFPrs_Style);

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &myColorSurf)
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &myColorCurv)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myHasColorSurf)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myHasColorCurv)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myIsVisible)
}
