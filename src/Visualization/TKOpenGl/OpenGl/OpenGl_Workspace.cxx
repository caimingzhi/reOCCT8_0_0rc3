#include <OpenGl_Workspace.hpp>

#include <OpenGl_Aspects.hpp>
#include <OpenGl_Element.hpp>
#include <OpenGl_GlCore15.hpp>
#include <OpenGl_RenderFilter.hpp>
#include <OpenGl_ShaderManager.hpp>
#include <OpenGl_View.hpp>
#include <OpenGl_Window.hpp>

IMPLEMENT_STANDARD_RTTIEXT(OpenGl_Workspace, Standard_Transient)

void OpenGl_Material::Init(const OpenGl_Context&           theCtx,
                           const Graphic3d_MaterialAspect& theFront,
                           const Quantity_Color&           theFrontColor,
                           const Graphic3d_MaterialAspect& theBack,
                           const Quantity_Color&           theBackColor)
{
  init(theCtx, theFront, theFrontColor, 0);
  if (&theFront != &theBack)
  {
    init(theCtx, theBack, theBackColor, 1);
  }
  else
  {
    Common[1] = Common[0];
    Pbr[1]    = Pbr[0];
  }
}

void OpenGl_Material::init(const OpenGl_Context&           theCtx,
                           const Graphic3d_MaterialAspect& theMat,
                           const Quantity_Color&           theInteriorColor,
                           const int                       theIndex)
{
  OpenGl_MaterialCommon& aCommon = Common[theIndex];
  OpenGl_MaterialPBR&    aPbr    = Pbr[theIndex];
  aPbr.ChangeMetallic()          = theMat.PBRMaterial().Metallic();
  aPbr.ChangeRoughness()         = theMat.PBRMaterial().NormalizedRoughness();
  aPbr.EmissionIOR =
    NCollection_Vec4<float>(theMat.PBRMaterial().Emission(), theMat.PBRMaterial().IOR());

  const NCollection_Vec3<float>& aSrcAmb = theMat.AmbientColor();
  const NCollection_Vec3<float>& aSrcDif = theMat.DiffuseColor();
  const NCollection_Vec3<float>& aSrcSpe = theMat.SpecularColor();
  const NCollection_Vec3<float>& aSrcEms = theMat.EmissiveColor();

  aCommon.SpecularShininess.SetValues(aSrcSpe, 128.0f * theMat.Shininess());

  switch (theMat.MaterialType())
  {
    case Graphic3d_MATERIAL_ASPECT:
    {
      aCommon.Diffuse.SetValues(aSrcDif * theInteriorColor, theMat.Alpha());
      aCommon.Ambient.SetValues(aSrcAmb * theInteriorColor, 1.0f);
      aCommon.Emission.SetValues(aSrcEms * theInteriorColor, 1.0f);
      aPbr.BaseColor.SetValues(theInteriorColor, theMat.Alpha());
      break;
    }
    case Graphic3d_MATERIAL_PHYSIC:
    {
      aCommon.Diffuse.SetValues(aSrcDif, theMat.Alpha());
      aCommon.Ambient.SetValues(aSrcAmb, 1.0f);
      aCommon.Emission.SetValues(aSrcEms, 1.0f);
      aPbr.BaseColor = theMat.PBRMaterial().Color();
      break;
    }
  }

  aCommon.Diffuse           = theCtx.Vec4FromQuantityColor(aCommon.Diffuse);
  aCommon.Ambient           = theCtx.Vec4FromQuantityColor(aCommon.Ambient);
  aCommon.SpecularShininess = theCtx.Vec4FromQuantityColor(aCommon.SpecularShininess);
  aCommon.Emission          = theCtx.Vec4FromQuantityColor(aCommon.Emission);
}

