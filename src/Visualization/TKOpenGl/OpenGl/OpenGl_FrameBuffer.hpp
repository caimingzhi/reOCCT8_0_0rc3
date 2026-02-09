#pragma once

#include <OpenGl_NamedResource.hpp>
#include <TCollection_AsciiString.hpp>
#include <Graphic3d_BufferType.hpp>
#include <NCollection_Vec2.hpp>
#include <Standard_TypeDef.hpp>
#include <NCollection_Vector.hpp>
#include <NCollection_Sequence.hpp>

class Image_PixMap;
class OpenGl_Texture;

class OpenGl_FrameBuffer : public OpenGl_NamedResource
{
  DEFINE_STANDARD_RTTIEXT(OpenGl_FrameBuffer, OpenGl_NamedResource)
public:
  static const unsigned int NO_FRAMEBUFFER  = 0;
  static const unsigned int NO_RENDERBUFFER = 0;

public:
  Standard_EXPORT static bool BufferDump(const occ::handle<OpenGl_Context>&     theGlCtx,
                                         const occ::handle<OpenGl_FrameBuffer>& theFbo,
                                         Image_PixMap&                          theImage,
                                         Graphic3d_BufferType                   theBufferType);

public:
  Standard_EXPORT OpenGl_FrameBuffer(
    const TCollection_AsciiString& theResourceId = TCollection_AsciiString::EmptyString());

  Standard_EXPORT ~OpenGl_FrameBuffer() override;

  Standard_EXPORT void Release(OpenGl_Context* theGlCtx) override;

  int NbSamples() const { return myNbSamples; }

  int NbColorBuffers() const { return myColorTextures.Length(); }

  bool HasColor() const { return !myColorFormats.IsEmpty(); }

  bool HasDepth() const { return myDepthFormat != 0; }

  NCollection_Vec2<int> GetSize() const { return NCollection_Vec2<int>(GetSizeX(), GetSizeY()); }

  Standard_EXPORT int GetSizeX() const;

  Standard_EXPORT int GetSizeY() const;

  NCollection_Vec2<int> GetVPSize() const { return NCollection_Vec2<int>(myVPSizeX, myVPSizeY); }

  int GetVPSizeX() const { return myVPSizeX; }

  int GetVPSizeY() const { return myVPSizeY; }

  NCollection_Vec2<int> GetInitVPSize() const
  {
    return NCollection_Vec2<int>(myInitVPSizeX, myInitVPSizeY);
  }

  int GetInitVPSizeX() const { return myInitVPSizeX; }

  int GetInitVPSizeY() const { return myInitVPSizeY; }

  bool IsValid() const { return isValidFrameBuffer(); }

  Standard_EXPORT bool Init(const occ::handle<OpenGl_Context>& theGlCtx,
                            const NCollection_Vec2<int>&       theSize,
                            const NCollection_Vector<int>&     theColorFormats,
                            const occ::handle<OpenGl_Texture>& theDepthStencilTexture,
                            const int                          theNbSamples = 0);

  Standard_EXPORT bool Init(const occ::handle<OpenGl_Context>& theGlCtx,
                            const NCollection_Vec2<int>&       theSize,
                            const int                          theColorFormat,
                            const int                          theDepthFormat,
                            const int                          theNbSamples = 0);

  Standard_EXPORT bool Init(const occ::handle<OpenGl_Context>& theGlCtx,
                            const NCollection_Vec2<int>&       theSize,
                            const NCollection_Vector<int>&     theColorFormats,
                            const int                          theDepthFormat,
                            const int                          theNbSamples = 0);

  Standard_EXPORT bool InitLazy(const occ::handle<OpenGl_Context>& theGlCtx,
                                const NCollection_Vec2<int>&       theViewportSize,
                                const int                          theColorFormat,
                                const int                          theDepthFormat,
                                const int                          theNbSamples = 0);

  Standard_EXPORT bool InitLazy(const occ::handle<OpenGl_Context>& theGlCtx,
                                const NCollection_Vec2<int>&       theViewportSize,
                                const NCollection_Vector<int>&     theColorFormats,
                                const int                          theDepthFormat,
                                const int                          theNbSamples = 0);

