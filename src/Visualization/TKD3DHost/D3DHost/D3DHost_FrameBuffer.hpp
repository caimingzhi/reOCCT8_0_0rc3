#pragma once

#include <OpenGl_FrameBuffer.hpp>

struct IDirect3DDevice9;
struct IDirect3DSurface9;

class D3DHost_FrameBuffer : public OpenGl_FrameBuffer
{
public:
  Standard_EXPORT D3DHost_FrameBuffer();

  Standard_EXPORT ~D3DHost_FrameBuffer();

  Standard_EXPORT virtual void Release(OpenGl_Context* theCtx) override;

  Standard_EXPORT bool Init(const occ::handle<OpenGl_Context>& theCtx,
                            IDirect3DDevice9*                  theD3DDevice,
                            const bool                         theIsD3dEx,
                            const int                          theSizeX,
                            const int                          theSizeY);

  Standard_EXPORT bool InitD3dInterop(const occ::handle<OpenGl_Context>& theCtx,
                                      IDirect3DDevice9*                  theD3DDevice,
                                      const bool                         theIsD3dEx,
                                      const int                          theSizeX,
                                      const int                          theSizeY,
                                      const int                          theDepthFormat);

  Standard_EXPORT bool InitD3dFallback(const occ::handle<OpenGl_Context>& theCtx,
                                       IDirect3DDevice9*                  theD3DDevice,
                                       const bool                         theIsD3dEx,
                                       const int                          theSizeX,
                                       const int                          theSizeY,
                                       const int                          theDepthFormat);

  Standard_EXPORT bool registerD3dBuffer(const occ::handle<OpenGl_Context>& theCtx);

  Standard_EXPORT virtual void BindBuffer(const occ::handle<OpenGl_Context>& theCtx) override;

  Standard_EXPORT virtual void LockSurface(const occ::handle<OpenGl_Context>& theCtx);

  Standard_EXPORT virtual void UnlockSurface(const occ::handle<OpenGl_Context>& theCtx);

  IDirect3DSurface9* D3dColorSurface() { return myD3dSurf; }

  void* D3dColorSurfaceShare() { return myD3dSurfShare; }

  bool D3dFallback() const { return myD3dFallback; }

  bool IsSRGBReady() const { return myIsSRGBReady; }

  void SetSRGBReady(bool theIsReady) { myIsSRGBReady = theIsReady; }

protected:
  using OpenGl_FrameBuffer::Init;

protected:
  IDirect3DSurface9* myD3dSurf;
  void*              myD3dSurfShare;
  void*              myGlD3dDevice;
  void*              myGlD3dSurf;
  int                myLockCount;

  bool myD3dFallback;

  bool myIsSRGBReady;

public:
  DEFINE_STANDARD_RTTIEXT(D3DHost_FrameBuffer, OpenGl_FrameBuffer)
};