OpenGl_Workspace::OpenGl_Workspace(OpenGl_View*                      theView,
                                   const occ::handle<OpenGl_Window>& theWindow)
    : myView(theView),
      myWindow(theWindow),
      myGlContext(!theWindow.IsNull() ? theWindow->GetGlContext() : nullptr),
      myUseZBuffer(true),
      myUseDepthWrite(true),

      myNbSkippedTranspElems(0),
      myRenderFilter(OpenGl_RenderFilter_Empty),

      myAspectsSet(&myDefaultAspects),

      myToAllowFaceCulling(false)
{
  if (!myGlContext.IsNull() && myGlContext->MakeCurrent())
  {
    myGlContext->core11fwd->glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    if (myGlContext->core11ffp != nullptr)
    {

      myGlContext->core11ffp->glLightModeli((GLenum)GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
      myGlContext->core11fwd->glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);
      if (myGlContext->caps->ffpEnable)
      {
        myGlContext->core11fwd->glHint(GL_FOG_HINT, GL_FASTEST);
      }
    }

    if (myGlContext->GraphicsLibrary() != Aspect_GraphicsLibrary_OpenGLES)
    {
      myGlContext->core11fwd->glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
      myGlContext->core11fwd->glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);
    }
    if (myGlContext->Vendor() == "microsoft corporation" && !myGlContext->IsGlGreaterEqual(1, 2))
    {

      theView->SetImmediateModeDrawToFront(false);
    }
  }

  myNoneCulling.Aspect()->SetFaceCulling(Graphic3d_TypeOfBackfacingModel_DoubleSided);
  myNoneCulling.Aspect()->SetDrawEdges(false);
  myNoneCulling.Aspect()->SetAlphaMode(Graphic3d_AlphaMode_Opaque);

  myFrontCulling.Aspect()->SetFaceCulling(Graphic3d_TypeOfBackfacingModel_BackCulled);
  myFrontCulling.Aspect()->SetDrawEdges(false);
  myFrontCulling.Aspect()->SetAlphaMode(Graphic3d_AlphaMode_Opaque);
}

bool OpenGl_Workspace::Activate()
{
  if (myWindow.IsNull() || !myWindow->Activate())
  {
    return false;
  }

  if (myGlContext->core11ffp == nullptr)
  {
    if (myGlContext->caps->ffpEnable)
    {
      Message::SendWarning(myGlContext->GraphicsLibrary() != Aspect_GraphicsLibrary_OpenGLES
                             ? "Warning: FFP is unsupported by OpenGL ES"
                             : "Warning: FFP is unsupported by OpenGL Core Profile");
      myGlContext->caps->ffpEnable = false;
    }
  }

  if (myGlContext->caps->useZeroToOneDepth && !myGlContext->arbClipControl)
  {
    Message::SendWarning(
      "Warning: glClipControl() requires OpenGL 4.5 or GL_ARB_clip_control extension");
    myGlContext->caps->useZeroToOneDepth = false;
  }
  myView->Camera()->SetZeroToOneDepth(myGlContext->caps->useZeroToOneDepth);
  if (myGlContext->arbClipControl)
  {
    myGlContext->Functions()->glClipControl(
      GL_LOWER_LEFT,
      myGlContext->caps->useZeroToOneDepth ? GL_ZERO_TO_ONE : GL_NEGATIVE_ONE_TO_ONE);
  }

  ResetAppliedAspect();

  myGlContext->BindProgram(occ::handle<OpenGl_ShaderProgram>());
  if (myGlContext->core20fwd != nullptr)
  {
    myGlContext->core20fwd->glUseProgram(OpenGl_ShaderProgram::NO_PROGRAM);
  }
  if (myGlContext->caps->ffpEnable)
  {
    myGlContext->ShaderManager()->PushState(occ::handle<OpenGl_ShaderProgram>());
  }
  return true;
}

void OpenGl_Workspace::ResetAppliedAspect()
{
  myGlContext->BindDefaultVao();

  myHighlightStyle.Nullify();
  myToAllowFaceCulling = false;
  myAspectsSet         = &myDefaultAspects;
  myAspectsApplied.Nullify();
  myGlContext->SetPolygonOffset(Graphic3d_PolygonOffset());

  ApplyAspects();
  myGlContext->SetLineStipple(myDefaultAspects.Aspect()->LinePattern());
  myGlContext->SetLineWidth(myDefaultAspects.Aspect()->LineWidth());
  if (myGlContext->core15fwd != nullptr)
  {
    myGlContext->core15fwd->glActiveTexture(GL_TEXTURE0);
  }
}

