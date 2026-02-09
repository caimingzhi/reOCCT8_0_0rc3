#pragma once

#include <Graphic3d_CullingTool.hpp>
#include <Graphic3d_WorldViewProjState.hpp>
#include <math_BullardGenerator.hpp>

#include <OpenGl_FrameBuffer.hpp>
#include <OpenGl_FrameStatsPrs.hpp>
#include <OpenGl_GraduatedTrihedron.hpp>
#include <OpenGl_LayerList.hpp>
#include <OpenGl_SceneGeometry.hpp>
#include <OpenGl_Structure.hpp>
#include <OpenGl_TileSampler.hpp>
#include <TCollection_AsciiString.hpp>

#include <map>
#include <set>

class OpenGl_BackgroundArray;
class OpenGl_DepthPeeling;
class OpenGl_PBREnvironment;
struct OpenGl_RaytraceMaterial;
class OpenGl_ShadowMap;
class OpenGl_ShadowMapArray;
class OpenGl_ShaderObject;
class OpenGl_TextureBuffer;
class OpenGl_Workspace;

class OpenGl_View : public Graphic3d_CView
{

public:
  Standard_EXPORT OpenGl_View(const occ::handle<Graphic3d_StructureManager>& theMgr,
                              const occ::handle<OpenGl_GraphicDriver>&       theDriver,
                              const occ::handle<OpenGl_Caps>&                theCaps,
                              OpenGl_StateCounter*                           theCounter);

  Standard_EXPORT ~OpenGl_View() override;

  Standard_EXPORT virtual void ReleaseGlResources(const occ::handle<OpenGl_Context>& theCtx);

  Standard_EXPORT void Remove() override;

  Standard_EXPORT bool SetImmediateModeDrawToFront(const bool theDrawToFrontBuffer) override;

  Standard_EXPORT void SetWindow(const occ::handle<Graphic3d_CView>& theParentVIew,
                                 const occ::handle<Aspect_Window>&   theWindow,
                                 const Aspect_RenderingContext       theContext) override;

  Standard_EXPORT occ::handle<Aspect_Window> Window() const override;

  bool IsDefined() const override { return !myWindow.IsNull(); }

  Standard_EXPORT void Resized() override;

  Standard_EXPORT void Redraw() override;

  Standard_EXPORT void RedrawImmediate() override;

  Standard_EXPORT void Invalidate() override;

  bool IsInvalidated() override { return !myBackBufferRestored; }

  Standard_EXPORT bool BufferDump(Image_PixMap&               theImage,
                                  const Graphic3d_BufferType& theBufferType) override;

  Standard_EXPORT bool ShadowMapDump(Image_PixMap&                  theImage,
                                     const TCollection_AsciiString& theLightName) override;

  Standard_EXPORT void InvalidateBVHData(const Graphic3d_ZLayerId theLayerId) override;

  Standard_EXPORT void InsertLayerBefore(const Graphic3d_ZLayerId        theLayerId,
                                         const Graphic3d_ZLayerSettings& theSettings,
                                         const Graphic3d_ZLayerId        theLayerAfter) override;

  Standard_EXPORT void InsertLayerAfter(const Graphic3d_ZLayerId        theNewLayerId,
                                        const Graphic3d_ZLayerSettings& theSettings,
                                        const Graphic3d_ZLayerId        theLayerBefore) override;

  Standard_EXPORT void RemoveZLayer(const Graphic3d_ZLayerId theLayerId) override;

  Standard_EXPORT void SetZLayerSettings(const Graphic3d_ZLayerId        theLayerId,
                                         const Graphic3d_ZLayerSettings& theSettings) override;

  Standard_EXPORT int ZLayerMax() const override;

  Standard_EXPORT const NCollection_List<occ::handle<Graphic3d_Layer>>& Layers() const override;

  Standard_EXPORT occ::handle<Graphic3d_Layer> Layer(
    const Graphic3d_ZLayerId theLayerId) const override;

  Standard_EXPORT Bnd_Box MinMaxValues(const bool theToIncludeAuxiliary) const override;

