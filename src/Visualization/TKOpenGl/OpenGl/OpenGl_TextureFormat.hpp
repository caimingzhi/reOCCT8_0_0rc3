#pragma once

#include <Image_CompressedFormat.hpp>
#include <Image_Format.hpp>
#include <OpenGl_GlCore13.hpp>
#include <TCollection_AsciiString.hpp>

class OpenGl_Context;

class OpenGl_TextureFormat
{
public:
  template <class theCompType, int theNbComps>
  static OpenGl_TextureFormat Create();

  Standard_EXPORT static OpenGl_TextureFormat FindFormat(const occ::handle<OpenGl_Context>& theCtx,
                                                         Image_Format theFormat,
                                                         bool         theIsColorMap);

  Standard_EXPORT static OpenGl_TextureFormat FindSizedFormat(
    const occ::handle<OpenGl_Context>& theCtx,
    GLint                              theSizedFormat);

  Standard_EXPORT static OpenGl_TextureFormat FindCompressedFormat(
    const occ::handle<OpenGl_Context>& theCtx,
    Image_CompressedFormat             theFormat,
    bool                               theIsColorMap);

  Standard_EXPORT static TCollection_AsciiString FormatFormat(GLint theInternalFormat);

  Standard_EXPORT static TCollection_AsciiString FormatDataType(GLint theDataType);

public:
  OpenGl_TextureFormat()
      : myImageFormat(Image_Format_UNKNOWN),
        myInternalFormat(0),
        myPixelFormat(0),
        myDataType(0),
        myNbComponents(0)
  {
  }

  bool IsValid() const { return myInternalFormat != 0 && myPixelFormat != 0 && myDataType != 0; }

  GLint InternalFormat() const { return myInternalFormat; }

  void SetInternalFormat(GLint theInternal) { myInternalFormat = theInternal; }

  GLenum PixelFormat() const { return myPixelFormat; }

  void SetPixelFormat(GLenum theFormat) { myPixelFormat = theFormat; }

  GLint DataType() const { return myDataType; }

  void SetDataType(GLint theType) { myDataType = theType; }

  GLint NbComponents() const { return myNbComponents; }

  void SetNbComponents(GLint theNbComponents) { myNbComponents = theNbComponents; }

  bool IsSRGB() const
  {
    return myInternalFormat == GL_SRGB8 || myInternalFormat == GL_SRGB8_ALPHA8;
  }

  Image_Format ImageFormat() const { return myImageFormat; }

  void SetImageFormat(Image_Format theFormat) { myImageFormat = theFormat; }

public:
  GLint Internal() const { return myInternalFormat; }

  GLenum Format() const { return myPixelFormat; }

private:
  Image_Format myImageFormat;
  GLint        myInternalFormat;
  GLenum       myPixelFormat;
  GLint        myDataType;
  GLint        myNbComponents;
};

template <class T>
struct OpenGl_TextureFormatSelector
{
};

template <>
struct OpenGl_TextureFormatSelector<GLubyte>
{
  static GLint DataType() { return GL_UNSIGNED_BYTE; }

  static GLint Internal(GLuint theChannels)
  {
    switch (theChannels)
    {
      case 1:
        return GL_R8;
      case 2:
        return GL_RG8;
      case 3:
        return GL_RGB8;
      case 4:
        return GL_RGBA8;
      default:
        return GL_NONE;
    }
  }
};

template <>
struct OpenGl_TextureFormatSelector<GLushort>
{
  static GLint DataType() { return GL_UNSIGNED_SHORT; }

  static GLint Internal(GLuint theChannels)
  {
    switch (theChannels)
    {
      case 1:
        return GL_R16;
      case 2:
        return GL_RG16;
      case 3:
        return GL_RGB16;
      case 4:
        return GL_RGBA16;
      default:
        return GL_NONE;
    }
  }
};

template <>
struct OpenGl_TextureFormatSelector<GLfloat>
{
  static GLint DataType() { return GL_FLOAT; }

  static GLint Internal(GLuint theChannels)
  {
    switch (theChannels)
    {
      case 1:
        return GL_R32F;
      case 2:
        return GL_RG32F;
      case 3:
        return GL_RGB32F;
      case 4:
        return GL_RGBA32F;
      default:
        return GL_NONE;
    }
  }
};

template <>
struct OpenGl_TextureFormatSelector<GLuint>
{
  static GLint DataType() { return GL_UNSIGNED_INT; }

  static GLint Internal(GLuint theChannels)
  {
    switch (theChannels)
    {
      case 1:
        return GL_RED;
      case 2:
        return GL_RG;
      case 3:
        return GL_RGB;
      case 4:
        return GL_RGBA;
      default:
        return GL_NONE;
    }
  }
};

template <>
struct OpenGl_TextureFormatSelector<GLbyte>
{
  static GLint DataType() { return GL_BYTE; }

  static GLint Internal(GLuint theChannels)
  {
    switch (theChannels)
    {
      case 1:
        return GL_R8_SNORM;
      case 2:
        return GL_RG8_SNORM;
      case 3:
        return GL_RGB8_SNORM;
      case 4:
        return GL_RGBA8_SNORM;
      default:
        return GL_NONE;
    }
  }
};

template <>
struct OpenGl_TextureFormatSelector<GLshort>
{
  static GLint DataType() { return GL_SHORT; }

  static GLint Internal(GLuint theChannels)
  {
    switch (theChannels)
    {
      case 1:
        return GL_R16_SNORM;
      case 2:
        return GL_RG16_SNORM;
      case 3:
        return GL_RGB16_SNORM;
      case 4:
        return GL_RGBA16_SNORM;
      default:
        return GL_NONE;
    }
  }
};

template <>
struct OpenGl_TextureFormatSelector<GLint>
{
  static GLint DataType() { return GL_INT; }

  static GLint Internal(GLuint theChannels)
  {
    switch (theChannels)
    {
      case 1:
        return GL_RED_SNORM;
      case 2:
        return GL_RG_SNORM;
      case 3:
        return GL_RGB_SNORM;
      case 4:
        return GL_RGBA_SNORM;
      default:
        return GL_NONE;
    }
  }
};

template <class theCompType, int theNbComps>
inline OpenGl_TextureFormat OpenGl_TextureFormat::Create()
{
  OpenGl_TextureFormat aFormat;
  aFormat.SetNbComponents(theNbComps);
  aFormat.SetInternalFormat(OpenGl_TextureFormatSelector<theCompType>::Internal(theNbComps));
  aFormat.SetDataType(OpenGl_TextureFormatSelector<theCompType>::DataType());
  GLenum aPixelFormat = GL_NONE;
  switch (theNbComps)
  {
    case 1:
      aPixelFormat = GL_RED;
      break;
    case 2:
      aPixelFormat = GL_RG;
      break;
    case 3:
      aPixelFormat = GL_RGB;
      break;
    case 4:
      aPixelFormat = GL_RGBA;
      break;
  }
  aFormat.SetPixelFormat(aPixelFormat);
  return aFormat;
}