Graphic3d_PolygonOffset OpenGl_Workspace::SetDefaultPolygonOffset(
  const Graphic3d_PolygonOffset& theOffset)
{
  Graphic3d_PolygonOffset aPrev = myDefaultAspects.Aspect()->PolygonOffset();
  myDefaultAspects.Aspect()->SetPolygonOffset(theOffset);
  if (myAspectsApplied == myDefaultAspects.Aspect() || myAspectsApplied.IsNull()
      || (myAspectsApplied->PolygonOffset().Mode & Aspect_POM_None) == Aspect_POM_None)
  {
    myGlContext->SetPolygonOffset(theOffset);
  }
  return aPrev;
}

const OpenGl_Aspects* OpenGl_Workspace::SetAspects(const OpenGl_Aspects* theAspect)
{
  const OpenGl_Aspects* aPrevAspects = myAspectsSet;
  myAspectsSet                       = theAspect;
  return aPrevAspects;
}

const OpenGl_Aspects* OpenGl_Workspace::ApplyAspects(bool theToBindTextures)
{

  Graphic3d_TypeOfBackfacingModel aCullFacesMode = myView->BackfacingModel();
  if (aCullFacesMode == Graphic3d_TypeOfBackfacingModel_Auto)
  {
    aCullFacesMode = myAspectsSet->Aspect()->FaceCulling();
    if (aCullFacesMode == Graphic3d_TypeOfBackfacingModel_Auto)
    {
      aCullFacesMode = Graphic3d_TypeOfBackfacingModel_DoubleSided;
      if (myToAllowFaceCulling)
      {
        if (myAspectsSet->Aspect()->InteriorStyle() == Aspect_IS_HATCH
            || myAspectsSet->Aspect()->AlphaMode() == Graphic3d_AlphaMode_Blend
            || myAspectsSet->Aspect()->AlphaMode() == Graphic3d_AlphaMode_Mask
            || myAspectsSet->Aspect()->AlphaMode() == Graphic3d_AlphaMode_MaskBlend
            || (myAspectsSet->Aspect()->AlphaMode() == Graphic3d_AlphaMode_BlendAuto
                && myAspectsSet->Aspect()->FrontMaterial().Transparency() != 0.0f))
        {

          aCullFacesMode = Graphic3d_TypeOfBackfacingModel_DoubleSided;
        }
        else
        {
          aCullFacesMode = Graphic3d_TypeOfBackfacingModel_BackCulled;
        }
      }
    }
  }
  myGlContext->SetFaceCulling(aCullFacesMode);

  if (myAspectsSet->Aspect() == myAspectsApplied && myHighlightStyle == myAspectFaceAppliedWithHL)
  {
    return myAspectsSet;
  }
  myAspectFaceAppliedWithHL = myHighlightStyle;

  if ((myAspectsSet->Aspect()->PolygonOffset().Mode & Aspect_POM_None) != Aspect_POM_None)
  {
    myGlContext->SetPolygonOffset(myAspectsSet->Aspect()->PolygonOffset());
  }

  const Aspect_InteriorStyle anIntstyle = myAspectsSet->Aspect()->InteriorStyle();
  if (myAspectsApplied.IsNull() || myAspectsApplied->InteriorStyle() != anIntstyle)
  {
    myGlContext->SetPolygonMode(anIntstyle == Aspect_IS_POINT ? GL_POINT : GL_FILL);
    myGlContext->SetPolygonHatchEnabled(anIntstyle == Aspect_IS_HATCH);
  }

  if (anIntstyle == Aspect_IS_HATCH)
  {
    myGlContext->SetPolygonHatchStyle(myAspectsSet->Aspect()->HatchStyle());
  }

  if (anIntstyle == Aspect_IS_HIDDENLINE)
  {

    *myAspectFaceHl.Aspect() = *myAspectsSet->Aspect();
    myAspectFaceHl.Aspect()->SetShadingModel(Graphic3d_TypeOfShadingModel_Unlit);
    myAspectFaceHl.Aspect()->SetInteriorColor(myView->BackgroundColor().GetRGB());
    myAspectFaceHl.Aspect()->SetDistinguish(false);
    myAspectFaceHl.SetNoLighting();
    myAspectsSet = &myAspectFaceHl;
  }
  else
  {
    myGlContext->SetShadingMaterial(myAspectsSet, myHighlightStyle);
  }

  if (theToBindTextures)
  {
    const occ::handle<OpenGl_TextureSet>& aTextureSet = TextureSet();
    myGlContext->BindTextures(aTextureSet, occ::handle<OpenGl_ShaderProgram>());
  }

  if ((myView->ShadingModel() == Graphic3d_TypeOfShadingModel_Pbr
       || myView->ShadingModel() == Graphic3d_TypeOfShadingModel_PbrFacet)
      && !myView->myPBREnvironment.IsNull() && myView->myPBREnvironment->IsNeededToBeBound())
  {
    myView->myPBREnvironment->Bind(myGlContext);
  }

  myAspectsApplied = myAspectsSet->Aspect();
  return myAspectsSet;
}

