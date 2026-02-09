#pragma once

#include <Aspect_InteriorStyle.hpp>

enum Aspect_TypeOfDisplayText
{
  Aspect_TODT_NORMAL,
  Aspect_TODT_SUBTITLE,
  Aspect_TODT_DEKALE,
  Aspect_TODT_BLEND,
  Aspect_TODT_DIMENSION,
  Aspect_TODT_SHADOW
};

#include <Aspect_TypeOfLine.hpp>

enum Aspect_TypeOfStyleText
{
  Aspect_TOST_NORMAL,
  Aspect_TOST_ANNOTATION
};

#include <Font_FontAspect.hpp>
#include <Graphic3d_AlphaMode.hpp>
#include <Graphic3d_MarkerImage.hpp>
#include <Graphic3d_MaterialAspect.hpp>
#include <Graphic3d_HatchStyle.hpp>
#include <Graphic3d_PolygonOffset.hpp>
#include <Graphic3d_ShaderProgram.hpp>
#include <Graphic3d_TextureSet.hpp>
#include <Graphic3d_TypeOfBackfacingModel.hpp>
#include <Graphic3d_TypeOfShadingModel.hpp>
#include <TCollection_HAsciiString.hpp>

class Graphic3d_Aspects : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_Aspects, Standard_Transient)
public:
  Standard_EXPORT Graphic3d_Aspects();

  Aspect_InteriorStyle InteriorStyle() const { return myInteriorStyle; }

  void SetInteriorStyle(const Aspect_InteriorStyle theStyle) { myInteriorStyle = theStyle; }

  Graphic3d_TypeOfShadingModel ShadingModel() const { return myShadingModel; }

  void SetShadingModel(const Graphic3d_TypeOfShadingModel theShadingModel)
  {
    myShadingModel = theShadingModel;
  }

  Graphic3d_AlphaMode AlphaMode() const { return myAlphaMode; }

  float AlphaCutoff() const { return myAlphaCutoff; }

  void SetAlphaMode(Graphic3d_AlphaMode theMode, float theAlphaCutoff = 0.5f)
  {
    myAlphaMode   = theMode;
    myAlphaCutoff = theAlphaCutoff;
  }

  const Quantity_ColorRGBA& ColorRGBA() const { return myInteriorColor; }

  const Quantity_Color& Color() const { return myInteriorColor.GetRGB(); }

  void SetColor(const Quantity_Color& theColor) { myInteriorColor.SetRGB(theColor); }

  const Quantity_Color& InteriorColor() const { return myInteriorColor.GetRGB(); }

  const Quantity_ColorRGBA& InteriorColorRGBA() const { return myInteriorColor; }

  void SetInteriorColor(const Quantity_Color& theColor) { myInteriorColor.SetRGB(theColor); }

  void SetInteriorColor(const Quantity_ColorRGBA& theColor) { myInteriorColor = theColor; }

  const Quantity_Color& BackInteriorColor() const { return myBackInteriorColor.GetRGB(); }

  const Quantity_ColorRGBA& BackInteriorColorRGBA() const { return myBackInteriorColor; }

  void SetBackInteriorColor(const Quantity_Color& theColor)
  {
    myBackInteriorColor.SetRGB(theColor);
  }

  void SetBackInteriorColor(const Quantity_ColorRGBA& theColor) { myBackInteriorColor = theColor; }

  const Graphic3d_MaterialAspect& FrontMaterial() const { return myFrontMaterial; }

  Graphic3d_MaterialAspect& ChangeFrontMaterial() { return myFrontMaterial; }

  void SetFrontMaterial(const Graphic3d_MaterialAspect& theMaterial)
  {
    myFrontMaterial = theMaterial;
  }

  const Graphic3d_MaterialAspect& BackMaterial() const { return myBackMaterial; }

  Graphic3d_MaterialAspect& ChangeBackMaterial() { return myBackMaterial; }

  void SetBackMaterial(const Graphic3d_MaterialAspect& theMaterial)
  {
    myBackMaterial = theMaterial;
  }

  Graphic3d_TypeOfBackfacingModel FaceCulling() const { return myFaceCulling; }

  void SetFaceCulling(Graphic3d_TypeOfBackfacingModel theCulling) { myFaceCulling = theCulling; }

  bool Distinguish() const { return myToDistinguishMaterials; }

  void SetDistinguish(bool toDistinguish) { myToDistinguishMaterials = toDistinguish; }

  void SetDistinguishOn() { myToDistinguishMaterials = true; }

  void SetDistinguishOff() { myToDistinguishMaterials = false; }

  const occ::handle<Graphic3d_ShaderProgram>& ShaderProgram() const { return myProgram; }

  void SetShaderProgram(const occ::handle<Graphic3d_ShaderProgram>& theProgram)
  {
    myProgram = theProgram;
  }

  const occ::handle<Graphic3d_TextureSet>& TextureSet() const { return myTextureSet; }

  void SetTextureSet(const occ::handle<Graphic3d_TextureSet>& theTextures)
  {
    myTextureSet = theTextures;
  }

  occ::handle<Graphic3d_TextureMap> TextureMap() const
  {
    return !myTextureSet.IsNull() && !myTextureSet->IsEmpty() ? myTextureSet->First()
                                                              : occ::handle<Graphic3d_TextureMap>();
  }

  Standard_EXPORT void SetTextureMap(const occ::handle<Graphic3d_TextureMap>& theTexture);

  bool ToMapTexture() const { return myToMapTexture; }

  bool TextureMapState() const { return myToMapTexture; }

  void SetTextureMapOn(bool theToMap) { myToMapTexture = theToMap; }

  void SetTextureMapOn() { myToMapTexture = true; }

  void SetTextureMapOff() { myToMapTexture = false; }

  const Graphic3d_PolygonOffset& PolygonOffset() const { return myPolygonOffset; }

  void SetPolygonOffset(const Graphic3d_PolygonOffset& theOffset) { myPolygonOffset = theOffset; }

  void PolygonOffsets(int& theMode, float& theFactor, float& theUnits) const
  {
    theMode   = myPolygonOffset.Mode;
    theFactor = myPolygonOffset.Factor;
    theUnits  = myPolygonOffset.Units;
  }

  void SetPolygonOffsets(const int   theMode,
                         const float theFactor = 1.0f,
                         const float theUnits  = 0.0f)
  {
    myPolygonOffset.Mode   = (Aspect_PolygonOffsetMode)(theMode & Aspect_POM_Mask);
    myPolygonOffset.Factor = theFactor;
    myPolygonOffset.Units  = theUnits;
  }

