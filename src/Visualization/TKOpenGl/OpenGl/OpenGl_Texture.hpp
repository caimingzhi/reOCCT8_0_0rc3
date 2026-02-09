#pragma once

#include <Graphic3d_CubeMap.hpp>
#include <NCollection_Vec3.hpp>
#include <Standard_TypeDef.hpp>
#include <OpenGl_TextureFormat.hpp>
#include <OpenGl_NamedResource.hpp>
#include <OpenGl_Sampler.hpp>
#include <Graphic3d_TextureUnit.hpp>
#include <Graphic3d_TypeOfTexture.hpp>
#include <TCollection_AsciiString.hpp>

class OpenGl_Texture : public OpenGl_NamedResource
{
  DEFINE_STANDARD_RTTIEXT(OpenGl_Texture, OpenGl_NamedResource)
public:
  static const unsigned int NO_TEXTURE = 0;

  Standard_EXPORT static size_t PixelSizeOfPixelFormat(int theInternalFormat);

public:
  Standard_EXPORT OpenGl_Texture(
    const TCollection_AsciiString& theResourceId          = TCollection_AsciiString::EmptyString(),
    const occ::handle<Graphic3d_TextureParams>& theParams = occ::handle<Graphic3d_TextureParams>());

  Standard_EXPORT ~OpenGl_Texture() override;

  virtual bool IsValid() const { return myTextureId != NO_TEXTURE; }

  unsigned int GetTarget() const { return myTarget; }

  const NCollection_Vec3<int>& Size() const { return mySize; }

  int SizeX() const { return mySize.x(); }

  int SizeY() const { return mySize.y(); }

  int SizeZ() const { return mySize.z(); }

  unsigned int TextureId() const { return myTextureId; }

  unsigned int GetFormat() const { return myTextFormat; }

  int SizedFormat() const { return mySizedFormat; }

  bool IsAlpha() const { return myIsAlpha; }

  void SetAlpha(const bool theValue) { myIsAlpha = theValue; }

  bool IsTopDown() const { return myIsTopDown; }

  void SetTopDown(bool theIsTopDown) { myIsTopDown = theIsTopDown; }

  Standard_EXPORT bool Create(const occ::handle<OpenGl_Context>& theCtx);

  Standard_EXPORT void Release(OpenGl_Context* theCtx) override;

  const occ::handle<OpenGl_Sampler>& Sampler() const { return mySampler; }

  void SetSampler(const occ::handle<OpenGl_Sampler>& theSampler) { mySampler = theSampler; }

  Standard_EXPORT bool InitSamplerObject(const occ::handle<OpenGl_Context>& theCtx);

  void Bind(const occ::handle<OpenGl_Context>& theCtx) const
  {
    Bind(theCtx, mySampler->Parameters()->TextureUnit());
  }

  void Unbind(const occ::handle<OpenGl_Context>& theCtx) const
  {
    Unbind(theCtx, mySampler->Parameters()->TextureUnit());
  }

  Standard_EXPORT void Bind(const occ::handle<OpenGl_Context>& theCtx,
                            const Graphic3d_TextureUnit        theTextureUnit) const;

  Standard_EXPORT void Unbind(const occ::handle<OpenGl_Context>& theCtx,
                              const Graphic3d_TextureUnit        theTextureUnit) const;

  size_t Revision() const { return myRevision; }

  void SetRevision(const size_t theRevision) { myRevision = theRevision; }

  Standard_EXPORT bool Init(const occ::handle<OpenGl_Context>& theCtx,
                            const Image_PixMap&                theImage,
                            const Graphic3d_TypeOfTexture      theType,
                            const bool                         theIsColorMap);

  Standard_EXPORT bool Init(const occ::handle<OpenGl_Context>& theCtx,
                            const OpenGl_TextureFormat&        theFormat,
                            const NCollection_Vec3<int>&       theSizeXYZ,
                            const Graphic3d_TypeOfTexture      theType,
                            const Image_PixMap*                theImage = nullptr);

  bool Init(const occ::handle<OpenGl_Context>& theCtx,
            const OpenGl_TextureFormat&        theFormat,
            const NCollection_Vec2<int>&       theSizeXY,
            const Graphic3d_TypeOfTexture      theType,
            const Image_PixMap*                theImage = nullptr)
  {
    return Init(theCtx, theFormat, NCollection_Vec3<int>(theSizeXY, 1), theType, theImage);
  }

  Standard_EXPORT bool Init(const occ::handle<OpenGl_Context>&        theCtx,
                            const occ::handle<Graphic3d_TextureRoot>& theTextureMap);

  Standard_EXPORT bool GenerateMipmaps(const occ::handle<OpenGl_Context>& theCtx);

  Standard_EXPORT bool InitCompressed(const occ::handle<OpenGl_Context>& theCtx,
                                      const Image_CompressedPixMap&      theImage,
                                      const bool                         theIsColorMap);

  Standard_EXPORT bool Init2DMultisample(const occ::handle<OpenGl_Context>& theCtx,
                                         const int                          theNbSamples,
                                         const int                          theTextFormat,
                                         const int                          theSizeX,
                                         const int                          theSizeY);

  Standard_EXPORT bool InitRectangle(const occ::handle<OpenGl_Context>& theCtx,
                                     const int                          theSizeX,
                                     const int                          theSizeY,
                                     const OpenGl_TextureFormat&        theFormat);