  Standard_EXPORT occ::handle<Standard_Transient> FBO() const override;

  Standard_EXPORT void SetFBO(const occ::handle<Standard_Transient>& theFbo) override;

  Standard_EXPORT occ::handle<Standard_Transient> FBOCreate(const int theWidth,
                                                            const int theHeight) override;

  Standard_EXPORT void FBORelease(occ::handle<Standard_Transient>& theFbo) override;

  Standard_EXPORT void FBOGetDimensions(const occ::handle<Standard_Transient>& theFbo,
                                        int&                                   theWidth,
                                        int&                                   theHeight,
                                        int&                                   theWidthMax,
                                        int& theHeightMax) override;

  Standard_EXPORT void FBOChangeViewport(const occ::handle<Standard_Transient>& theFbo,
                                         const int                              theWidth,
                                         const int                              theHeight) override;

  const occ::handle<OpenGl_DepthPeeling>& DepthPeelingFbos() const { return myDepthPeelingFbos; }

public:
  Standard_EXPORT Aspect_GradientBackground GradientBackground() const override;

  Standard_EXPORT void SetGradientBackground(
    const Aspect_GradientBackground& theBackground) override;

  Standard_EXPORT void SetBackgroundImage(const occ::handle<Graphic3d_TextureMap>& theTextureMap,
                                          bool theToUpdatePBREnv = true) override;

  Standard_EXPORT void SetTextureEnv(
    const occ::handle<Graphic3d_TextureEnv>& theTextureEnv) override;

  Standard_EXPORT Aspect_FillMethod BackgroundImageStyle() const override;

  Standard_EXPORT void SetBackgroundImageStyle(const Aspect_FillMethod theFillStyle) override;

  Standard_EXPORT void SetImageBasedLighting(bool theToEnableIBL) override;

  Standard_EXPORT unsigned int SpecIBLMapLevels() const;

  const gp_XYZ& LocalOrigin() const { return myLocalOrigin; }

  Standard_EXPORT void SetLocalOrigin(const gp_XYZ& theOrigin);

  const occ::handle<Graphic3d_LightSet>& Lights() const override { return myLights; }

  void SetLights(const occ::handle<Graphic3d_LightSet>& theLights) override
  {
    myLights               = theLights;
    myCurrLightSourceState = myStateCounter->Increment();
  }

  const occ::handle<Graphic3d_SequenceOfHClipPlane>& ClipPlanes() const override
  {
    return myClipPlanes;
  }

  void SetClipPlanes(const occ::handle<Graphic3d_SequenceOfHClipPlane>& thePlanes) override
  {
    myClipPlanes = thePlanes;
  }

  Standard_EXPORT void DiagnosticInformation(
    NCollection_IndexedDataMap<TCollection_AsciiString, TCollection_AsciiString>& theDict,
    Graphic3d_DiagnosticInfo theFlags) const override;

  Standard_EXPORT TCollection_AsciiString StatisticInformation() const override;

  Standard_EXPORT void StatisticInformation(
    NCollection_IndexedDataMap<TCollection_AsciiString, TCollection_AsciiString>& theDict)
    const override;

public:
  const Quantity_ColorRGBA& BackgroundColor() const { return myBgColor; }

  OpenGl_GraduatedTrihedron& ChangeGraduatedTrihedron() { return myGraduatedTrihedron; }

  void SetTextureEnv(const occ::handle<OpenGl_Context>&       theCtx,
                     const occ::handle<Graphic3d_TextureEnv>& theTexture);

  void SetBackgroundTextureStyle(const Aspect_FillMethod FillStyle);

  void SetBackgroundGradient(const Quantity_Color&           AColor1,
                             const Quantity_Color&           AColor2,
                             const Aspect_GradientFillMethod AType);

  void SetBackgroundGradientType(const Aspect_GradientFillMethod AType);

  const OpenGl_LayerList& LayerList() const { return myZLayers; }

  const occ::handle<OpenGl_Window>& GlWindow() const { return myWindow; }

  const occ::handle<OpenGl_TextureSet>& GlTextureEnv() const { return myTextureEnv; }