public:
  Aspect_TypeOfLine LineType() const { return myLineType; }

  void SetLineType(Aspect_TypeOfLine theType)
  {
    myLineType    = theType;
    myLinePattern = DefaultLinePatternForType(theType);
  }

  uint16_t LinePattern() const { return myLinePattern; }

  void SetLinePattern(uint16_t thePattern)
  {
    myLineType    = DefaultLineTypeForPattern(thePattern);
    myLinePattern = thePattern;
  }

  uint16_t LineStippleFactor() const { return myLineFactor; }

  void SetLineStippleFactor(uint16_t theFactor)
  {
    if (theFactor == 0 || theFactor > 256)
    {
      throw Standard_OutOfRange("Graphic3d_Aspects::SetLineStippleFactor(), bad factor value");
    }
    myLineFactor = theFactor;
  }

  float LineWidth() const { return myLineWidth; }

  void SetLineWidth(float theWidth)
  {
    if (theWidth <= 0.0f)
    {
      throw Standard_OutOfRange("Bad value for EdgeLineWidth");
    }
    myLineWidth = theWidth;
  }

  static uint16_t DefaultLinePatternForType(Aspect_TypeOfLine theType)
  {
    switch (theType)
    {
      case Aspect_TOL_DASH:
        return 0xFFC0;
      case Aspect_TOL_DOT:
        return 0xCCCC;
      case Aspect_TOL_DOTDASH:
        return 0xFF18;
      case Aspect_TOL_EMPTY:
        return 0x0000;
      case Aspect_TOL_SOLID:
        return 0xFFFF;
      case Aspect_TOL_USERDEFINED:
        return 0xFF24;
    }
    return 0xFFFF;
  }

  static Aspect_TypeOfLine DefaultLineTypeForPattern(uint16_t thePattern)
  {
    switch (thePattern)
    {
      case 0x0000:
        return Aspect_TOL_EMPTY;
      case 0xFFC0:
        return Aspect_TOL_DASH;
      case 0xCCCC:
        return Aspect_TOL_DOT;
      case 0xFF18:
        return Aspect_TOL_DOTDASH;
      case 0xFFFF:
        return Aspect_TOL_SOLID;
      case 0xFF24:
        return Aspect_TOL_USERDEFINED;
    }
    return Aspect_TOL_USERDEFINED;
  }

