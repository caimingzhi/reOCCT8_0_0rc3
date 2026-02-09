#pragma once

#include <Graphic3d_BufferType.hpp>
#include <Graphic3d_PresentationAttributes.hpp>

#include <OpenGl_Aspects.hpp>
#include <OpenGl_Vec.hpp>

class OpenGl_FrameBuffer;
class OpenGl_Group;
class OpenGl_View;
class OpenGl_Window;
class Image_PixMap;

class OpenGl_Workspace : public Standard_Transient
{
public:
  Standard_EXPORT OpenGl_Workspace(OpenGl_View*                      theView,
                                   const occ::handle<OpenGl_Window>& theWindow);

  ~OpenGl_Workspace() override = default;

  Standard_EXPORT bool Activate();

  OpenGl_View* View() const { return myView; }

  const occ::handle<OpenGl_Context>& GetGlContext() { return myGlContext; }

  Standard_EXPORT occ::handle<OpenGl_FrameBuffer> FBOCreate(const int theWidth,
                                                            const int theHeight);

  Standard_EXPORT void FBORelease(occ::handle<OpenGl_FrameBuffer>& theFbo);

  bool BufferDump(const occ::handle<OpenGl_FrameBuffer>& theFbo,
                  Image_PixMap&                          theImage,
                  const Graphic3d_BufferType&            theBufferType);

  Standard_EXPORT int Width() const;

  Standard_EXPORT int Height() const;

  bool SetUseZBuffer(const bool theToUse)
  {
    const bool wasUsed = myUseZBuffer;
    myUseZBuffer       = theToUse;
    return wasUsed;
  }

  bool& UseZBuffer() { return myUseZBuffer; }

  bool& UseDepthWrite() { return myUseDepthWrite; }

  Standard_EXPORT Graphic3d_PolygonOffset
    SetDefaultPolygonOffset(const Graphic3d_PolygonOffset& theOffset);

  bool ToAllowFaceCulling() const { return myToAllowFaceCulling; }

  bool SetAllowFaceCulling(bool theToAllow)
  {
    const bool wasAllowed = myToAllowFaceCulling;
    myToAllowFaceCulling  = theToAllow;
    return wasAllowed;
  }

  bool ToHighlight() const { return !myHighlightStyle.IsNull(); }

  const occ::handle<Graphic3d_PresentationAttributes>& HighlightStyle() const
  {
    return myHighlightStyle;
  }

  void SetHighlightStyle(const occ::handle<Graphic3d_PresentationAttributes>& theStyle)
  {
    myHighlightStyle = theStyle;
  }

  const NCollection_Vec4<float>& EdgeColor() const
  {
    return !myHighlightStyle.IsNull() ? myHighlightStyle->ColorRGBA()
                                      : myAspectsSet->Aspect()->EdgeColorRGBA();
  }

  const NCollection_Vec4<float>& InteriorColor() const
  {
    return !myHighlightStyle.IsNull() ? myHighlightStyle->ColorRGBA()
                                      : myAspectsSet->Aspect()->InteriorColorRGBA();
  }

  const NCollection_Vec4<float>& TextColor() const
  {
    return !myHighlightStyle.IsNull() ? myHighlightStyle->ColorRGBA()
                                      : myAspectsSet->Aspect()->ColorRGBA();
  }

  const NCollection_Vec4<float>& TextSubtitleColor() const
  {
    return !myHighlightStyle.IsNull() ? myHighlightStyle->ColorRGBA()
                                      : myAspectsSet->Aspect()->ColorSubTitleRGBA();
  }

  const OpenGl_Aspects* Aspects() const { return myAspectsSet; }

  Standard_EXPORT const OpenGl_Aspects* SetAspects(const OpenGl_Aspects* theAspect);

  const occ::handle<OpenGl_TextureSet>& TextureSet() const
  {
    const occ::handle<OpenGl_TextureSet>& aTextureSet =
      myAspectsSet->TextureSet(myGlContext, ToHighlight());
    return !aTextureSet.IsNull() || myAspectsSet->Aspect()->ToMapTexture() ? aTextureSet
                                                                           : myEnvironmentTexture;
  }

  Standard_EXPORT const OpenGl_Aspects* ApplyAspects(bool theToBindTextures = true);

  void ResetAppliedAspect();

  int RenderFilter() const { return myRenderFilter; }

  void SetRenderFilter(int theFilter) { myRenderFilter = theFilter; }

  bool ShouldRender(const OpenGl_Element* theElement, const OpenGl_Group* theGroup);

  int NbSkippedTransparentElements() { return myNbSkippedTranspElems; }

  void ResetSkippedCounter() { myNbSkippedTranspElems = 0; }

  const OpenGl_Aspects& NoneCulling() const { return myNoneCulling; }

  const OpenGl_Aspects& FrontCulling() const { return myFrontCulling; }

  void SetEnvironmentTexture(const occ::handle<OpenGl_TextureSet>& theTexture)
  {
    myEnvironmentTexture = theTexture;
  }

  const occ::handle<OpenGl_TextureSet>& EnvironmentTexture() const { return myEnvironmentTexture; }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

protected:
  OpenGl_View*                myView;
  occ::handle<OpenGl_Window>  myWindow;
  occ::handle<OpenGl_Context> myGlContext;
  bool                        myUseZBuffer;
  bool                        myUseDepthWrite;
  OpenGl_Aspects              myNoneCulling;
  OpenGl_Aspects              myFrontCulling;

protected:
  int myNbSkippedTranspElems;
  int myRenderFilter;

  OpenGl_Aspects                 myDefaultAspects;
  const OpenGl_Aspects*          myAspectsSet;
  occ::handle<Graphic3d_Aspects> myAspectsApplied;

  occ::handle<Graphic3d_PresentationAttributes> myAspectFaceAppliedWithHL;

  bool                                          myToAllowFaceCulling;
  occ::handle<Graphic3d_PresentationAttributes> myHighlightStyle;

  OpenGl_Aspects myAspectFaceHl;

  occ::handle<OpenGl_TextureSet> myEnvironmentTexture;

public:
  DEFINE_STANDARD_RTTIEXT(OpenGl_Workspace, Standard_Transient)
  DEFINE_STANDARD_ALLOC
};
