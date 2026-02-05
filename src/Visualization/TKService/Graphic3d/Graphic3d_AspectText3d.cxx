#include <Graphic3d_AspectText3d.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Graphic3d_AspectText3d, Graphic3d_Aspects)

//=================================================================================================

Graphic3d_AspectText3d::Graphic3d_AspectText3d()
{
  SetAlphaMode(Graphic3d_AlphaMode_MaskBlend, 0.285f);
  myShadingModel = Graphic3d_TypeOfShadingModel_Unlit;
  myInteriorColor.SetRGB(Quantity_NOC_YELLOW);
  myEdgeColor.SetRGB(Quantity_NOC_WHITE);
}

//=================================================================================================

Graphic3d_AspectText3d::Graphic3d_AspectText3d(const Quantity_Color& theColor,
                                               const char*           theFont,
                                               double,
                                               double,
                                               Aspect_TypeOfStyleText   theStyle,
                                               Aspect_TypeOfDisplayText theDisplayType)
{
  SetAlphaMode(Graphic3d_AlphaMode_MaskBlend, 0.285f);
  myShadingModel    = Graphic3d_TypeOfShadingModel_Unlit;
  myTextStyle       = theStyle;
  myTextDisplayType = theDisplayType;
  myInteriorColor.SetRGB(theColor);
  myEdgeColor.SetRGB(Quantity_NOC_WHITE);
  if (theFont != nullptr && *theFont != '\0')
  {
    myTextFont = new TCollection_HAsciiString(theFont);
  }
}

//=================================================================================================

void Graphic3d_AspectText3d::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)
  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, Graphic3d_Aspects)
}
