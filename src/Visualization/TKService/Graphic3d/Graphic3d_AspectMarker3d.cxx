#include <Graphic3d_AspectMarker3d.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Graphic3d_AspectMarker3d, Graphic3d_Aspects)

Graphic3d_AspectMarker3d::Graphic3d_AspectMarker3d()
{
  myShadingModel = Graphic3d_TypeOfShadingModel_Unlit;
  myInteriorColor.SetRGB(Quantity_NOC_YELLOW);
  myMarkerType  = Aspect_TOM_X;
  myMarkerScale = 1.0f;
}

Graphic3d_AspectMarker3d::Graphic3d_AspectMarker3d(const Aspect_TypeOfMarker theType,
                                                   const Quantity_Color&     theColor,
                                                   const double              theScale)
{
  myShadingModel = Graphic3d_TypeOfShadingModel_Unlit;
  myInteriorColor.SetRGB(theColor);
  myMarkerType = theType;
  SetMarkerScale((float)theScale);
}

Graphic3d_AspectMarker3d::Graphic3d_AspectMarker3d(
  const Quantity_Color&                            theColor,
  const int                                        theWidth,
  const int                                        theHeight,
  const occ::handle<NCollection_HArray1<uint8_t>>& theTextureBitMap)
{
  myShadingModel = Graphic3d_TypeOfShadingModel_Unlit;
  myMarkerImage  = new Graphic3d_MarkerImage(theTextureBitMap, theWidth, theHeight);
  myInteriorColor.SetRGB(theColor), myMarkerType = Aspect_TOM_USERDEFINED;
  myMarkerScale = 1.0f;
}

Graphic3d_AspectMarker3d::Graphic3d_AspectMarker3d(const occ::handle<Image_PixMap>& theTextureImage)
{
  myShadingModel = Graphic3d_TypeOfShadingModel_Unlit;
  myMarkerImage  = new Graphic3d_MarkerImage(theTextureImage);
  myInteriorColor.SetRGB(Quantity_NOC_YELLOW);
  myMarkerType  = Aspect_TOM_USERDEFINED;
  myMarkerScale = 1.0f;
}

void Graphic3d_AspectMarker3d::GetTextureSize(int& theWidth, int& theHeight) const
{
  if (!myMarkerImage.IsNull())
  {
    myMarkerImage->GetTextureSize(theWidth, theHeight);
  }
  else
  {
    theWidth  = 0;
    theHeight = 0;
  }
}

void Graphic3d_AspectMarker3d::SetBitMap(
  const int                                        theWidth,
  const int                                        theHeight,
  const occ::handle<NCollection_HArray1<uint8_t>>& theTextureBitMap)
{
  myMarkerImage.Nullify();
  myMarkerImage = new Graphic3d_MarkerImage(theTextureBitMap, theWidth, theHeight);
}
