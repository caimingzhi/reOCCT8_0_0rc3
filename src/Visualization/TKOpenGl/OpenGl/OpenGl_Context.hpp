#pragma once

#include <Aspect_Drawable.hpp>

typedef void* Aspect_Display;

#include <Aspect_GraphicsLibrary.hpp>
#include <Aspect_RenderingContext.hpp>
#include <Graphic3d_DiagnosticInfo.hpp>
#include <Message.hpp>
#include <OpenGl_Caps.hpp>
#include <OpenGl_LineAttributes.hpp>
#include <OpenGl_Material.hpp>

#ifndef _OpenGl_MatrixState_H__
  #define _OpenGl_MatrixState_H__

  #include <OpenGl_Vec.hpp>
  #include <NCollection_Vector.hpp>
  #include <Standard_Dump.hpp>

template <class T>
class OpenGl_MatrixState
{
public:
  OpenGl_MatrixState()
      : myStack(8),
        myStackHead(-1)
  {
  }

  void Push()
  {
    if (++myStackHead >= myStack.Size())
    {
      myStack.Append(myCurrent);
    }
    else
    {
      myStack.SetValue(myStackHead, myCurrent);
    }
  }

  void Pop()
  {
    Standard_ASSERT_RETURN(myStackHead != -1,
                           "Matrix stack already empty when MatrixState.Pop() called.",
                           Standard_VOID_RETURN);
    myCurrent = myStack.Value(myStackHead--);
  }

  const typename OpenGl::MatrixType<T>::Mat4& Current() { return myCurrent; }

  void SetCurrent(const typename OpenGl::MatrixType<T>::Mat4& theNewCurrent)
  {
    myCurrent = theNewCurrent;
  }

  typename OpenGl::MatrixType<T>::Mat4& ChangeCurrent() { return myCurrent; }

  template <typename Other_t>
  void SetCurrent(const typename OpenGl::MatrixType<Other_t>::Mat4& theNewCurrent)
  {
    myCurrent.Convert(theNewCurrent);
  }

  void SetIdentity() { myCurrent = typename OpenGl::MatrixType<T>::Mat4(); }

  void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const
  {
    (void)theDepth;
    OCCT_DUMP_FIELD_VALUES_NUMERICAL(theOStream,
                                     "myCurrent",
                                     16,
                                     myCurrent.GetValue(0, 0),
                                     myCurrent.GetValue(0, 1),
                                     myCurrent.GetValue(0, 2),
                                     myCurrent.GetValue(0, 3),
                                     myCurrent.GetValue(1, 0),
                                     myCurrent.GetValue(1, 1),
                                     myCurrent.GetValue(1, 2),
                                     myCurrent.GetValue(1, 3),
                                     myCurrent.GetValue(2, 0),
                                     myCurrent.GetValue(2, 1),
                                     myCurrent.GetValue(2, 2),
                                     myCurrent.GetValue(2, 3),
                                     myCurrent.GetValue(3, 0),
                                     myCurrent.GetValue(3, 1),
                                     myCurrent.GetValue(3, 2),
                                     myCurrent.GetValue(3, 3))

    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myStack.Size())
    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myStackHead)
  }

private:
  NCollection_Vector<typename OpenGl::MatrixType<T>::Mat4> myStack;

  typename OpenGl::MatrixType<T>::Mat4 myCurrent;
  int                                  myStackHead;
};

#endif

#include <OpenGl_Vec.hpp>
#include <OpenGl_Resource.hpp>
#include <OpenGl_TextureSet.hpp>
#include <Standard_Transient.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <TColStd_PackedMapOfInteger.hpp>
#include <OpenGl_Clipping.hpp>

#include <NCollection_Shared.hpp>

#include <memory>

#if defined(__APPLE__)
  #import <TargetConditionals.h>
  #if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
    #ifdef __OBJC__
@class EAGLContext;
    #else
struct EAGLContext;
    #endif
  #else
    #ifdef __OBJC__
@class NSOpenGLContext;
    #else
struct NSOpenGLContext;
    #endif
  #endif
#endif