  bool InitLazy(const occ::handle<OpenGl_Context>& theGlCtx,
                const OpenGl_FrameBuffer&          theFbo,
                const bool                         theToKeepMsaa = true)
  {
    return InitLazy(theGlCtx,
                    NCollection_Vec2<int>(theFbo.myVPSizeX, theFbo.myVPSizeY),
                    theFbo.myColorFormats,
                    theFbo.myDepthFormat,
                    theToKeepMsaa ? theFbo.myNbSamples : 0);
  }

  bool InitRenderBuffer(const occ::handle<OpenGl_Context>& theGlCtx,
                        const NCollection_Vec2<int>&       theSize,
                        const NCollection_Vector<int>&     theColorFormats,
                        const int                          theDepthFormat,
                        const int                          theNbSamples = 0)
  {
    return initRenderBuffer(theGlCtx, theSize, theColorFormats, theDepthFormat, theNbSamples, 0);
  }

  Standard_EXPORT bool InitWithRB(const occ::handle<OpenGl_Context>& theGlCtx,
                                  const NCollection_Vec2<int>&       theSize,
                                  const int                          theColorFormat,
                                  const int                          theDepthFormat,
                                  const unsigned int                 theColorRBufferFromWindow);

  Standard_EXPORT bool InitWrapper(const occ::handle<OpenGl_Context>& theGlCtx);

  Standard_EXPORT bool InitWrapper(
    const occ::handle<OpenGl_Context>&                       theGlContext,
    const NCollection_Sequence<occ::handle<OpenGl_Texture>>& theColorTextures,
    const occ::handle<OpenGl_Texture>& theDepthTexture = occ::handle<OpenGl_Texture>());

  Standard_EXPORT void SetupViewport(const occ::handle<OpenGl_Context>& theGlCtx);

  Standard_EXPORT void ChangeViewport(const int theVPSizeX, const int theVPSizeY);

  Standard_EXPORT virtual void BindBuffer(const occ::handle<OpenGl_Context>& theGlCtx);

  Standard_EXPORT virtual void BindDrawBuffer(const occ::handle<OpenGl_Context>& theGlCtx);

  Standard_EXPORT virtual void BindReadBuffer(const occ::handle<OpenGl_Context>& theGlCtx);

  Standard_EXPORT virtual void UnbindBuffer(const occ::handle<OpenGl_Context>& theGlCtx);

  const occ::handle<OpenGl_Texture>& ColorTexture(const int theColorBufferIndex = 0) const
  {
    return myColorTextures.Value(theColorBufferIndex);
  }

  const occ::handle<OpenGl_Texture>& DepthStencilTexture() const { return myDepthStencilTexture; }

  bool IsColorRenderBuffer() const { return myGlColorRBufferId != NO_RENDERBUFFER; }

  unsigned int ColorRenderBuffer() const { return myGlColorRBufferId; }

  bool IsDepthStencilRenderBuffer() const { return myGlDepthRBufferId != NO_RENDERBUFFER; }

  unsigned int DepthStencilRenderBuffer() const { return myGlDepthRBufferId; }

  Standard_EXPORT size_t EstimatedDataSize() const override;

public:
  Standard_EXPORT bool initRenderBuffer(const occ::handle<OpenGl_Context>& theGlCtx,
                                        const NCollection_Vec2<int>&       theSize,
                                        const NCollection_Vector<int>&     theColorFormats,
                                        const int                          theDepthFormat,
                                        const int                          theNbSamples,
                                        const unsigned int theColorRBufferFromWindow);

  Standard_DEPRECATED("Obsolete method, use Init() taking NCollection_Vec2<int>")

  bool Init(const occ::handle<OpenGl_Context>& theGlCtx,
            const int                          theSizeX,
            const int                          theSizeY,
            const NCollection_Vector<int>&     theColorFormats,
            const occ::handle<OpenGl_Texture>& theDepthStencilTexture,
            const int                          theNbSamples = 0)
  {
    return Init(theGlCtx,
                NCollection_Vec2<int>(theSizeX, theSizeY),
                theColorFormats,
                theDepthStencilTexture,
                theNbSamples);
  }