  const Graphic3d_CullingTool& BVHTreeSelector() const { return myBVHSelector; }

  bool HasImmediateStructures() const { return myZLayers.NbImmediateStructures() != 0; }

public:
  Standard_EXPORT void GraduatedTrihedronDisplay(
    const Graphic3d_GraduatedTrihedron& theTrihedronData) override;

  Standard_EXPORT void GraduatedTrihedronErase() override;

  Standard_EXPORT void GraduatedTrihedronMinMaxValues(
    const NCollection_Vec3<float> theMin,
    const NCollection_Vec3<float> theMax) override;

  bool ToFlipOutput() const override { return myToFlipOutput; }

  void SetToFlipOutput(const bool theFlip) override { myToFlipOutput = theFlip; }

protected:
  void initTextureEnv(const occ::handle<OpenGl_Context>& theContext);

protected:
  Standard_EXPORT virtual bool prepareFrameBuffers(Graphic3d_Camera::Projection& theProj);

  Standard_EXPORT virtual void redraw(const Graphic3d_Camera::Projection theProjection,
                                      OpenGl_FrameBuffer*                theReadDrawFbo,
                                      OpenGl_FrameBuffer*                theOitAccumFbo);

  Standard_EXPORT virtual bool redrawImmediate(const Graphic3d_Camera::Projection theProjection,
                                               OpenGl_FrameBuffer*                theReadFbo,
                                               OpenGl_FrameBuffer*                theDrawFbo,
                                               OpenGl_FrameBuffer*                theOitAccumFbo,
                                               const bool theIsPartialUpdate = false);

  Standard_EXPORT bool blitSubviews(const Graphic3d_Camera::Projection theProjection,
                                    OpenGl_FrameBuffer*                theDrawFbo);

  Standard_EXPORT bool blitBuffers(OpenGl_FrameBuffer* theReadFbo,
                                   OpenGl_FrameBuffer* theDrawFbo,
                                   const bool          theToFlip = false);

  Standard_EXPORT void bindDefaultFbo(OpenGl_FrameBuffer* theCustomFbo = nullptr);

protected:
  Standard_EXPORT virtual void renderShadowMap(const occ::handle<OpenGl_ShadowMap>& theShadowMap);

  Standard_EXPORT virtual void render(Graphic3d_Camera::Projection theProjection,
                                      OpenGl_FrameBuffer*          theReadDrawFbo,
                                      OpenGl_FrameBuffer*          theOitAccumFbo,
                                      const bool                   theToDrawImmediate);

  Standard_EXPORT virtual void renderScene(Graphic3d_Camera::Projection theProjection,
                                           OpenGl_FrameBuffer*          theReadDrawFbo,
                                           OpenGl_FrameBuffer*          theOitAccumFbo,
                                           const bool                   theToDrawImmediate);

  Standard_EXPORT virtual void drawBackground(const occ::handle<OpenGl_Workspace>& theWorkspace,
                                              Graphic3d_Camera::Projection         theProjection);

  Standard_EXPORT virtual void renderStructs(Graphic3d_Camera::Projection theProjection,
                                             OpenGl_FrameBuffer*          theReadDrawFbo,
                                             OpenGl_FrameBuffer*          theOitAccumFbo,
                                             const bool                   theToDrawImmediate);

  void renderTrihedron(const occ::handle<OpenGl_Workspace>& theWorkspace);

  void renderFrameStats();

private:
  Standard_EXPORT void displayStructure(const occ::handle<Graphic3d_CStructure>& theStructure,
                                        const Graphic3d_DisplayPriority thePriority) override;

  Standard_EXPORT void eraseStructure(
    const occ::handle<Graphic3d_CStructure>& theStructure) override;

  Standard_EXPORT void changeZLayer(const occ::handle<Graphic3d_CStructure>& theCStructure,
                                    const Graphic3d_ZLayerId theNewLayerId) override;

  Standard_EXPORT void changePriority(const occ::handle<Graphic3d_CStructure>& theCStructure,
                                      const Graphic3d_DisplayPriority theNewPriority) override;

private:
  void releaseSrgbResources(const occ::handle<OpenGl_Context>& theCtx);