struct OpenGl_GlFunctions;
struct OpenGl_ArbTBO;
struct OpenGl_ArbIns;
struct OpenGl_ArbDbg;
struct OpenGl_ArbFBO;
struct OpenGl_ArbFBOBlit;
struct OpenGl_ArbSamplerObject;
struct OpenGl_ArbTexBindless;
struct OpenGl_ExtGS;

struct OpenGl_GlCore11Fwd;
struct OpenGl_GlCore11;
struct OpenGl_GlCore12;
struct OpenGl_GlCore13;
struct OpenGl_GlCore14;
struct OpenGl_GlCore15;
struct OpenGl_GlCore20;
struct OpenGl_GlCore21;
struct OpenGl_GlCore30;
struct OpenGl_GlCore31;
struct OpenGl_GlCore32;
struct OpenGl_GlCore33;
struct OpenGl_GlCore40;
struct OpenGl_GlCore41;
struct OpenGl_GlCore42;
struct OpenGl_GlCore43;
struct OpenGl_GlCore44;
struct OpenGl_GlCore45;
struct OpenGl_GlCore46;

class Graphic3d_Camera;
class Graphic3d_PresentationAttributes;
class OpenGl_Aspects;
class OpenGl_FrameBuffer;
class OpenGl_ShaderProgram;
class OpenGl_ShaderManager;
class OpenGl_FrameStats;

enum OpenGl_FeatureFlag
{
  OpenGl_FeatureNotAvailable = 0,
  OpenGl_FeatureInExtensions = 1,
  OpenGl_FeatureInCore       = 2
};

class OpenGl_Context : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(OpenGl_Context, Standard_Transient)
  friend class OpenGl_Window;
  friend struct OpenGl_GlFunctions;

public:
  typedef NCollection_Shared<
    NCollection_DataMap<TCollection_AsciiString, occ::handle<OpenGl_Resource>>>
    OpenGl_ResourcesMap;

  inline static int GetPowerOfTwo(const int theNumber, const int theThreshold)
  {
    for (int p2 = 2; p2 <= theThreshold; p2 <<= 1)
    {
      if (theNumber <= p2)
      {
        return p2;
      }
    }
    return theThreshold;
  }

  Standard_EXPORT static TCollection_AsciiString FormatGlEnumHex(int theGlEnum);

  Standard_EXPORT static TCollection_AsciiString FormatPointer(const void* thePtr);

  Standard_EXPORT static TCollection_AsciiString FormatSize(size_t theSize);

  Standard_EXPORT static TCollection_AsciiString FormatGlError(int theGlError);

public:
  Standard_EXPORT OpenGl_Context(const occ::handle<OpenGl_Caps>& theCaps = nullptr);

  Standard_EXPORT ~OpenGl_Context() override;

  Standard_EXPORT void forcedRelease();

  Standard_EXPORT void Share(const occ::handle<OpenGl_Context>& theShareCtx);

  Standard_EXPORT bool Init(const bool theIsCoreProfile = false);

  inline bool IsValid() const { return myIsInitialized; }

  Standard_EXPORT bool Init(const Aspect_Drawable         theSurface,
                            const Aspect_Display          theDisplay,
                            const Aspect_RenderingContext theContext,
                            const bool                    theIsCoreProfile = false);

  Aspect_Drawable Window() const { return myWindow; }

  Aspect_Display GetDisplay() const { return myDisplay; }

  Aspect_RenderingContext RenderingContext() const { return myGContext; }

#if defined(__APPLE__) && !defined(HAVE_XLIB)
  #if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE

  bool Init(EAGLContext* theGContext, const bool theIsCoreProfile = false)
  {
    return Init((Aspect_Drawable)0,
                (Aspect_Display)0,
                (Aspect_RenderingContext)theGContext,
                theIsCoreProfile);
  }
  #else

  bool Init(NSOpenGLContext* theGContext, const bool theIsCoreProfile = false)
  {
    return Init((Aspect_Drawable)0,
                (Aspect_Display)0,
                (Aspect_RenderingContext)theGContext,
                theIsCoreProfile);
  }
  #endif