int OpenGl_Workspace::Width() const
{
  return !myView->GlWindow().IsNull() ? myView->GlWindow()->Width() : 0;
}

int OpenGl_Workspace::Height() const
{
  return !myView->GlWindow().IsNull() ? myView->GlWindow()->Height() : 0;
}

occ::handle<OpenGl_FrameBuffer> OpenGl_Workspace::FBOCreate(const int theWidth, const int theHeight)
{

  if (!Activate())
    return occ::handle<OpenGl_FrameBuffer>();

  const occ::handle<OpenGl_Context>& aCtx = GetGlContext();
  aCtx->BindTextures(occ::handle<OpenGl_TextureSet>(), occ::handle<OpenGl_ShaderProgram>());
  occ::handle<OpenGl_FrameBuffer> aFrameBuffer = new OpenGl_FrameBuffer();
  if (!aFrameBuffer->Init(aCtx,
                          NCollection_Vec2<int>(theWidth, theHeight),
                          GL_SRGB8_ALPHA8,
                          GL_DEPTH24_STENCIL8,
                          0))
  {
    aFrameBuffer->Release(aCtx.operator->());
    return occ::handle<OpenGl_FrameBuffer>();
  }
  return aFrameBuffer;
}

void OpenGl_Workspace::FBORelease(occ::handle<OpenGl_FrameBuffer>& theFbo)
{

  if (!Activate() || theFbo.IsNull())
  {
    return;
  }

  theFbo->Release(GetGlContext().operator->());
  theFbo.Nullify();
}

bool OpenGl_Workspace::BufferDump(const occ::handle<OpenGl_FrameBuffer>& theFbo,
                                  Image_PixMap&                          theImage,
                                  const Graphic3d_BufferType&            theBufferType)
{
  return !theImage.IsEmpty() && Activate()
         && OpenGl_FrameBuffer::BufferDump(GetGlContext(), theFbo, theImage, theBufferType);
}

bool OpenGl_Workspace::ShouldRender(const OpenGl_Element* theElement, const OpenGl_Group* theGroup)
{
  if ((myRenderFilter & OpenGl_RenderFilter_SkipTrsfPersistence) != 0)
  {
    if (theGroup->HasPersistence())
    {
      return false;
    }
  }

  if ((myRenderFilter & OpenGl_RenderFilter_NonRaytraceableOnly) != 0)
  {
    if (!theGroup->HasPersistence() && OpenGl_Raytrace::IsRaytracedElement(theElement))
    {
      return false;
    }
  }
  else if ((myRenderFilter & OpenGl_RenderFilter_FillModeOnly) != 0)
  {
    if (!theElement->IsFillDrawMode())
    {
      return false;
    }
  }

  if ((myRenderFilter & OpenGl_RenderFilter_OpaqueOnly) != 0)
  {
    if (!theElement->IsFillDrawMode())
    {
      return true;
    }

    if (OpenGl_Context::CheckIsTransparent(myAspectsSet, myHighlightStyle))
    {
      ++myNbSkippedTranspElems;
      return false;
    }
  }
  else if ((myRenderFilter & OpenGl_RenderFilter_TransparentOnly) != 0)
  {
    if (!theElement->IsFillDrawMode())
    {
      if (dynamic_cast<const OpenGl_Aspects*>(theElement) == nullptr)
      {
        return false;
      }
    }
    else if (!OpenGl_Context::CheckIsTransparent(myAspectsSet, myHighlightStyle))
    {
      return false;
    }
  }
  return true;
}

void OpenGl_Workspace::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myUseZBuffer)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myUseDepthWrite)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &myNoneCulling)
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &myFrontCulling)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myNbSkippedTranspElems)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myRenderFilter)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &myDefaultAspects)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myAspectsSet)
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myAspectsApplied.get())

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myToAllowFaceCulling)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &myAspectFaceHl)
}