  bool copyBackToFront();

  OpenGl_VertexBuffer* initBlitQuad(const bool theToFlip);

  void drawStereoPair(OpenGl_FrameBuffer* theDrawFbo);

  bool checkOitCompatibility(const occ::handle<OpenGl_Context>& theGlContext, const bool theMSAA);

protected:
  OpenGl_GraphicDriver*         myDriver;
  occ::handle<OpenGl_Window>    myWindow;
  occ::handle<OpenGl_Workspace> myWorkspace;
  occ::handle<OpenGl_Caps>      myCaps;
  bool                          myWasRedrawnGL;

  occ::handle<Graphic3d_SequenceOfHClipPlane> myClipPlanes;
  gp_XYZ                                      myLocalOrigin;
  occ::handle<OpenGl_FrameBuffer>             myFBO;
  bool                                        myToShowGradTrihedron;
  Graphic3d_GraduatedTrihedron                myGTrihedronData;

  occ::handle<Graphic3d_LightSet> myNoShadingLight;
  occ::handle<Graphic3d_LightSet> myLights;

  OpenGl_LayerList myZLayers;

  Graphic3d_WorldViewProjState myWorldViewProjState;
  OpenGl_StateCounter*         myStateCounter;
  size_t                       myCurrLightSourceState;
  size_t                       myLightsRevision;

  typedef std::pair<size_t, size_t> StateInfo;

  StateInfo myLastOrientationState;
  StateInfo myLastViewMappingState;
  StateInfo myLastLightSourceState;

  Graphic3d_CullingTool myBVHSelector;

  OpenGl_GraduatedTrihedron myGraduatedTrihedron;
  OpenGl_FrameStatsPrs      myFrameStatsPrs;

  occ::handle<OpenGl_FrameBuffer> myOpenGlFBO;
  occ::handle<OpenGl_FrameBuffer> myOpenGlFBO2;

protected:
  int   mySRgbState;
  GLint myFboColorFormat;

  GLint                              myFboDepthFormat;
  NCollection_Vector<int>            myFboOitColorConfig;
  occ::handle<OpenGl_FrameBuffer>    myMainSceneFbos[2];
  occ::handle<OpenGl_FrameBuffer>    myMainSceneFbosOit[2];
  occ::handle<OpenGl_FrameBuffer>    myImmediateSceneFbos[2];
  occ::handle<OpenGl_FrameBuffer>    myImmediateSceneFbosOit[2];
  occ::handle<OpenGl_FrameBuffer>    myXrSceneFbo;
  occ::handle<OpenGl_DepthPeeling>   myDepthPeelingFbos;
  occ::handle<OpenGl_ShadowMapArray> myShadowMaps;
  OpenGl_VertexBuffer                myFullScreenQuad;
  OpenGl_VertexBuffer                myFullScreenQuadFlip;
  bool                               myToFlipOutput;
  unsigned int                       myFrameCounter;
  bool                               myHasFboBlit;
  bool                               myToDisableOIT;
  bool                               myToDisableOITMSAA;
  bool                               myToDisableMSAA;
  bool                               myTransientDrawToFront;
  bool                               myBackBufferRestored;
  bool                               myIsImmediateDrawn;

protected:
  OpenGl_Aspects*         myTextureParams;
  OpenGl_Aspects*         myCubeMapParams;
  OpenGl_Aspects*         myColoredQuadParams;
  OpenGl_BackgroundArray* myBackgrounds[Graphic3d_TypeOfBackground_NB];

  occ::handle<OpenGl_TextureSet> myTextureEnv;
  occ::handle<OpenGl_Texture>    mySkydomeTexture;

protected:
  Standard_EXPORT void updateSkydomeBg(const occ::handle<OpenGl_Context>& theCtx);

protected:
  Standard_EXPORT bool checkPBRAvailability() const;

  Standard_EXPORT void updatePBREnvironment(const occ::handle<OpenGl_Context>& theCtx);

protected:
  enum PBREnvironmentState
  {
    OpenGl_PBREnvState_NONEXISTENT,
    OpenGl_PBREnvState_UNAVAILABLE,
    OpenGl_PBREnvState_CREATED
  };