#endif

  Standard_EXPORT static void ReadGlVersion(int& theGlVerMajor, int& theGlVerMinor);

  Standard_EXPORT bool CheckExtension(const char* theExtName) const;

  Standard_EXPORT static bool CheckExtension(const char* theExtString, const char* theExtName);

  template <typename FuncType_t>
  bool FindProcVerbose(const char*& theLastFailFuncName,
                       const char*  theFuncName,
                       FuncType_t&  theFuncPtr)
  {
    theFuncPtr = (FuncType_t)findProc(theFuncName);
    if (theFuncPtr == nullptr)
    {
      theLastFailFuncName = theFuncName;
      return false;
    }
    return true;
  }

  template <typename FuncType_t>
  bool FindProc(const char* theFuncName, FuncType_t& theFuncPtr)
  {
    theFuncPtr = (FuncType_t)findProc(theFuncName);
    return (theFuncPtr != nullptr);
  }

  Aspect_GraphicsLibrary GraphicsLibrary() const { return myGapi; }

  inline bool IsGlGreaterEqual(const int theVerMajor, const int theVerMinor) const
  {
    return (myGlVerMajor > theVerMajor)
           || (myGlVerMajor == theVerMajor && myGlVerMinor >= theVerMinor);
  }

  int VersionMajor() const { return myGlVerMajor; }

  int VersionMinor() const { return myGlVerMinor; }

  const OpenGl_GlFunctions* Functions() const { return myFuncs.get(); }

  Standard_EXPORT bool ResetErrors(const bool theToPrintErrors = false);

  Standard_EXPORT bool IsCurrent() const;

  Standard_EXPORT bool MakeCurrent();

  Standard_EXPORT void SwapBuffers();

  Standard_EXPORT bool SetSwapInterval(const int theInterval);

  Standard_EXPORT bool IsRender() const;

  Standard_EXPORT bool IsFeedback() const;

  Standard_EXPORT size_t AvailableMemory() const;

  Standard_EXPORT TCollection_AsciiString MemoryInfo() const;

  Standard_EXPORT void MemoryInfo(
    NCollection_IndexedDataMap<TCollection_AsciiString, TCollection_AsciiString>& theDict) const;

  Standard_EXPORT void DiagnosticInformation(
    NCollection_IndexedDataMap<TCollection_AsciiString, TCollection_AsciiString>& theDict,
    Graphic3d_DiagnosticInfo                                                      theFlags) const;

  Standard_EXPORT void WindowBufferBits(NCollection_Vec4<int>& theColorBits,
                                        NCollection_Vec2<int>& theDepthStencilBits) const;

  Standard_EXPORT const occ::handle<OpenGl_Resource>& GetResource(
    const TCollection_AsciiString& theKey) const;

  template <typename TheHandleType>
  bool GetResource(const TCollection_AsciiString& theKey, TheHandleType& theValue) const
  {
    const occ::handle<OpenGl_Resource>& aResource = GetResource(theKey);
    if (aResource.IsNull())
    {
      return false;
    }

    theValue = TheHandleType::DownCast(aResource);
    return !theValue.IsNull();
  }

  Standard_EXPORT bool ShareResource(const TCollection_AsciiString&      theKey,
                                     const occ::handle<OpenGl_Resource>& theResource);

  Standard_EXPORT void ReleaseResource(const TCollection_AsciiString& theKey,
                                       const bool                     theToDelay = false);

  template <class T>
  void DelayedRelease(occ::handle<T>& theResource)
  {
    myUnusedResources->Prepend(theResource);
    theResource.Nullify();
  }

  Standard_EXPORT void ReleaseDelayed();

  const OpenGl_ResourcesMap& SharedResources() const { return *mySharedResources; }

  inline OpenGl_Clipping& ChangeClipping() { return myClippingState; }

  inline const OpenGl_Clipping& Clipping() const { return myClippingState; }

  inline const occ::handle<OpenGl_ShaderManager>& ShaderManager() const { return myShaderManager; }

