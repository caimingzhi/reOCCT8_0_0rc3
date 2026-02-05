#include <Prs3d_TextAspect.hpp>

#include <Font_NameOfFont.hpp>
#include <Standard_Dump.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Prs3d_TextAspect, Prs3d_BasicAspect)

//=================================================================================================

Prs3d_TextAspect::Prs3d_TextAspect()
    : myTextAspect(
        new Graphic3d_AspectText3d(Quantity_Color(Quantity_NOC_YELLOW), Font_NOF_SERIF, 1.0, 0.0)),
      myHeight(16.0),
      myHorizontalJustification(Graphic3d_HTA_LEFT),
      myVerticalJustification(Graphic3d_VTA_BOTTOM),
      myOrientation(Graphic3d_TP_RIGHT)
{
}

//=================================================================================================

Prs3d_TextAspect::Prs3d_TextAspect(const occ::handle<Graphic3d_AspectText3d>& theAspect)
    : myTextAspect(theAspect),
      myHeight(16.0),
      myHorizontalJustification(Graphic3d_HTA_LEFT),
      myVerticalJustification(Graphic3d_VTA_BOTTOM),
      myOrientation(Graphic3d_TP_RIGHT)
{
}

//=================================================================================================

void Prs3d_TextAspect::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myTextAspect.get())

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myHeight)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myHorizontalJustification)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myVerticalJustification)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myOrientation)
}