public:
  Aspect_TypeOfMarker MarkerType() const { return myMarkerType; }

  void SetMarkerType(Aspect_TypeOfMarker theType) { myMarkerType = theType; }

  float MarkerScale() const { return myMarkerScale; }

  void SetMarkerScale(const float theScale)
  {
    if (theScale <= 0.0f)
    {
      throw Standard_OutOfRange("Bad value for MarkerScale");
    }
    myMarkerScale = theScale;
  }

  const occ::handle<Graphic3d_MarkerImage>& MarkerImage() const { return myMarkerImage; }

  void SetMarkerImage(const occ::handle<Graphic3d_MarkerImage>& theImage)
  {
    myMarkerImage = theImage;
  }

  bool IsMarkerSprite() const
  {
    if (myMarkerType == Aspect_TOM_POINT || myMarkerType == Aspect_TOM_EMPTY)
    {
      return false;
    }

    return myMarkerType != Aspect_TOM_USERDEFINED || !myMarkerImage.IsNull();
  }

public:
  const occ::handle<TCollection_HAsciiString>& TextFont() const { return myTextFont; }

  void SetTextFont(const occ::handle<TCollection_HAsciiString>& theFont) { myTextFont = theFont; }

  Font_FontAspect TextFontAspect() const { return myTextFontAspect; }

  void SetTextFontAspect(Font_FontAspect theFontAspect) { myTextFontAspect = theFontAspect; }

  Aspect_TypeOfDisplayText TextDisplayType() const { return myTextDisplayType; }

  void SetTextDisplayType(Aspect_TypeOfDisplayText theType) { myTextDisplayType = theType; }

  const Quantity_ColorRGBA& ColorSubTitleRGBA() const { return myEdgeColor; }

  const Quantity_Color& ColorSubTitle() const { return myEdgeColor.GetRGB(); }

  void SetColorSubTitle(const Quantity_Color& theColor) { myEdgeColor.SetRGB(theColor); }

  void SetColorSubTitle(const Quantity_ColorRGBA& theColor) { myEdgeColor = theColor; }

  bool IsTextZoomable() const { return myIsTextZoomable; }

  void SetTextZoomable(bool theFlag) { myIsTextZoomable = theFlag; }

  Aspect_TypeOfStyleText TextStyle() const { return myTextStyle; }

  void SetTextStyle(Aspect_TypeOfStyleText theStyle) { myTextStyle = theStyle; }

  float TextAngle() const { return myTextAngle; }

  void SetTextAngle(float theAngle) { myTextAngle = (float)theAngle; }

public:
  bool ToDrawEdges() const { return myToDrawEdges && myLineType != Aspect_TOL_EMPTY; }

  void SetDrawEdges(bool theToDraw)
  {
    myToDrawEdges = theToDraw;
    if (myLineType == Aspect_TOL_EMPTY)
    {
      myLineType = Aspect_TOL_SOLID;
    }
  }

  void SetEdgeOn() { SetDrawEdges(true); }

  void SetEdgeOff() { SetDrawEdges(false); }

  const Quantity_Color& EdgeColor() const { return myEdgeColor.GetRGB(); }

  const Quantity_ColorRGBA& EdgeColorRGBA() const { return myEdgeColor; }

  void SetEdgeColor(const Quantity_Color& theColor) { myEdgeColor.SetRGB(theColor); }

  void SetEdgeColor(const Quantity_ColorRGBA& theColor) { myEdgeColor = theColor; }

  Aspect_TypeOfLine EdgeLineType() const { return myLineType; }

  void SetEdgeLineType(Aspect_TypeOfLine theType) { SetLineType(theType); }

  float EdgeWidth() const { return myLineWidth; }

  void SetEdgeWidth(double theWidth) { SetLineWidth((float)theWidth); }

  bool ToSkipFirstEdge() const { return myToSkipFirstEdge; }

  void SetSkipFirstEdge(bool theToSkipFirstEdge) { myToSkipFirstEdge = theToSkipFirstEdge; }

  bool ToDrawSilhouette() const { return myToDrawSilhouette; }

  void SetDrawSilhouette(bool theToDraw) { myToDrawSilhouette = theToDraw; }

public:
  const occ::handle<Graphic3d_HatchStyle>& HatchStyle() const { return myHatchStyle; }

  void SetHatchStyle(const occ::handle<Graphic3d_HatchStyle>& theStyle) { myHatchStyle = theStyle; }

  void SetHatchStyle(const Aspect_HatchStyle theStyle)
  {
    if (theStyle == Aspect_HS_SOLID)
    {
      myHatchStyle.Nullify();
      return;
    }

    myHatchStyle = new Graphic3d_HatchStyle(theStyle);
  }