public:
  int TextureWrapClamp() const { return myTexClamp; }

  bool HasTextureBaseLevel() const
  {
    return myGapi == Aspect_GraphicsLibrary_OpenGLES ? IsGlGreaterEqual(3, 0)
                                                     : IsGlGreaterEqual(1, 2);
  }

  const occ::handle<Image_SupportedFormats>& SupportedTextureFormats() const
  {
    return mySupportedFormats;
  }

  int MaxDegreeOfAnisotropy() const { return myAnisoMax; }

  int MaxTextureSize() const { return myMaxTexDim; }

  int MaxCombinedTextureUnits() const { return myMaxTexCombined; }

  int MaxTextureUnitsFFP() const { return myMaxTexUnitsFFP; }

  Graphic3d_TextureUnit SpriteTextureUnit() const { return mySpriteTexUnit; }

  bool HasTextureMultisampling() const { return myHasMsaaTextures; }

  int MaxMsaaSamples() const { return myMaxMsaaSamples; }

  int MaxDumpSizeX() const { return myMaxDumpSizeX; }

  int MaxDumpSizeY() const { return myMaxDumpSizeY; }

  int MaxDrawBuffers() const { return myMaxDrawBuffers; }

  int MaxColorAttachments() const { return myMaxColorAttachments; }

  int MaxClipPlanes() const { return myMaxClipPlanes; }

  bool HasRayTracing() const { return myHasRayTracing; }

  bool HasRayTracingTextures() const { return myHasRayTracingTextures; }

  bool HasRayTracingAdaptiveSampling() const { return myHasRayTracingAdaptiveSampling; }

  bool HasRayTracingAdaptiveSamplingAtomic() const { return myHasRayTracingAdaptiveSamplingAtomic; }

  bool HasSRGB() const { return hasTexSRGB && hasFboSRGB; }

  bool ToRenderSRGB() const { return HasSRGB() && !caps->sRGBDisable && !caps->ffpEnable; }

  bool IsWindowSRGB() const { return myIsSRgbWindow; }

  void SetWindowSRGB(bool theIsSRgb) { myIsSRgbWindow = theIsSRgb; }

  bool IsWindowDeepColor() const { return myIsWindowDeepColor; }

  NCollection_Vec4<float> Vec4FromQuantityColor(const NCollection_Vec4<float>& theColor) const
  {
    return myIsSRgbActive ? Vec4LinearFromQuantityColor(theColor)
                          : Vec4sRGBFromQuantityColor(theColor);
  }

  const NCollection_Vec4<float>& Vec4LinearFromQuantityColor(
    const NCollection_Vec4<float>& theColor) const
  {
    return theColor;
  }

  NCollection_Vec4<float> Vec4sRGBFromQuantityColor(const NCollection_Vec4<float>& theColor) const
  {
    return Quantity_ColorRGBA::Convert_LinearRGB_To_sRGB(theColor);
  }

  bool HasPBR() const { return myHasPBR; }

  Graphic3d_TextureUnit PBREnvLUTTexUnit() const { return myPBREnvLUTTexUnit; }

  Graphic3d_TextureUnit PBRDiffIBLMapSHTexUnit() const { return myPBRDiffIBLMapSHTexUnit; }

  Graphic3d_TextureUnit PBRSpecIBLMapTexUnit() const { return myPBRSpecIBLMapTexUnit; }

  Graphic3d_TextureUnit ShadowMapTexUnit() const { return myShadowMapTexUnit; }

  Graphic3d_TextureUnit DepthPeelingDepthTexUnit() const { return myDepthPeelingDepthTexUnit; }

  Graphic3d_TextureUnit DepthPeelingFrontColorTexUnit() const
  {
    return myDepthPeelingFrontColorTexUnit;
  }

  inline bool ToUseVbo() const { return core15fwd != nullptr && !caps->vboDisable; }

  bool IsGlNormalizeEnabled() const { return myIsGlNormalizeEnabled; }

  Standard_EXPORT bool SetGlNormalizeEnabled(bool isEnabled);

  int PolygonMode() const { return myPolygonMode; }

  Standard_EXPORT int SetPolygonMode(const int theMode);

  bool IsPolygonHatchEnabled() const { return myHatchIsEnabled; }

  Standard_EXPORT bool SetPolygonHatchEnabled(const bool theIsEnabled);

  int PolygonHatchStyle() const { return myActiveHatchType; }

  Standard_EXPORT int SetPolygonHatchStyle(const occ::handle<Graphic3d_HatchStyle>& theStyle);

  Standard_EXPORT void SetPolygonOffset(const Graphic3d_PolygonOffset& theOffset);

  const Graphic3d_PolygonOffset& PolygonOffset() const { return myPolygonOffset; }

  const occ::handle<Graphic3d_Camera>& Camera() const { return myCamera; }

  Standard_EXPORT void SetCamera(const occ::handle<Graphic3d_Camera>& theCamera);

  Standard_EXPORT void ApplyModelWorldMatrix();

  Standard_EXPORT void ApplyWorldViewMatrix();

  Standard_EXPORT void ApplyModelViewMatrix();

  Standard_EXPORT void ApplyProjectionMatrix();

