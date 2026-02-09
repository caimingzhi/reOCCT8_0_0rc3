#pragma once

#include <D3DHost_FrameBuffer.hpp>
#include <OpenGl_View.hpp>
#include <OpenGl_Workspace.hpp>

class D3DHost_GraphicDriver;
struct IDirect3D9;
struct IDirect3DDevice9;
typedef struct _D3DPRESENT_PARAMETERS_ D3DPRESENT_PARAMETERS;

class D3DHost_View : public OpenGl_View
{

public:
  Standard_EXPORT D3DHost_View(const occ::handle<Graphic3d_StructureManager>& theMgr,
                               const occ::handle<D3DHost_GraphicDriver>&      theDriver,
                               const occ::handle<OpenGl_Caps>&                theCaps,
                               OpenGl_StateCounter*                           theCounter);

  Standard_EXPORT virtual ~D3DHost_View();

  Standard_EXPORT virtual void ReleaseGlResources(
    const occ::handle<OpenGl_Context>& theCtx) override;

  Standard_EXPORT virtual void SetWindow(const occ::handle<Graphic3d_CView>& theParentVIew,
                                         const occ::handle<Aspect_Window>&   theWindow,
                                         const Aspect_RenderingContext       theContext) override;

  Standard_EXPORT virtual void Resized() override;

  Standard_EXPORT virtual void Redraw() override;

  Standard_EXPORT virtual void RedrawImmediate() override;

  Standard_EXPORT virtual void DiagnosticInformation(
    NCollection_IndexedDataMap<TCollection_AsciiString, TCollection_AsciiString>& theDict,
    Graphic3d_DiagnosticInfo theFlags) const override;

public:
  bool isD3dEx() const { return myIsD3dEx; }

  IDirect3DDevice9* D3dDevice() const { return myD3dDevice; }

  const occ::handle<D3DHost_FrameBuffer>& D3dWglBuffer() const { return myD3dWglFbo; }

  Standard_EXPORT IDirect3DSurface9* D3dColorSurface() const;

protected:
  Standard_EXPORT static TCollection_AsciiString d3dFormatError(const long theErrCode);

  Standard_EXPORT bool d3dInitLib();

  Standard_EXPORT bool d3dInit();

  Standard_EXPORT bool d3dReset();

  Standard_EXPORT bool d3dCreateRenderTarget();

  Standard_EXPORT void d3dBeginRender();

  Standard_EXPORT void d3dEndRender();

  Standard_EXPORT bool d3dSwap();

protected:
  IDirect3D9*                               myD3dLib;
  IDirect3DDevice9*                         myD3dDevice;
  NCollection_Handle<D3DPRESENT_PARAMETERS> myD3dParams;
  unsigned int                              myRefreshRate;
  bool                                      myIsD3dEx;
  occ::handle<D3DHost_FrameBuffer>          myD3dWglFbo;

public:
  DEFINE_STANDARD_RTTIEXT(D3DHost_View, OpenGl_View)
};
