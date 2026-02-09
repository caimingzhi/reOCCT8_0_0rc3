#pragma once

#include <AIS_Shape.hpp>
#include <gp_Pnt2d.hpp>
#include <Graphic3d_NameOfTexture2D.hpp>
#include <Image_PixMap.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>
#include <Graphic3d_AspectFillArea3d.hpp>
#include <Prs3d_Presentation.hpp>
#include <PrsMgr_PresentationManager.hpp>

class Graphic3d_AspectFillArea3d;
class Graphic3d_Texture2D;

class AIS_TexturedShape : public AIS_Shape
{

public:
  Standard_EXPORT AIS_TexturedShape(const TopoDS_Shape& theShape);

  Standard_EXPORT virtual void SetTextureFileName(
    const TCollection_AsciiString& theTextureFileName);

  Standard_EXPORT virtual void SetTexturePixMap(const occ::handle<Image_PixMap>& theTexturePixMap);

  bool TextureMapState() const { return myToMapTexture; }

  Standard_EXPORT void SetTextureMapOn();

  Standard_EXPORT void SetTextureMapOff();

  const char* TextureFile() const { return myTextureFile.ToCString(); }

  const occ::handle<Image_PixMap>& TexturePixMap() const { return myTexturePixMap; }

public:
  Standard_EXPORT void UpdateAttributes();

  Standard_EXPORT void SetColor(const Quantity_Color& theColor) override;

  Standard_EXPORT void UnsetColor() override;

  Standard_EXPORT void SetMaterial(const Graphic3d_MaterialAspect& theAspect) override;

  Standard_EXPORT void UnsetMaterial() override;

  Standard_EXPORT void EnableTextureModulate();

  Standard_EXPORT void DisableTextureModulate();

  bool TextureRepeat() const { return myToRepeat; }

  double URepeat() const { return myUVRepeat.X(); }

  double VRepeat() const { return myUVRepeat.Y(); }

  Standard_EXPORT void SetTextureRepeat(const bool   theToRepeat,
                                        const double theURepeat = 1.0,
                                        const double theVRepeat = 1.0);

  bool TextureOrigin() const { return myIsCustomOrigin; }

  double TextureUOrigin() const { return myUVOrigin.X(); }

  double TextureVOrigin() const { return myUVOrigin.Y(); }

  Standard_EXPORT void SetTextureOrigin(const bool   theToSetTextureOrigin,
                                        const double theUOrigin = 0.0,
                                        const double theVOrigin = 0.0);

  bool TextureScale() const { return myToScale; }

  double TextureScaleU() const { return myUVScale.X(); }

  double TextureScaleV() const { return myUVScale.Y(); }

  Standard_EXPORT void SetTextureScale(const bool   theToSetTextureScale,
                                       const double theScaleU = 1.0,
                                       const double theScaleV = 1.0);

  bool ShowTriangles() const { return myToShowTriangles; }

  Standard_EXPORT void ShowTriangles(const bool theToShowTriangles);

  bool TextureModulate() const { return myModulate; }

  bool AcceptDisplayMode(const int theMode) const override { return theMode >= 0 && theMode <= 3; }

protected:
  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

  Standard_EXPORT void updateAttributes(const occ::handle<Prs3d_Presentation>& thePrs);

protected:
  occ::handle<Graphic3d_Texture2D>        myTexture;
  occ::handle<Graphic3d_AspectFillArea3d> myAspect;

protected:
  occ::handle<Image_PixMap> myTexturePixMap;
  TCollection_AsciiString   myTextureFile;
  Graphic3d_NameOfTexture2D myPredefTexture;

protected:
  bool myToMapTexture;
  bool myModulate;
  bool myIsCustomOrigin;
  bool myToRepeat;
  bool myToScale;
  bool myToShowTriangles;

public:
  DEFINE_STANDARD_RTTIEXT(AIS_TexturedShape, AIS_Shape)
};