public:
  inline const occ::handle<Message_Messenger>& Messenger() const
  {
    return ::Message::DefaultMessenger();
  }

  Standard_EXPORT void PushMessage(const unsigned int                theSource,
                                   const unsigned int                theType,
                                   const unsigned int                theId,
                                   const unsigned int                theSeverity,
                                   const TCollection_ExtendedString& theMessage);

  Standard_EXPORT bool ExcludeMessage(const unsigned int theSource, const unsigned int theId);

  Standard_EXPORT bool IncludeMessage(const unsigned int theSource, const unsigned int theId);

  bool HasStereoBuffers() const { return myIsStereoBuffers; }

public:
  const occ::handle<OpenGl_FrameStats>& FrameStats() const { return myFrameStats; }

  void SetFrameStats(const occ::handle<OpenGl_FrameStats>& theStats) { myFrameStats = theStats; }

  const int* Viewport() const { return myViewport; }

  Standard_EXPORT void ResizeViewport(const int theRect[4]);

  const int* VirtualViewport() const { return myViewportVirt; }

  int ReadBuffer() { return myReadBuffer; }

  Standard_EXPORT void SetReadBuffer(const int theReadBuffer);

  int DrawBuffer(int theIndex = 0) const
  {
    return theIndex >= myDrawBuffers.Lower() && theIndex <= myDrawBuffers.Upper()
             ? myDrawBuffers.Value(theIndex)
             : 0;
  }

  Standard_EXPORT void SetDrawBuffer(const int theDrawBuffer);

  Standard_EXPORT void SetDrawBuffers(const int theNb, const int* theDrawBuffers);

  void SetReadDrawBuffer(const int theBuffer)
  {
    SetReadBuffer(theBuffer);
    SetDrawBuffer(theBuffer);
  }

  bool IsFrameBufferSRGB() const { return myIsSRgbActive; }

  Standard_EXPORT void SetFrameBufferSRGB(bool theIsFbo, bool theIsFboSRgb = true);

  const NCollection_Vec4<bool>& ColorMaskRGBA() const { return myColorMask; }

  Standard_EXPORT void SetColorMaskRGBA(const NCollection_Vec4<bool>& theToWriteColor);

  bool ColorMask() const { return myColorMask.r(); }

  Standard_EXPORT bool SetColorMask(bool theToWriteColor);

  bool AllowSampleAlphaToCoverage() const { return myAllowAlphaToCov; }

  void SetAllowSampleAlphaToCoverage(bool theToEnable) { myAllowAlphaToCov = theToEnable; }

  bool SampleAlphaToCoverage() const { return myAlphaToCoverage; }

  Standard_EXPORT bool SetSampleAlphaToCoverage(bool theToEnable);

  Graphic3d_TypeOfBackfacingModel FaceCulling() const { return myFaceCulling; }

  Standard_EXPORT void SetFaceCulling(Graphic3d_TypeOfBackfacingModel theMode);

  bool ToCullBackFaces() const
  {
    return myFaceCulling == Graphic3d_TypeOfBackfacingModel_BackCulled;
  }

  void SetCullBackFaces(bool theToEnable)
  {
    SetFaceCulling(theToEnable ? Graphic3d_TypeOfBackfacingModel_BackCulled
                               : Graphic3d_TypeOfBackfacingModel_DoubleSided);
  }

  Standard_EXPORT void FetchState();

  const occ::handle<OpenGl_TextureSet>& ActiveTextures() const { return myActiveTextures; }

  Standard_DEPRECATED("BindTextures() with explicit GLSL program should be used instead")

  occ::handle<OpenGl_TextureSet> BindTextures(const occ::handle<OpenGl_TextureSet>& theTextures)
  {
    return BindTextures(theTextures, myActiveProgram);
  }

  Standard_EXPORT occ::handle<OpenGl_TextureSet> BindTextures(
    const occ::handle<OpenGl_TextureSet>&    theTextures,
    const occ::handle<OpenGl_ShaderProgram>& theProgram);

  const occ::handle<OpenGl_ShaderProgram>& ActiveProgram() const { return myActiveProgram; }

  Standard_EXPORT bool BindProgram(const occ::handle<OpenGl_ShaderProgram>& theProgram);

  Standard_EXPORT void SetShadingMaterial(
    const OpenGl_Aspects*                                theAspect,
    const occ::handle<Graphic3d_PresentationAttributes>& theHighlight);

  Standard_EXPORT static bool CheckIsTransparent(
    const OpenGl_Aspects*                                theAspect,
    const occ::handle<Graphic3d_PresentationAttributes>& theHighlight,
    float&                                               theAlphaFront,
    float&                                               theAlphaBack);

  static bool CheckIsTransparent(const OpenGl_Aspects*                                theAspect,
                                 const occ::handle<Graphic3d_PresentationAttributes>& theHighlight)
  {
    float anAlphaFront = 1.0f, anAlphaBack = 1.0f;
    return CheckIsTransparent(theAspect, theHighlight, anAlphaFront, anAlphaBack);
  }

  Standard_EXPORT void SetColor4fv(const NCollection_Vec4<float>& theColor);

  Standard_EXPORT void SetTypeOfLine(const Aspect_TypeOfLine theType, const float theFactor = 1.0f);

  void SetLineStipple(const uint16_t thePattern) { SetLineStipple(1.0f, thePattern); }

  Standard_EXPORT void SetLineStipple(const float theFactor, const uint16_t thePattern);

  Standard_EXPORT void SetLineWidth(const float theWidth);

  Standard_EXPORT void SetPointSize(const float theSize);

  Standard_EXPORT void SetPointSpriteOrigin();

  Standard_EXPORT void SetTextureMatrix(const occ::handle<Graphic3d_TextureParams>& theParams,
                                        const bool                                  theIsTopDown);

  Standard_EXPORT void BindDefaultVao();

  const occ::handle<OpenGl_FrameBuffer>& DefaultFrameBuffer() const { return myDefaultFbo; }

  Standard_EXPORT occ::handle<OpenGl_FrameBuffer> SetDefaultFrameBuffer(
    const occ::handle<OpenGl_FrameBuffer>& theFbo);

  bool IsDebugContext() const { return myIsGlDebugCtx; }

  Standard_EXPORT void EnableFeatures() const;

  Standard_EXPORT void DisableFeatures() const;

  unsigned int Resolution() const { return myResolution; }

  float ResolutionRatio() const { return myResolutionRatio; }

  float RenderScale() const { return myRenderScale; }

  bool HasRenderScale() const { return std::abs(myRenderScale - 1.0f) > 0.0001f; }

  float RenderScaleInv() const { return myRenderScaleInv; }

  float LineWidthScale() const { return myLineWidthScale; }

  void SetResolution(unsigned int theResolution, float theRatio, float theScale)
  {
    myResolution     = (unsigned int)(theScale * theResolution + 0.5f);
    myRenderScale    = theScale;
    myRenderScaleInv = 1.0f / theScale;
    SetResolutionRatio(theRatio * theScale);
  }

  void SetResolutionRatio(const float theRatio)
  {
    myResolutionRatio = theRatio;
    myLineWidthScale  = (std::max)(1.0f, std::floor(theRatio + 0.5f));
  }

  float LineFeather() const { return myLineFeather; }

  void SetLineFeather(float theValue) { myLineFeather = theValue; }

  Standard_EXPORT bool GetBufferSubData(unsigned int theTarget,
                                        intptr_t     theOffset,
                                        intptr_t     theSize,
                                        void*        theData);

  const TCollection_AsciiString& Vendor() const { return myVendor; }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  Standard_EXPORT void DumpJsonOpenGlState(Standard_OStream& theOStream, int theDepth = -1);

  Standard_EXPORT void SetShadeModel(Graphic3d_TypeOfShadingModel theModel);