public:
  bool IsEqual(const Graphic3d_Aspects& theOther)
  {
    if (this == &theOther)
    {
      return true;
    }

    return myProgram == theOther.myProgram && myTextureSet == theOther.myTextureSet
           && myMarkerImage == theOther.myMarkerImage && myInteriorColor == theOther.myInteriorColor
           && myBackInteriorColor == theOther.myBackInteriorColor
           && myFrontMaterial == theOther.myFrontMaterial
           && myBackMaterial == theOther.myBackMaterial
           && myInteriorStyle == theOther.myInteriorStyle
           && myShadingModel == theOther.myShadingModel && myFaceCulling == theOther.myFaceCulling
           && myAlphaMode == theOther.myAlphaMode && myAlphaCutoff == theOther.myAlphaCutoff
           && myLineType == theOther.myLineType && myEdgeColor == theOther.myEdgeColor
           && myLineWidth == theOther.myLineWidth && myLineFactor == theOther.myLineFactor
           && myLinePattern == theOther.myLinePattern && myMarkerType == theOther.myMarkerType
           && myMarkerScale == theOther.myMarkerScale && myHatchStyle == theOther.myHatchStyle
           && myTextFont == theOther.myTextFont && myPolygonOffset == theOther.myPolygonOffset
           && myTextStyle == theOther.myTextStyle && myTextDisplayType == theOther.myTextDisplayType
           && myTextFontAspect == theOther.myTextFontAspect && myTextAngle == theOther.myTextAngle
           && myToSkipFirstEdge == theOther.myToSkipFirstEdge
           && myToDistinguishMaterials == theOther.myToDistinguishMaterials
           && myToDrawEdges == theOther.myToDrawEdges
           && myToDrawSilhouette == theOther.myToDrawSilhouette
           && myToMapTexture == theOther.myToMapTexture
           && myIsTextZoomable == theOther.myIsTextZoomable;
  }

  Standard_EXPORT virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

public:
  Standard_DEPRECATED("Deprecated method, FaceCulling() should be used instead")

  bool ToSuppressBackFaces() const
  {
    return myFaceCulling == Graphic3d_TypeOfBackfacingModel_BackCulled
           || myFaceCulling == Graphic3d_TypeOfBackfacingModel_Auto;
  }

  Standard_DEPRECATED("Deprecated method, SetFaceCulling() should be used "
                      "instead")

  void SetSuppressBackFaces(bool theToSuppress)
  {
    myFaceCulling = theToSuppress ? Graphic3d_TypeOfBackfacingModel_Auto
                                  : Graphic3d_TypeOfBackfacingModel_DoubleSided;
  }

  Standard_DEPRECATED("Deprecated method, FaceCulling() should be used instead")

  bool BackFace() const
  {
    return myFaceCulling == Graphic3d_TypeOfBackfacingModel_BackCulled
           || myFaceCulling == Graphic3d_TypeOfBackfacingModel_Auto;
  }

  Standard_DEPRECATED("Deprecated method, SetFaceCulling() should be used instead")

  void AllowBackFace() { myFaceCulling = Graphic3d_TypeOfBackfacingModel_DoubleSided; }

  Standard_DEPRECATED("Deprecated method, SetFaceCulling() should be used instead")

  void SuppressBackFace() { myFaceCulling = Graphic3d_TypeOfBackfacingModel_Auto; }

protected:
  occ::handle<Graphic3d_ShaderProgram>  myProgram;
  occ::handle<Graphic3d_TextureSet>     myTextureSet;
  occ::handle<Graphic3d_MarkerImage>    myMarkerImage;
  occ::handle<Graphic3d_HatchStyle>     myHatchStyle;
  occ::handle<TCollection_HAsciiString> myTextFont;
  Graphic3d_MaterialAspect              myFrontMaterial;
  Graphic3d_MaterialAspect              myBackMaterial;

  Quantity_ColorRGBA myInteriorColor;
  Quantity_ColorRGBA myBackInteriorColor;
  Quantity_ColorRGBA myEdgeColor;

  Graphic3d_PolygonOffset         myPolygonOffset;
  Aspect_InteriorStyle            myInteriorStyle;
  Graphic3d_TypeOfShadingModel    myShadingModel;
  Graphic3d_TypeOfBackfacingModel myFaceCulling;
  Graphic3d_AlphaMode             myAlphaMode;
  float                           myAlphaCutoff;

  Aspect_TypeOfLine myLineType;
  float             myLineWidth;
  uint16_t          myLineFactor;
  uint16_t          myLinePattern;

  Aspect_TypeOfMarker myMarkerType;
  float               myMarkerScale;

  Aspect_TypeOfStyleText   myTextStyle;
  Aspect_TypeOfDisplayText myTextDisplayType;
  Font_FontAspect          myTextFontAspect;
  float                    myTextAngle;

  bool myToSkipFirstEdge;
  bool myToDistinguishMaterials;
  bool myToDrawEdges;
  bool myToDrawSilhouette;
  bool myToMapTexture;
  bool myIsTextZoomable;
};
