#pragma once

#include <Image_PixMap.hpp>
#include <OSD_Path.hpp>
#include <Graphic3d_TypeOfTexture.hpp>
#include <Standard.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

class Image_CompressedPixMap;
class Image_SupportedFormats;
class Graphic3d_TextureParams;

class Graphic3d_TextureRoot : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_TextureRoot, Standard_Transient)
public:
  Standard_EXPORT static TCollection_AsciiString TexturesFolder();

public:
  Standard_EXPORT ~Graphic3d_TextureRoot() override;

  Standard_EXPORT virtual bool IsDone() const;

  const OSD_Path& Path() const { return myPath; }

  Graphic3d_TypeOfTexture Type() const { return myType; }

  const TCollection_AsciiString& GetId() const { return myTexId; }

  size_t Revision() const { return myRevision; }

  void UpdateRevision() { ++myRevision; }

  Standard_EXPORT virtual occ::handle<Image_CompressedPixMap> GetCompressedImage(
    const occ::handle<Image_SupportedFormats>& theSupported);

  Standard_EXPORT virtual occ::handle<Image_PixMap> GetImage(
    const occ::handle<Image_SupportedFormats>& theSupported);

  const occ::handle<Graphic3d_TextureParams>& GetParams() const { return myParams; }

  bool IsColorMap() const { return myIsColorMap; }

  void SetColorMap(bool theIsColor) { myIsColorMap = theIsColor; }

  bool HasMipmaps() const { return myHasMipmaps; }

  void SetMipmapsGeneration(bool theToGenerateMipmaps) { myHasMipmaps = theToGenerateMipmaps; }

  bool IsTopDown() const { return myIsTopDown; }

protected:
  Standard_EXPORT Graphic3d_TextureRoot(const TCollection_AsciiString& theFileName,
                                        const Graphic3d_TypeOfTexture  theType);

  Standard_EXPORT Graphic3d_TextureRoot(const occ::handle<Image_PixMap>& thePixmap,
                                        const Graphic3d_TypeOfTexture    theType);

  Standard_EXPORT void generateId();

  Standard_EXPORT static void convertToCompatible(
    const occ::handle<Image_SupportedFormats>& theSupported,
    const occ::handle<Image_PixMap>&           theImage);

  virtual occ::handle<Image_PixMap> GetImage() const { return occ::handle<Image_PixMap>(); }

protected:
  occ::handle<Graphic3d_TextureParams> myParams;

  TCollection_AsciiString   myTexId;
  occ::handle<Image_PixMap> myPixMap;
  OSD_Path                  myPath;
  size_t                    myRevision;
  Graphic3d_TypeOfTexture   myType;
  bool                      myIsColorMap;
  bool                      myIsTopDown;
  bool                      myHasMipmaps;
};