private:
  Standard_EXPORT void* findProc(const char* theFuncName);

  Standard_EXPORT void checkWrongVersion(int         theGlVerMajor,
                                         int         theGlVerMinor,
                                         const char* theLastFailedProc);

  Standard_EXPORT void init(const bool theIsCoreProfile);

public:
  OpenGl_GlCore11*    core11ffp;
  OpenGl_GlCore11Fwd* core11fwd;
  OpenGl_GlCore15*    core15;
  OpenGl_GlCore20*    core20;
  OpenGl_GlCore30*    core30;
  OpenGl_GlCore32*    core32;
  OpenGl_GlCore33*    core33;
  OpenGl_GlCore41*    core41;
  OpenGl_GlCore42*    core42;
  OpenGl_GlCore43*    core43;
  OpenGl_GlCore44*    core44;
  OpenGl_GlCore45*    core45;
  OpenGl_GlCore46*    core46;

  OpenGl_GlCore15* core15fwd;
  OpenGl_GlCore20* core20fwd;

  occ::handle<OpenGl_Caps> caps;

public:
  bool                     hasGetBufferData;
  bool                     hasPackRowLength;
  bool                     hasUnpackRowLength;
  bool                     hasHighp;
  bool                     hasUintIndex;
  bool                     hasTexRGBA8;
  bool                     hasTexFloatLinear;
  bool                     hasTexSRGB;
  bool                     hasFboSRGB;
  bool                     hasSRGBControl;
  bool                     hasFboRenderMipmap;
  OpenGl_FeatureFlag       hasFlatShading;
  OpenGl_FeatureFlag       hasGlslBitwiseOps;
  OpenGl_FeatureFlag       hasDrawBuffers;
  OpenGl_FeatureFlag       hasFloatBuffer;
  OpenGl_FeatureFlag       hasHalfFloatBuffer;
  OpenGl_FeatureFlag       hasSampleVariables;
  OpenGl_FeatureFlag       hasGeometryStage;
  bool                     arbDrawBuffers;
  bool                     arbNPTW;
  bool                     arbTexRG;
  bool                     arbTexFloat;
  OpenGl_ArbSamplerObject* arbSamplerObject;
  OpenGl_ArbTexBindless*   arbTexBindless;
  OpenGl_ArbTBO*           arbTBO;
  bool                     arbTboRGB32;
  bool                     arbClipControl;
  OpenGl_ArbIns*           arbIns;
  OpenGl_ArbDbg*           arbDbg;
  OpenGl_ArbFBO*           arbFBO;
  OpenGl_ArbFBOBlit*       arbFBOBlit;
  bool                     arbSampleShading;
  bool                     arbDepthClamp;
  bool                     extFragDepth;
  bool                     extDrawBuffers;
  OpenGl_ExtGS*            extGS;
  bool                     extBgra;
  bool                     extTexR16;

  bool extAnis;
  bool extPDS;
  bool atiMem;
  bool nvxMem;
  bool oesSampleVariables;
  bool oesStdDerivatives;