  occ::handle<OpenGl_PBREnvironment> myPBREnvironment;
  PBREnvironmentState                myPBREnvState;
  bool                               myPBREnvRequest;

protected:
  enum RaytraceInitStatus
  {
    OpenGl_RT_NONE,
    OpenGl_RT_INIT,
    OpenGl_RT_FAIL
  };

  enum RaytraceUpdateMode
  {
    OpenGl_GUM_CHECK,
    OpenGl_GUM_PREPARE,
    OpenGl_GUM_REBUILD
  };

  enum ShaderVariableIndex
  {
    OpenGl_RT_aPosition,

    OpenGl_RT_uOriginLT,
    OpenGl_RT_uOriginLB,
    OpenGl_RT_uOriginRT,
    OpenGl_RT_uOriginRB,
    OpenGl_RT_uDirectLT,
    OpenGl_RT_uDirectLB,
    OpenGl_RT_uDirectRT,
    OpenGl_RT_uDirectRB,
    OpenGl_RT_uViewPrMat,
    OpenGl_RT_uUnviewMat,

    OpenGl_RT_uSceneRad,
    OpenGl_RT_uSceneEps,
    OpenGl_RT_uLightAmbnt,
    OpenGl_RT_uLightCount,

    OpenGl_RT_uBackColorTop,
    OpenGl_RT_uBackColorBot,

    OpenGl_RT_uShadowsEnabled,
    OpenGl_RT_uReflectEnabled,
    OpenGl_RT_uEnvMapEnabled,
    OpenGl_RT_uEnvMapForBack,
    OpenGl_RT_uTexSamplersArray,
    OpenGl_RT_uBlockedRngEnabled,

    OpenGl_RT_uWinSizeX,
    OpenGl_RT_uWinSizeY,

    OpenGl_RT_uAccumSamples,
    OpenGl_RT_uFrameRndSeed,

    OpenGl_RT_uFsaaOffset,
    OpenGl_RT_uSamples,

    OpenGl_RT_uRenderImage,
    OpenGl_RT_uTilesImage,
    OpenGl_RT_uOffsetImage,
    OpenGl_RT_uTileSize,
    OpenGl_RT_uVarianceScaleFactor,

    OpenGl_RT_uMaxRadiance,

    OpenGl_RT_NbVariables
  };

  enum ShaderImageNames
  {
    OpenGl_RT_OutputImage      = 0,
    OpenGl_RT_VisualErrorImage = 1,
    OpenGl_RT_TileOffsetsImage = 2,
    OpenGl_RT_TileSamplesImage = 3
  };

  class ShaderSource
  {
  public:
    ShaderSource() {}

  public:
    const TCollection_AsciiString& ErrorDescription() const { return myError; }

    const TCollection_AsciiString& Prefix() const { return myPrefix; }

    void SetPrefix(const TCollection_AsciiString& thePrefix) { myPrefix = thePrefix; }

    TCollection_AsciiString Source(const occ::handle<OpenGl_Context>& theCtx,
                                   const GLenum                       theType) const;

    bool LoadFromFiles(
      const TCollection_AsciiString* theFileNames,
      const TCollection_AsciiString& thePrefix = TCollection_AsciiString::EmptyString());

    bool LoadFromStrings(
      const TCollection_AsciiString* theStrings,
      const TCollection_AsciiString& thePrefix = TCollection_AsciiString::EmptyString());

  private:
    TCollection_AsciiString mySource;
    TCollection_AsciiString myPrefix;
    TCollection_AsciiString myError;
  };

  static constexpr int THE_DEFAULT_NB_BOUNCES = 3;

  static constexpr int THE_DEFAULT_STACK_SIZE = 10;

  struct RaytracingParams
  {

    int StackSize;

    int NbBounces;

    bool IsZeroToOneDepth;

    bool TransparentShadows;

    bool GlobalIllumination;

    bool UseBindlessTextures;

    bool TwoSidedBsdfModels;

    bool AdaptiveScreenSampling;