  Standard_DEPRECATED("Obsolete method, use Init() taking NCollection_Vec2<int>")

  bool Init(const occ::handle<OpenGl_Context>& theGlCtx,
            const int                          theSizeX,
            const int                          theSizeY,
            const int                          theColorFormat,
            const int                          theDepthFormat,
            const int                          theNbSamples = 0)
  {
    return Init(theGlCtx,
                NCollection_Vec2<int>(theSizeX, theSizeY),
                theColorFormat,
                theDepthFormat,
                theNbSamples);
  }

  Standard_DEPRECATED("Obsolete method, use Init() taking NCollection_Vec2<int>")

  bool Init(const occ::handle<OpenGl_Context>& theGlCtx,
            const int                          theSizeX,
            const int                          theSizeY,
            const NCollection_Vector<int>&     theColorFormats,
            const int                          theDepthFormat,
            const int                          theNbSamples = 0)
  {
    return Init(theGlCtx,
                NCollection_Vec2<int>(theSizeX, theSizeY),
                theColorFormats,
                theDepthFormat,
                theNbSamples);
  }

  Standard_DEPRECATED("Obsolete method, use InitLazy() taking NCollection_Vec2<int>")

  bool InitLazy(const occ::handle<OpenGl_Context>& theGlCtx,
                const int                          theViewportSizeX,
                const int                          theViewportSizeY,
                const int                          theColorFormat,
                const int                          theDepthFormat,
                const int                          theNbSamples = 0)
  {
    return InitLazy(theGlCtx,
                    NCollection_Vec2<int>(theViewportSizeX, theViewportSizeY),
                    theColorFormat,
                    theDepthFormat,
                    theNbSamples);
  }

  Standard_DEPRECATED("Obsolete method, use InitLazy() taking NCollection_Vec2<int>")

  bool InitLazy(const occ::handle<OpenGl_Context>& theGlCtx,
                const int                          theViewportSizeX,
                const int                          theViewportSizeY,
                const NCollection_Vector<int>&     theColorFormats,
                const int                          theDepthFormat,
                const int                          theNbSamples = 0)
  {
    return InitLazy(theGlCtx,
                    NCollection_Vec2<int>(theViewportSizeX, theViewportSizeY),
                    theColorFormats,
                    theDepthFormat,
                    theNbSamples);
  }

  Standard_DEPRECATED("Obsolete method, use InitWithRB() taking NCollection_Vec2<int>")

  bool InitWithRB(const occ::handle<OpenGl_Context>& theGlCtx,
                  const int                          theSizeX,
                  const int                          theSizeY,
                  const int                          theColorFormat,
                  const int                          theDepthFormat,
                  const unsigned int                 theColorRBufferFromWindow = 0)
  {
    return InitWithRB(theGlCtx,
                      NCollection_Vec2<int>(theSizeX, theSizeY),
                      theColorFormat,
                      theDepthFormat,
                      theColorRBufferFromWindow);
  }

protected:
  bool isValidFrameBuffer() const { return myGlFBufferId != NO_FRAMEBUFFER; }

protected:
  typedef NCollection_Vector<occ::handle<OpenGl_Texture>> OpenGl_TextureArray;

protected:
  int                     myInitVPSizeX;
  int                     myInitVPSizeY;
  int                     myVPSizeX;
  int                     myVPSizeY;
  int                     myNbSamples;
  NCollection_Vector<int> myColorFormats;
  int                     myDepthFormat;
  unsigned int            myGlFBufferId;
  unsigned int            myGlColorRBufferId;
  unsigned int            myGlDepthRBufferId;
  bool                    myIsOwnBuffer;
  bool                    myIsOwnColor;
  bool                    myIsOwnDepth;

  OpenGl_TextureArray         myColorTextures;
  occ::handle<OpenGl_Texture> myDepthStencilTexture;
};