public:
  OpenGl_MatrixState<float> ModelWorldState;
  OpenGl_MatrixState<float> WorldViewState;
  OpenGl_MatrixState<float> ProjectionState;

private:
  Aspect_Drawable myWindow;
  Aspect_Display  myDisplay;

  Aspect_RenderingContext myGContext;

private:
  typedef NCollection_Shared<NCollection_DataMap<TCollection_AsciiString, int>>
                                                                             OpenGl_DelayReleaseMap;
  typedef NCollection_Shared<NCollection_List<occ::handle<OpenGl_Resource>>> OpenGl_ResourcesStack;

  occ::handle<OpenGl_ResourcesMap> mySharedResources;

  occ::handle<OpenGl_DelayReleaseMap> myDelayed;
  occ::handle<OpenGl_ResourcesStack>  myUnusedResources;

  OpenGl_Clipping myClippingState;

  void*                               myGlLibHandle;
  std::unique_ptr<OpenGl_GlFunctions> myFuncs;
  Aspect_GraphicsLibrary              myGapi;
  occ::handle<Image_SupportedFormats> mySupportedFormats;
  int                                 myAnisoMax;
  int                                 myTexClamp;
  int                                 myMaxTexDim;
  int                                 myMaxTexCombined;

  int myMaxTexUnitsFFP;

  int  myMaxDumpSizeX;
  int  myMaxDumpSizeY;
  int  myMaxClipPlanes;
  int  myMaxMsaaSamples;
  int  myMaxDrawBuffers;
  int  myMaxColorAttachments;
  int  myGlVerMajor;
  int  myGlVerMinor;
  bool myIsInitialized;
  bool myIsStereoBuffers;
  bool myHasMsaaTextures;
  bool myIsGlNormalizeEnabled;

  Graphic3d_TextureUnit mySpriteTexUnit;

  bool myHasRayTracing;
  bool myHasRayTracingTextures;
  bool myHasRayTracingAdaptiveSampling;
  bool myHasRayTracingAdaptiveSamplingAtomic;

  bool                  myHasPBR;
  Graphic3d_TextureUnit myPBREnvLUTTexUnit;
  Graphic3d_TextureUnit myPBRDiffIBLMapSHTexUnit;

  Graphic3d_TextureUnit myPBRSpecIBLMapTexUnit;
  Graphic3d_TextureUnit myShadowMapTexUnit;

  Graphic3d_TextureUnit myDepthPeelingDepthTexUnit;
  Graphic3d_TextureUnit myDepthPeelingFrontColorTexUnit;

  occ::handle<OpenGl_ShaderManager> myShaderManager;