    bool AdaptiveScreenSamplingAtomic;

    bool UseEnvMapForBackground;

    bool ToIgnoreNormalMap;

    float RadianceClampingValue;

    bool DepthOfField;

    bool CubemapForBack;

    Graphic3d_ToneMappingMethod ToneMappingMethod;

    RaytracingParams()
        : StackSize(THE_DEFAULT_STACK_SIZE),
          NbBounces(THE_DEFAULT_NB_BOUNCES),
          IsZeroToOneDepth(false),
          TransparentShadows(false),
          GlobalIllumination(false),
          UseBindlessTextures(false),
          TwoSidedBsdfModels(false),
          AdaptiveScreenSampling(false),
          AdaptiveScreenSamplingAtomic(false),
          UseEnvMapForBackground(false),
          ToIgnoreNormalMap(false),
          RadianceClampingValue(30.0),
          DepthOfField(false),
          CubemapForBack(false),
          ToneMappingMethod(Graphic3d_ToneMappingMethod_Disabled)
    {
    }
  };

  struct StructState
  {
    size_t StructureState;
    size_t InstancedState;

    StructState(const size_t theStructureState = 0, const size_t theInstancedState = 0)
        : StructureState(theStructureState),
          InstancedState(theInstancedState)
    {
    }

    StructState(const OpenGl_Structure* theStructure)
    {
      StructureState = theStructure->ModificationState();

      InstancedState = theStructure->InstancedStructure() != nullptr
                         ? theStructure->InstancedStructure()->ModificationState()
                         : 0;
    }
  };

protected:
  bool updateRaytraceGeometry(const RaytraceUpdateMode           theMode,
                              const int                          theViewId,
                              const occ::handle<OpenGl_Context>& theGlContext);

  bool updateRaytraceLightSources(const NCollection_Mat4<float>&     theInvModelView,
                                  const occ::handle<OpenGl_Context>& theGlContext);

  bool toUpdateStructure(const OpenGl_Structure* theStructure);

  bool addRaytraceStructure(const OpenGl_Structure*            theStructure,
                            const occ::handle<OpenGl_Context>& theGlContext);

  bool addRaytraceGroups(const OpenGl_Structure*            theStructure,
                         const OpenGl_RaytraceMaterial&     theStructMat,
                         const occ::handle<TopLoc_Datum3D>& theTrsf,
                         const occ::handle<OpenGl_Context>& theGlContext);

  OpenGl_RaytraceMaterial convertMaterial(const OpenGl_Aspects*              theAspect,
                                          const occ::handle<OpenGl_Context>& theGlContext);

  occ::handle<OpenGl_TriangleSet> addRaytracePrimitiveArray(
    const OpenGl_PrimitiveArray*   theArray,
    const int                      theMatID,
    const NCollection_Mat4<float>* theTrans);

  bool addRaytraceVertexIndices(OpenGl_TriangleSet&          theSet,
                                const int                    theMatID,
                                const int                    theCount,
                                const int                    theOffset,
                                const OpenGl_PrimitiveArray& theArray);

  bool addRaytraceTriangleArray(OpenGl_TriangleSet&                       theSet,
                                const int                                 theMatID,
                                const int                                 theCount,
                                const int                                 theOffset,
                                const occ::handle<Graphic3d_IndexBuffer>& theIndices);

  bool addRaytraceTriangleFanArray(OpenGl_TriangleSet&                       theSet,
                                   const int                                 theMatID,
                                   const int                                 theCount,
                                   const int                                 theOffset,
                                   const occ::handle<Graphic3d_IndexBuffer>& theIndices);

  bool addRaytraceTriangleStripArray(OpenGl_TriangleSet&                       theSet,
                                     const int                                 theMatID,
                                     const int                                 theCount,
                                     const int                                 theOffset,
                                     const occ::handle<Graphic3d_IndexBuffer>& theIndices);

  bool addRaytraceQuadrangleArray(OpenGl_TriangleSet&                       theSet,
                                  const int                                 theMatID,
                                  const int                                 theCount,
                                  const int                                 theOffset,
                                  const occ::handle<Graphic3d_IndexBuffer>& theIndices);