  Standard_EXPORT bool Init3D(const occ::handle<OpenGl_Context>& theCtx,
                              const OpenGl_TextureFormat&        theFormat,
                              const NCollection_Vec3<int>&       theSizeXYZ,
                              const void*                        thePixels);

  bool HasMipmaps() const { return myMaxMipLevel > 0; }

  int MaxMipmapLevel() const { return myMaxMipLevel; }

  int NbSamples() const { return myNbSamples; }

  Standard_EXPORT size_t EstimatedDataSize() const override;

  virtual bool IsPointSprite() const { return false; }

  Standard_EXPORT bool ImageDump(Image_PixMap&                      theImage,
                                 const occ::handle<OpenGl_Context>& theCtx,
                                 Graphic3d_TextureUnit              theTexUnit,
                                 int                                theLevel    = 0,
                                 int                                theCubeSide = 0) const;

public:
  Standard_DEPRECATED("Deprecated method, OpenGl_TextureFormat::FindFormat() should be used "
                      "instead")

  static bool GetDataFormat(const occ::handle<OpenGl_Context>& theCtx,
                            const Image_Format                 theFormat,
                            int&                               theTextFormat,
                            unsigned int&                      thePixelFormat,
                            unsigned int&                      theDataType)
  {
    OpenGl_TextureFormat aFormat = OpenGl_TextureFormat::FindFormat(theCtx, theFormat, false);
    theTextFormat                = aFormat.InternalFormat();
    thePixelFormat               = aFormat.PixelFormat();
    theDataType                  = aFormat.DataType();
    return aFormat.IsValid();
  }

  Standard_DEPRECATED("Deprecated method, OpenGl_TextureFormat::FindFormat() should be used "
                      "instead")

  static bool GetDataFormat(const occ::handle<OpenGl_Context>& theCtx,
                            const Image_PixMap&                theData,
                            int&                               theTextFormat,
                            unsigned int&                      thePixelFormat,
                            unsigned int&                      theDataType)
  {
    OpenGl_TextureFormat aFormat =
      OpenGl_TextureFormat::FindFormat(theCtx, theData.Format(), false);
    theTextFormat  = aFormat.InternalFormat();
    thePixelFormat = aFormat.PixelFormat();
    theDataType    = aFormat.DataType();
    return aFormat.IsValid();
  }

  Standard_DEPRECATED("Deprecated method, OpenGl_TextureFormat should be passed instead of "
                      "separate parameters")

  bool Init(const occ::handle<OpenGl_Context>& theCtx,
            const int                          theTextFormat,
            const unsigned int                 thePixelFormat,
            const unsigned int                 theDataType,
            const int                          theSizeX,
            const int                          theSizeY,
            const Graphic3d_TypeOfTexture      theType,
            const Image_PixMap*                theImage = nullptr)
  {
    OpenGl_TextureFormat aFormat;
    aFormat.SetInternalFormat(theTextFormat);
    aFormat.SetPixelFormat(thePixelFormat);
    aFormat.SetDataType(theDataType);
    return Init(theCtx, aFormat, NCollection_Vec2<int>(theSizeX, theSizeY), theType, theImage);
  }

  Standard_DEPRECATED("Deprecated method, theIsColorMap parameter should be explicitly "
                      "specified")

  bool Init(const occ::handle<OpenGl_Context>& theCtx,
            const Image_PixMap&                theImage,
            const Graphic3d_TypeOfTexture      theType)
  {
    return Init(theCtx, theImage, theType, true);
  }

  Standard_DEPRECATED("Deprecated method, OpenGl_TextureFormat should be passed instead of "
                      "separate parameters")

  bool Init3D(const occ::handle<OpenGl_Context>& theCtx,
              const int                          theTextFormat,
              const unsigned int                 thePixelFormat,
              const unsigned int                 theDataType,
              const int                          theSizeX,
              const int                          theSizeY,
              const int                          theSizeZ,
              const void*                        thePixels)
  {
    OpenGl_TextureFormat aFormat;
    aFormat.SetInternalFormat(theTextFormat);
    aFormat.SetPixelFormat(thePixelFormat);
    aFormat.SetDataType(theDataType);
    return Init3D(theCtx, aFormat, NCollection_Vec3<int>(theSizeX, theSizeY, theSizeZ), thePixels);
  }

  Standard_EXPORT bool InitCubeMap(const occ::handle<OpenGl_Context>&    theCtx,
                                   const occ::handle<Graphic3d_CubeMap>& theCubeMap,
                                   size_t                                theSize,
                                   Image_Format                          theFormat,
                                   bool                                  theToGenMipmap,
                                   bool                                  theIsColorMap);

protected:
  Standard_EXPORT void applyDefaultSamplerParams(const occ::handle<OpenGl_Context>& theCtx);

protected:
  occ::handle<OpenGl_Sampler> mySampler;
  size_t                      myRevision;
  unsigned int                myTextureId;
  unsigned int                myTarget;
  NCollection_Vec3<int>       mySize;
  unsigned int                myTextFormat;
  int                         mySizedFormat;
  int                         myNbSamples;
  int                         myMaxMipLevel;
  bool                        myIsAlpha;

  bool myIsTopDown;
};