private:
  occ::handle<Graphic3d_Camera>     myCamera;
  occ::handle<OpenGl_FrameStats>    myFrameStats;
  occ::handle<OpenGl_ShaderProgram> myActiveProgram;
  occ::handle<OpenGl_TextureSet>    myActiveTextures;

  int                             myActiveMockTextures;
  occ::handle<OpenGl_FrameBuffer> myDefaultFbo;

  occ::handle<OpenGl_LineAttributes> myHatchStyles;
  int                                myActiveHatchType;
  bool                               myHatchIsEnabled;
  occ::handle<OpenGl_Texture>        myTextureRgbaBlack;
  occ::handle<OpenGl_Texture>        myTextureRgbaWhite;
  int                                myViewport[4];
  int                                myViewportVirt[4];
  int                                myPointSpriteOrig;
  int                                myRenderMode;
  int                                myShadeModel;
  int                                myPolygonMode;
  Graphic3d_PolygonOffset            myPolygonOffset;
  Graphic3d_TypeOfBackfacingModel    myFaceCulling;
  int                                myReadBuffer;
  NCollection_Array1<int>            myDrawBuffers;
  unsigned int                       myDefaultVao;
  NCollection_Vec4<bool>             myColorMask;
  bool                               myAllowAlphaToCov;
  bool                               myAlphaToCoverage;
  bool                               myIsGlDebugCtx;
  bool                               myIsWindowDeepColor;
  bool                               myIsSRgbWindow;
  bool                               myIsSRgbActive;
  TCollection_AsciiString            myVendor;
  TColStd_PackedMapOfInteger         myFilters[6];
  unsigned int                       myResolution;
  float                              myResolutionRatio;

  float           myLineWidthScale;
  float           myLineFeather;
  float           myRenderScale;
  float           myRenderScaleInv;
  OpenGl_Material myMaterial;

private:
  OpenGl_Context(const OpenGl_Context&)            = delete;
  OpenGl_Context& operator=(const OpenGl_Context&) = delete;
};