  bool addRaytraceQuadrangleStripArray(OpenGl_TriangleSet&                       theSet,
                                       const int                                 theMatID,
                                       const int                                 theCount,
                                       const int                                 theOffset,
                                       const occ::handle<Graphic3d_IndexBuffer>& theIndices);

  bool addRaytracePolygonArray(OpenGl_TriangleSet&                       theSet,
                               const int                                 theMatID,
                               const int                                 theCount,
                               const int                                 theOffset,
                               const occ::handle<Graphic3d_IndexBuffer>& theIndices);

  bool uploadRaytraceData(const occ::handle<OpenGl_Context>& theGlContext);

  TCollection_AsciiString generateShaderPrefix(
    const occ::handle<OpenGl_Context>& theGlContext) const;

  bool safeFailBack(const TCollection_ExtendedString&  theMessage,
                    const occ::handle<OpenGl_Context>& theGlContext);

  occ::handle<OpenGl_ShaderObject> initShader(const GLenum                       theType,
                                              const ShaderSource&                theSource,
                                              const occ::handle<OpenGl_Context>& theGlContext);

  occ::handle<OpenGl_ShaderProgram> initProgram(
    const occ::handle<OpenGl_Context>&      theGlContext,
    const occ::handle<OpenGl_ShaderObject>& theVertShader,
    const occ::handle<OpenGl_ShaderObject>& theFragShader,
    const TCollection_AsciiString&          theName);

  bool initRaytraceResources(const int                          theSizeX,
                             const int                          theSizeY,
                             const occ::handle<OpenGl_Context>& theGlContext);

  void releaseRaytraceResources(const occ::handle<OpenGl_Context>& theGlContext,
                                const bool                         theToRebuild = false);

  bool updateRaytraceBuffers(const int                          theSizeX,
                             const int                          theSizeY,
                             const occ::handle<OpenGl_Context>& theGlContext);

  void updateCamera(const NCollection_Mat4<float>& theOrientation,
                    const NCollection_Mat4<float>& theViewMapping,
                    NCollection_Vec3<float>*       theOrigins,
                    NCollection_Vec3<float>*       theDirects,
                    NCollection_Mat4<float>&       theView,
                    NCollection_Mat4<float>&       theUnView);

  void updatePerspCameraPT(const NCollection_Mat4<float>& theOrientation,
                           const NCollection_Mat4<float>& theViewMapping,
                           Graphic3d_Camera::Projection   theProjection,
                           NCollection_Mat4<float>&       theViewPr,
                           NCollection_Mat4<float>&       theUnview,
                           const int                      theWinSizeX,
                           const int                      theWinSizeY);

  void bindRaytraceTextures(const occ::handle<OpenGl_Context>& theGlContext, int theStereoView);

  void unbindRaytraceTextures(const occ::handle<OpenGl_Context>& theGlContext);

  bool setUniformState(const int                          theProgramId,
                       const int                          theSizeX,
                       const int                          theSizeY,
                       Graphic3d_Camera::Projection       theProjection,
                       const occ::handle<OpenGl_Context>& theGlContext);

  bool runRaytraceShaders(const int                          theSizeX,
                          const int                          theSizeY,
                          Graphic3d_Camera::Projection       theProjection,
                          OpenGl_FrameBuffer*                theReadDrawFbo,
                          const occ::handle<OpenGl_Context>& theGlContext);

  bool runRaytrace(const int                          theSizeX,
                   const int                          theSizeY,
                   Graphic3d_Camera::Projection       theProjection,
                   OpenGl_FrameBuffer*                theReadDrawFbo,
                   const occ::handle<OpenGl_Context>& theGlContext);

  bool runPathtrace(const int                          theSizeX,
                    const int                          theSizeY,
                    Graphic3d_Camera::Projection       theProjection,
                    const occ::handle<OpenGl_Context>& theGlContext);

  bool runPathtraceOut(Graphic3d_Camera::Projection       theProjection,
                       OpenGl_FrameBuffer*                theReadDrawFbo,
                       const occ::handle<OpenGl_Context>& theGlContext);

