

#include <Prs3d_DimensionAspect.hpp>

#include <Aspect_TypeOfLine.hpp>
#include <Graphic3d_AspectText3d.hpp>
#include <Standard_Dump.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Prs3d_DimensionAspect, Prs3d_BasicAspect)

Prs3d_DimensionAspect::Prs3d_DimensionAspect()
    : myLineAspect(new Prs3d_LineAspect(Quantity_NOC_LAWNGREEN, Aspect_TOL_SOLID, 1.0)),
      myTextAspect(new Prs3d_TextAspect()),
      myArrowAspect(new Prs3d_ArrowAspect()),
      myValueStringFormat("%g"),
      myExtensionSize(6.0),
      myArrowTailSize(6.0),
      myArrowOrientation(Prs3d_DAO_Fit),
      myTextHPosition(Prs3d_DTHP_Fit),
      myTextVPosition(Prs3d_DTVP_Center),
      myToDisplayUnits(false),
      myIsText3d(false),
      myIsTextShaded(false),
      myIsArrows3d(false)
{
  myTextAspect->Aspect()->SetTextZoomable(false);
  myTextAspect->SetColor(Quantity_NOC_LAWNGREEN);
  myTextAspect->SetHorizontalJustification(Graphic3d_HTA_CENTER);
  myTextAspect->SetVerticalJustification(Graphic3d_VTA_CENTER);

  myArrowAspect->SetColor(Quantity_NOC_LAWNGREEN);
  myArrowAspect->SetAngle(M_PI * 12.0 / 180.0);
  myArrowAspect->SetLength(6.0);
}

void Prs3d_DimensionAspect::SetCommonColor(const Quantity_Color& theColor)
{
  myLineAspect->SetColor(theColor);
  myTextAspect->SetColor(theColor);
  myArrowAspect->SetColor(theColor);
}

void Prs3d_DimensionAspect::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myLineAspect.get())
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myTextAspect.get())
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myArrowAspect.get())

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myValueStringFormat)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myExtensionSize)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myArrowTailSize)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myArrowOrientation)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myTextHPosition)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myTextVPosition)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myToDisplayUnits)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myIsText3d)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myIsTextShaded)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myIsArrows3d)
}
