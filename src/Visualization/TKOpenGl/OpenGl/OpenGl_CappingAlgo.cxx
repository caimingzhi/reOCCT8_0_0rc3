#include <OpenGl_CappingAlgo.hpp>

#include <OpenGl_ClippingIterator.hpp>
#include <OpenGl_RenderFilter.hpp>
#include <OpenGl_Context.hpp>
#include <OpenGl_CappingPlaneResource.hpp>
#include <OpenGl_Structure.hpp>
#include <OpenGl_ShaderManager.hpp>

namespace
{

  struct StencilTestSentry
  {
    StencilTestSentry(const occ::handle<OpenGl_Context>& theCtx)
        : myCtx(theCtx.get()),
          myDepthFuncPrev(0)
    {
    }

    ~StencilTestSentry()
    {
      if (myDepthFuncPrev != 0)
      {
        myCtx->core11fwd->glClear(GL_STENCIL_BUFFER_BIT);
        myCtx->core11fwd->glDepthFunc(myDepthFuncPrev);
        myCtx->core11fwd->glStencilFunc(GL_ALWAYS, 0, 0xFF);
        myCtx->core11fwd->glDisable(GL_STENCIL_TEST);
      }
    }

    void Init()
    {
      if (myDepthFuncPrev == 0)
      {
        myCtx->core11fwd->glEnable(GL_STENCIL_TEST);
        myCtx->core11fwd->glGetIntegerv(GL_DEPTH_FUNC, &myDepthFuncPrev);
        myCtx->core11fwd->glDepthFunc(GL_LESS);
      }
    }

  private:
    OpenGl_Context* myCtx;
    GLint           myDepthFuncPrev;
  };

  static void renderPlane(const occ::handle<OpenGl_Workspace>&            theWorkspace,
                          const occ::handle<OpenGl_CappingPlaneResource>& thePlane)
  {
    const occ::handle<OpenGl_Context>& aContext       = theWorkspace->GetGlContext();
    const bool                         wasCullAllowed = theWorkspace->SetAllowFaceCulling(true);

    aContext->ModelWorldState.Push();
    aContext->ModelWorldState.SetCurrent(thePlane->Orientation());
    aContext->ApplyModelViewMatrix();

    thePlane->Primitives().Render(theWorkspace);

    aContext->ModelWorldState.Pop();
    aContext->ApplyModelViewMatrix();

    theWorkspace->SetAllowFaceCulling(wasCullAllowed);
  }