  bool raytrace(const int                          theSizeX,
                const int                          theSizeY,
                Graphic3d_Camera::Projection       theProjection,
                OpenGl_FrameBuffer*                theReadDrawFbo,
                const occ::handle<OpenGl_Context>& theGlContext);

protected:
  RaytraceInitStatus myRaytraceInitStatus;

  bool myIsRaytraceDataValid;

  bool myIsRaytraceWarnTextures;

  OpenGl_RaytraceGeometry myRaytraceGeometry;

  opencascade::handle<BVH_Builder<float, 3>> myRaytraceBVHBuilder;

  RaytracingParams myRaytraceParameters;

  float myRaytraceSceneRadius;

  float myRaytraceSceneEpsilon;

  ShaderSource myRaytraceShaderSource;

  ShaderSource myPostFSAAShaderSource;

  ShaderSource myOutImageShaderSource;

  occ::handle<OpenGl_ShaderObject> myRaytraceShader;

  occ::handle<OpenGl_ShaderObject> myPostFSAAShader;

  occ::handle<OpenGl_ShaderObject> myOutImageShader;

  occ::handle<OpenGl_ShaderProgram> myRaytraceProgram;

  occ::handle<OpenGl_ShaderProgram> myPostFSAAProgram;

  occ::handle<OpenGl_ShaderProgram> myOutImageProgram;

  occ::handle<OpenGl_TextureBuffer> mySceneNodeInfoTexture;

  occ::handle<OpenGl_TextureBuffer> mySceneMinPointTexture;

  occ::handle<OpenGl_TextureBuffer> mySceneMaxPointTexture;

  occ::handle<OpenGl_TextureBuffer> mySceneTransformTexture;

  occ::handle<OpenGl_TextureBuffer> myGeometryVertexTexture;

  occ::handle<OpenGl_TextureBuffer> myGeometryNormalTexture;

  occ::handle<OpenGl_TextureBuffer> myGeometryTexCrdTexture;

  occ::handle<OpenGl_TextureBuffer> myGeometryTriangTexture;

  occ::handle<OpenGl_TextureBuffer> myRaytraceMaterialTexture;

  occ::handle<OpenGl_TextureBuffer> myRaytraceLightSrcTexture;

  occ::handle<OpenGl_FrameBuffer> myRaytraceFBO1[2];

  occ::handle<OpenGl_FrameBuffer> myRaytraceFBO2[2];

  occ::handle<OpenGl_Texture> myRaytraceOutputTexture[2];

  occ::handle<OpenGl_Texture> myRaytraceVisualErrorTexture[2];

  occ::handle<OpenGl_Texture> myRaytraceTileOffsetsTexture[2];

  occ::handle<OpenGl_Texture> myRaytraceTileSamplesTexture[2];

  OpenGl_VertexBuffer myRaytraceScreenQuad;

  int myUniformLocations[2][OpenGl_RT_NbVariables];

  std::map<const OpenGl_Structure*, StructState> myStructureStates;

  std::map<size_t, OpenGl_TriangleSet*> myArrayToTrianglesMap;

  std::set<int> myNonRaytraceStructureIDs;

  bool myToUpdateEnvironmentMap;

  size_t myRaytraceLayerListState;

  int myAccumFrames;

  NCollection_Vec3<float> myPreviousOrigins[3];

  math_BullardGenerator myRNG;

  OpenGl_TileSampler myTileSampler;

  NCollection_Vec3<float> myEyeOrig;

  NCollection_Vec3<float> myEyeView;

  NCollection_Vec3<float> myEyeVert;

  NCollection_Vec3<float> myEyeSide;

  NCollection_Vec2<float> myEyeSize;

  float myPrevCameraApertureRadius;

  float myPrevCameraFocalPlaneDist;

public:
  DEFINE_STANDARD_ALLOC
  DEFINE_STANDARD_RTTIEXT(OpenGl_View, Graphic3d_CView)

  friend class OpenGl_GraphicDriver;
  friend class OpenGl_Workspace;
  friend class OpenGl_LayerList;
  friend class OpenGl_FrameStats;
};