  static void renderCappingForStructure(StencilTestSentry&                      theStencilSentry,
                                        const occ::handle<OpenGl_Workspace>&    theWorkspace,
                                        const OpenGl_Structure&                 theStructure,
                                        const occ::handle<Graphic3d_ClipPlane>& theClipChain,
                                        const int                               theSubPlaneIndex,
                                        const occ::handle<OpenGl_CappingPlaneResource>& thePlane)
  {
    const int aPrevFilter = theWorkspace->RenderFilter();
    const int anAnyFilter =
      aPrevFilter & ~(int)(OpenGl_RenderFilter_OpaqueOnly | OpenGl_RenderFilter_TransparentOnly);

    const occ::handle<OpenGl_Context>&      aContext     = theWorkspace->GetGlContext();
    const occ::handle<Graphic3d_ClipPlane>& aRenderPlane = thePlane->Plane();
    for (OpenGl_Structure::GroupIterator aGroupIter(theStructure.Groups()); aGroupIter.More();
         aGroupIter.Next())
    {
      if (!aGroupIter.Value()->IsClosed())
      {
        continue;
      }

      theStencilSentry.Init();

      const OpenGl_Aspects* anObjAspectFace =
        aRenderPlane->ToUseObjectProperties() ? aGroupIter.Value()->GlAspects() : nullptr;
      thePlane->Update(aContext,
                       anObjAspectFace != nullptr ? anObjAspectFace->Aspect()
                                                  : occ::handle<Graphic3d_Aspects>());
      theWorkspace->SetAspects(thePlane->AspectFace());
      theWorkspace->SetRenderFilter(aPrevFilter);
      if (!theWorkspace->ShouldRender(&thePlane->Primitives(), aGroupIter.Value()))
      {
        continue;
      }

      theWorkspace->SetRenderFilter(anAnyFilter);

      aContext->ChangeClipping().DisableAllExcept(theClipChain, theSubPlaneIndex);
      aContext->ShaderManager()->UpdateClippingState();

      aContext->core11fwd->glClear(GL_STENCIL_BUFFER_BIT);
      const NCollection_Vec4<bool> aColorMaskBack = aContext->ColorMaskRGBA();
      aContext->SetColorMask(false);

      theWorkspace->SetAspects(&theWorkspace->NoneCulling());
      theWorkspace->ApplyAspects();

      if (theWorkspace->UseZBuffer())
      {
        aContext->core11fwd->glDisable(GL_DEPTH_TEST);
      }
      if (theWorkspace->UseDepthWrite())
      {
        aContext->core11fwd->glDepthMask(GL_FALSE);
      }
      aContext->core11fwd->glStencilFunc(GL_ALWAYS, 1, 0x01);
      aContext->core11fwd->glStencilOp(GL_KEEP, GL_INVERT, GL_INVERT);

      if (aRenderPlane->ToUseObjectProperties())
      {
        aGroupIter.Value()->Render(theWorkspace);
      }
      else
      {
        for (; aGroupIter.More(); aGroupIter.Next())
        {
          if (aGroupIter.Value()->IsClosed())
          {
            aGroupIter.Value()->Render(theWorkspace);
          }
        }
      }

      theWorkspace->SetAspects(&theWorkspace->FrontCulling());
      theWorkspace->ApplyAspects();

      aContext->ChangeClipping().EnableAllExcept(theClipChain, theSubPlaneIndex);
      aContext->ShaderManager()->UpdateClippingState();

      aContext->SetColorMaskRGBA(aColorMaskBack);
      if (theWorkspace->UseDepthWrite())
      {
        aContext->core11fwd->glDepthMask(GL_TRUE);
      }
      aContext->core11fwd->glStencilFunc(GL_EQUAL, 1, 0x01);
      aContext->core11fwd->glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
      if (theWorkspace->UseZBuffer())
      {
        aContext->core11fwd->glEnable(GL_DEPTH_TEST);
      }

      theWorkspace->SetAspects(thePlane->AspectFace());
      renderPlane(theWorkspace, thePlane);

      aContext->ChangeClipping().ResetCappingFilter();
      aContext->ShaderManager()->RevertClippingState();
      aContext->ShaderManager()->RevertClippingState();
    }

    if (theStructure.InstancedStructure() != nullptr)
    {
      renderCappingForStructure(theStencilSentry,
                                theWorkspace,
                                *theStructure.InstancedStructure(),
                                theClipChain,
                                theSubPlaneIndex,
                                thePlane);
    }
  }
} // namespace

void OpenGl_CappingAlgo::RenderCapping(const occ::handle<OpenGl_Workspace>& theWorkspace,
                                       const OpenGl_Structure&              theStructure)
{
  const occ::handle<OpenGl_Context>& aContext = theWorkspace->GetGlContext();
  if (!aContext->Clipping().IsCappingOn())
  {

    return;
  }

  const OpenGl_Aspects* aFaceAsp = theWorkspace->Aspects();

  const int aPrevFilter = theWorkspace->RenderFilter();
  theWorkspace->SetRenderFilter(aPrevFilter | OpenGl_RenderFilter_FillModeOnly);
  StencilTestSentry aStencilSentry(aContext);

  for (OpenGl_ClippingIterator aCappingIt(aContext->Clipping()); aCappingIt.More();
       aCappingIt.Next())
  {

    const occ::handle<Graphic3d_ClipPlane>& aClipChain = aCappingIt.Value();
    if (!aClipChain->IsCapping() || aCappingIt.IsDisabled())
    {
      continue;
    }

    int aSubPlaneIndex = 1;
    for (const Graphic3d_ClipPlane* aSubPlaneIter = aClipChain.get(); aSubPlaneIter != nullptr;
         aSubPlaneIter = aSubPlaneIter->ChainNextPlane().get(), ++aSubPlaneIndex)
    {

      const TCollection_AsciiString&           aResId = aSubPlaneIter->GetId();
      occ::handle<OpenGl_CappingPlaneResource> aPlaneRes;
      if (!aContext->GetResource(aResId, aPlaneRes))
      {

        aPlaneRes = new OpenGl_CappingPlaneResource(aSubPlaneIter);
        aContext->ShareResource(aResId, aPlaneRes);
      }

      renderCappingForStructure(aStencilSentry,
                                theWorkspace,
                                theStructure,
                                aClipChain,
                                aSubPlaneIndex,
                                aPlaneRes);

      aPlaneRes.Nullify();
      aContext->ReleaseResource(aResId, true);
    }
  }

  theWorkspace->SetAspects(aFaceAsp);
  theWorkspace->SetRenderFilter(aPrevFilter);
}
