#pragma once

#include <Aspect_RenderingContext.hpp>
#include <Aspect_SkydomeBackground.hpp>
#include <Aspect_Window.hpp>
#include <Graphic3d_BufferType.hpp>
#include <Graphic3d_CubeMap.hpp>
#include <Graphic3d_DataStructureManager.hpp>
#include <Graphic3d_DiagnosticInfo.hpp>
#include <Graphic3d_GraduatedTrihedron.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_Shared.hpp>
#include <Graphic3d_RenderingParams.hpp>
#include <Graphic3d_Structure.hpp>
#include <NCollection_Sequence.hpp>
#include <Graphic3d_TextureEnv.hpp>

enum Graphic3d_TypeOfAnswer
{
  Graphic3d_TOA_YES,
  Graphic3d_TOA_NO,
  Graphic3d_TOA_COMPUTE
};

#include <Graphic3d_TypeOfBackfacingModel.hpp>
#include <Graphic3d_TypeOfBackground.hpp>
#include <Graphic3d_TypeOfShadingModel.hpp>

enum Graphic3d_TypeOfVisualization
{
  Graphic3d_TOV_WIREFRAME,
  Graphic3d_TOV_SHADING
};

#include <NCollection_Vec3.hpp>
#include <Standard_TypeDef.hpp>
#include <Graphic3d_ZLayerId.hpp>
#include <Graphic3d_ZLayerSettings.hpp>
#include <Image_PixMap.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_IndexedDataMap.hpp>

class Aspect_NeutralWindow;
class Aspect_XRSession;
class Graphic3d_CView;
class Graphic3d_Layer;
class Graphic3d_StructureManager;

class Graphic3d_CView : public Graphic3d_DataStructureManager
{
  friend class Graphic3d_StructureManager;
  DEFINE_STANDARD_RTTIEXT(Graphic3d_CView, Graphic3d_DataStructureManager)
public:
  Standard_EXPORT Graphic3d_CView(const occ::handle<Graphic3d_StructureManager>& theMgr);

  Standard_EXPORT ~Graphic3d_CView() override;

  int Identification() const { return myId; }

  Standard_EXPORT virtual void Activate();

  Standard_EXPORT virtual void Deactivate();

  bool IsActive() const { return myIsActive; }

  Standard_EXPORT virtual void Remove();

  bool IsRemoved() const { return myIsRemoved; }

  const occ::handle<Graphic3d_Camera>& Camera() const override { return myCamera; }

  virtual void SetCamera(const occ::handle<Graphic3d_Camera>& theCamera) { myCamera = theCamera; }

  virtual bool ToFlipOutput() const { return false; }

  virtual void SetToFlipOutput(const bool) {}

public:
  Graphic3d_TypeOfShadingModel ShadingModel() const { return myRenderParams.ShadingModel; }

  Standard_EXPORT void SetShadingModel(Graphic3d_TypeOfShadingModel theModel);

  Graphic3d_TypeOfBackfacingModel BackfacingModel() const { return myBackfacing; }

  void SetBackfacingModel(const Graphic3d_TypeOfBackfacingModel theModel)
  {
    myBackfacing = theModel;
  }

  Graphic3d_TypeOfVisualization VisualizationType() const { return myVisualization; }

  void SetVisualizationType(const Graphic3d_TypeOfVisualization theType)
  {
    myVisualization = theType;
  }

  Graphic3d_ZLayerId ZLayerTarget() const { return myZLayerTarget; }

  void SetZLayerTarget(const Graphic3d_ZLayerId theTarget) { myZLayerTarget = theTarget; }

  bool ZLayerRedrawMode() const { return myZLayerRedrawMode; }

  void SetZLayerRedrawMode(const bool theMode) { myZLayerRedrawMode = theMode; }

  Standard_EXPORT void SetComputedMode(const bool theMode);

  bool ComputedMode() const { return myIsInComputedMode; }

  Standard_EXPORT void ReCompute(const occ::handle<Graphic3d_Structure>& theStructure);

  Standard_EXPORT void Update(const Graphic3d_ZLayerId theLayerId = Graphic3d_ZLayerId_UNKNOWN);

  Standard_EXPORT void Compute();

  Standard_EXPORT void DisplayedStructures(
    NCollection_Map<occ::handle<Graphic3d_Structure>>& theStructures) const;

  virtual int NumberOfDisplayedStructures() const { return myStructsDisplayed.Extent(); }

  Standard_EXPORT bool IsComputed(const int                         theStructId,
                                  occ::handle<Graphic3d_Structure>& theComputedStruct) const;

  Standard_EXPORT virtual Bnd_Box MinMaxValues(const bool theToIncludeAuxiliary = false) const;

  Standard_EXPORT Bnd_Box
    MinMaxValues(const NCollection_Map<occ::handle<Graphic3d_Structure>>& theSet,
                 const bool theToIncludeAuxiliary = false) const;

  const occ::handle<Graphic3d_StructureManager>& StructureManager() const
  {
    return myStructureManager;
  }

private:
  Standard_EXPORT Graphic3d_TypeOfAnswer
    acceptDisplay(const Graphic3d_TypeOfStructure theStructType) const;

  Standard_EXPORT void Clear(Graphic3d_Structure* theStructure, const bool theWithDestruction);

  Standard_EXPORT void Connect(const Graphic3d_Structure* theMother,
                               const Graphic3d_Structure* theDaughter);

  Standard_EXPORT void Disconnect(const Graphic3d_Structure* theMother,
                                  const Graphic3d_Structure* theDaughter);

  Standard_EXPORT void Display(const occ::handle<Graphic3d_Structure>& theStructure);

  Standard_EXPORT void Erase(const occ::handle<Graphic3d_Structure>& theStructure);

  Standard_EXPORT void Highlight(const occ::handle<Graphic3d_Structure>& theStructure);

  Standard_EXPORT void SetTransform(const occ::handle<Graphic3d_Structure>& theStructure,
                                    const occ::handle<TopLoc_Datum3D>&      theTrsf);

  Standard_EXPORT void UnHighlight(const occ::handle<Graphic3d_Structure>& theStructure);

  Standard_EXPORT int IsComputed(const Graphic3d_Structure* theStructure) const;

  int IsComputed(const occ::handle<Graphic3d_Structure>& theStructure) const
  {
    return IsComputed(theStructure.get());
  }

  Standard_EXPORT bool IsDisplayed(const occ::handle<Graphic3d_Structure>& theStructure) const;

  Standard_EXPORT void ChangePriority(const occ::handle<Graphic3d_Structure>& theStructure,
                                      const Graphic3d_DisplayPriority         theOldPriority,
                                      const Graphic3d_DisplayPriority         theNewPriority);

  Standard_EXPORT void ChangeZLayer(const occ::handle<Graphic3d_Structure>& theStructure,
                                    const Graphic3d_ZLayerId                theLayerId);

  Standard_EXPORT int HaveTheSameOwner(const occ::handle<Graphic3d_Structure>& theStructure) const;

public:
  virtual void Redraw() = 0;

  virtual void RedrawImmediate() = 0;

  virtual void Invalidate() = 0;

  virtual bool IsInvalidated() = 0;

  Standard_EXPORT virtual void Resized() = 0;

  virtual bool SetImmediateModeDrawToFront(const bool theDrawToFrontBuffer) = 0;

  virtual void SetWindow(const occ::handle<Graphic3d_CView>& theParentVIew,
                         const occ::handle<Aspect_Window>&   theWindow,
                         const Aspect_RenderingContext       theContext) = 0;

  virtual occ::handle<Aspect_Window> Window() const = 0;

  virtual bool IsDefined() const = 0;

  virtual bool BufferDump(Image_PixMap& theImage, const Graphic3d_BufferType& theBufferType) = 0;

  virtual bool ShadowMapDump(Image_PixMap&                  theImage,
                             const TCollection_AsciiString& theLightName) = 0;

  virtual void InvalidateBVHData(const Graphic3d_ZLayerId theLayerId) = 0;

  virtual void InsertLayerBefore(const Graphic3d_ZLayerId        theNewLayerId,
                                 const Graphic3d_ZLayerSettings& theSettings,
                                 const Graphic3d_ZLayerId        theLayerAfter) = 0;

  virtual void InsertLayerAfter(const Graphic3d_ZLayerId        theNewLayerId,
                                const Graphic3d_ZLayerSettings& theSettings,
                                const Graphic3d_ZLayerId        theLayerBefore) = 0;

  virtual int ZLayerMax() const = 0;

  virtual const NCollection_List<occ::handle<Graphic3d_Layer>>& Layers() const = 0;

  virtual occ::handle<Graphic3d_Layer> Layer(const Graphic3d_ZLayerId theLayerId) const = 0;

  Standard_EXPORT virtual void InvalidateZLayerBoundingBox(const Graphic3d_ZLayerId theLayerId);

  virtual void RemoveZLayer(const Graphic3d_ZLayerId theLayerId) = 0;

  virtual void SetZLayerSettings(const Graphic3d_ZLayerId        theLayerId,
                                 const Graphic3d_ZLayerSettings& theSettings) = 0;

  Standard_EXPORT double ConsiderZoomPersistenceObjects();

  virtual occ::handle<Standard_Transient> FBO() const = 0;

  virtual void SetFBO(const occ::handle<Standard_Transient>& theFbo) = 0;

  virtual occ::handle<Standard_Transient> FBOCreate(const int theWidth, const int theHeight) = 0;

  virtual void FBORelease(occ::handle<Standard_Transient>& theFbo) = 0;

  virtual void FBOGetDimensions(const occ::handle<Standard_Transient>& theFbo,
                                int&                                   theWidth,
                                int&                                   theHeight,
                                int&                                   theWidthMax,
                                int&                                   theHeightMax) = 0;

  virtual void FBOChangeViewport(const occ::handle<Standard_Transient>& theFbo,
                                 const int                              theWidth,
                                 const int                              theHeight) = 0;

public:
  Standard_EXPORT virtual void CopySettings(const occ::handle<Graphic3d_CView>& theOther);

  const Graphic3d_RenderingParams& RenderingParams() const { return myRenderParams; }

  Graphic3d_RenderingParams& ChangeRenderingParams() { return myRenderParams; }

public:
  virtual Aspect_Background Background() const { return Aspect_Background(myBgColor.GetRGB()); }

  virtual void SetBackground(const Aspect_Background& theBackground)
  {
    myBgColor.SetRGB(theBackground.Color());
  }

  virtual Aspect_GradientBackground GradientBackground() const = 0;

  virtual void SetGradientBackground(const Aspect_GradientBackground& theBackground) = 0;

  const occ::handle<Graphic3d_TextureMap>& BackgroundImage() { return myBackgroundImage; }

  const occ::handle<Graphic3d_CubeMap>& BackgroundCubeMap() const { return myCubeMapBackground; }

  const occ::handle<Graphic3d_CubeMap>& IBLCubeMap() const { return myCubeMapIBL; }

  virtual void SetBackgroundImage(const occ::handle<Graphic3d_TextureMap>& theTextureMap,
                                  bool theToUpdatePBREnv = true) = 0;

  virtual Aspect_FillMethod BackgroundImageStyle() const = 0;

  virtual void SetBackgroundImageStyle(const Aspect_FillMethod theFillStyle) = 0;

  Graphic3d_TypeOfBackground BackgroundType() const { return myBackgroundType; }

  void SetBackgroundType(Graphic3d_TypeOfBackground theType) { myBackgroundType = theType; }

  const Aspect_SkydomeBackground& BackgroundSkydome() const { return mySkydomeAspect; }

  Standard_EXPORT void SetBackgroundSkydome(const Aspect_SkydomeBackground& theAspect,
                                            bool theToUpdatePBREnv = true);

  virtual void SetImageBasedLighting(bool theToEnableIBL) = 0;

  const occ::handle<Graphic3d_TextureEnv>& TextureEnv() const { return myTextureEnvData; }

  virtual void SetTextureEnv(const occ::handle<Graphic3d_TextureEnv>& theTextureEnv) = 0;

public:
  virtual const occ::handle<Graphic3d_LightSet>& Lights() const = 0;

  virtual void SetLights(const occ::handle<Graphic3d_LightSet>& theLights) = 0;

  virtual const occ::handle<Graphic3d_SequenceOfHClipPlane>& ClipPlanes() const = 0;

  virtual void SetClipPlanes(const occ::handle<Graphic3d_SequenceOfHClipPlane>& thePlanes) = 0;

  Standard_EXPORT virtual void DiagnosticInformation(
    NCollection_IndexedDataMap<TCollection_AsciiString, TCollection_AsciiString>& theDict,
    Graphic3d_DiagnosticInfo theFlags) const = 0;

  virtual TCollection_AsciiString StatisticInformation() const = 0;

  virtual void StatisticInformation(
    NCollection_IndexedDataMap<TCollection_AsciiString, TCollection_AsciiString>& theDict)
    const = 0;

public:
  double UnitFactor() const { return myUnitFactor; }

  Standard_EXPORT void SetUnitFactor(double theFactor);

  const occ::handle<Aspect_XRSession>& XRSession() const { return myXRSession; }

  void SetXRSession(const occ::handle<Aspect_XRSession>& theSession) { myXRSession = theSession; }

  Standard_EXPORT bool IsActiveXR() const;

  Standard_EXPORT virtual bool InitXR();

  Standard_EXPORT virtual void ReleaseXR();

  Standard_EXPORT virtual void ProcessXRInput();

  Standard_EXPORT void SetupXRPosedCamera();

  Standard_EXPORT void UnsetXRPosedCamera();

  const occ::handle<Graphic3d_Camera>& PosedXRCamera() const { return myPosedXRCamera; }

  void SetPosedXRCamera(const occ::handle<Graphic3d_Camera>& theCamera)
  {
    myPosedXRCamera = theCamera;
  }

  const occ::handle<Graphic3d_Camera>& BaseXRCamera() const { return myBaseXRCamera; }

  void SetBaseXRCamera(const occ::handle<Graphic3d_Camera>& theCamera)
  {
    myBaseXRCamera = theCamera;
  }

  gp_Trsf PoseXRToWorld(const gp_Trsf& thePoseXR) const
  {
    const occ::handle<Graphic3d_Camera>& anOrigin = myBaseXRCamera;
    const gp_Ax3                         anAxVr(gp::Origin(), gp::DZ(), gp::DX());
    const gp_Ax3 aCameraCS(anOrigin->Eye().XYZ(), -anOrigin->Direction(), -anOrigin->SideRight());
    gp_Trsf      aTrsfCS;
    aTrsfCS.SetTransformation(aCameraCS, anAxVr);
    return aTrsfCS * thePoseXR;
  }

  gp_Ax1 ViewAxisInWorld(const gp_Trsf& thePoseXR) const
  {
    return gp_Ax1(gp::Origin(), -gp::DZ()).Transformed(PoseXRToWorld(thePoseXR));
  }

  Standard_EXPORT void SynchronizeXRBaseToPosedCamera();

  Standard_EXPORT void SynchronizeXRPosedToBaseCamera();

  Standard_EXPORT void ComputeXRPosedCameraFromBase(Graphic3d_Camera& theCam,
                                                    const gp_Trsf&    theXRTrsf) const;

  Standard_EXPORT void ComputeXRBaseCameraFromPosed(const Graphic3d_Camera& theCamPosed,
                                                    const gp_Trsf&          thePoseTrsf);

  Standard_EXPORT void TurnViewXRCamera(const gp_Trsf& theTrsfTurn);

public:
  virtual const Graphic3d_GraduatedTrihedron& GetGraduatedTrihedron() { return myGTrihedronData; }

  virtual void GraduatedTrihedronDisplay(const Graphic3d_GraduatedTrihedron& theTrihedronData)
  {
    (void)theTrihedronData;
  }

  virtual void GraduatedTrihedronErase() {}

  virtual void GraduatedTrihedronMinMaxValues(const NCollection_Vec3<float> theMin,
                                              const NCollection_Vec3<float> theMax)
  {
    (void)theMin;
    (void)theMax;
  }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

public:
  bool IsSubview() const { return myParentView != nullptr; }

  Graphic3d_CView* ParentView() { return myParentView; }

  bool IsSubviewComposer() const { return myIsSubviewComposer; }

  void SetSubviewComposer(bool theIsComposer) { myIsSubviewComposer = theIsComposer; }

  const NCollection_Sequence<occ::handle<Graphic3d_CView>>& Subviews() const { return mySubviews; }

  Standard_EXPORT void AddSubview(const occ::handle<Graphic3d_CView>& theView);

  Standard_EXPORT bool RemoveSubview(const Graphic3d_CView* theView);

  Aspect_TypeOfTriedronPosition SubviewCorner() const { return mySubviewCorner; }

  void SetSubviewCorner(Aspect_TypeOfTriedronPosition thePos) { mySubviewCorner = thePos; }

  const NCollection_Vec2<int>& SubviewTopLeft() const { return mySubviewTopLeft; }

  bool IsSubViewRelativeSize() const
  {
    return mySubviewSize.x() <= 1.0 && mySubviewSize.y() <= 1.0;
  }

  const NCollection_Vec2<double>& SubviewSize() const { return mySubviewSize; }

  void SetSubviewSize(const NCollection_Vec2<double>& theSize) { mySubviewSize = theSize; }

  const NCollection_Vec2<double>& SubviewOffset() const { return mySubviewOffset; }

  void SetSubviewOffset(const NCollection_Vec2<double>& theOffset) { mySubviewOffset = theOffset; }

  const NCollection_Vec2<int>& SubviewMargins() const { return mySubviewMargins; }

  void SetSubviewMargins(const NCollection_Vec2<int>& theMargins) { mySubviewMargins = theMargins; }

  Standard_EXPORT void SubviewResized(const occ::handle<Aspect_NeutralWindow>& theWindow);

private:
  virtual void displayStructure(const occ::handle<Graphic3d_CStructure>& theStructure,
                                const Graphic3d_DisplayPriority          thePriority) = 0;

  virtual void eraseStructure(const occ::handle<Graphic3d_CStructure>& theStructure) = 0;

  virtual void changeZLayer(const occ::handle<Graphic3d_CStructure>& theCStructure,
                            const Graphic3d_ZLayerId                 theNewLayerId) = 0;

  virtual void changePriority(const occ::handle<Graphic3d_CStructure>& theCStructure,
                              const Graphic3d_DisplayPriority          theNewPriority) = 0;

protected:
  int                       myId;
  Graphic3d_RenderingParams myRenderParams;

  NCollection_Sequence<occ::handle<Graphic3d_CView>> mySubviews;
  Graphic3d_CView*                                   myParentView;

  bool                          myIsSubviewComposer;
  Aspect_TypeOfTriedronPosition mySubviewCorner;
  NCollection_Vec2<int>         mySubviewTopLeft;
  NCollection_Vec2<int>         mySubviewMargins;
  NCollection_Vec2<double>      mySubviewSize;
  NCollection_Vec2<double>      mySubviewOffset;

  occ::handle<Graphic3d_StructureManager>                myStructureManager;
  occ::handle<Graphic3d_Camera>                          myCamera;
  NCollection_Sequence<occ::handle<Graphic3d_Structure>> myStructsToCompute;
  NCollection_Sequence<occ::handle<Graphic3d_Structure>> myStructsComputed;
  NCollection_Map<occ::handle<Graphic3d_Structure>>      myStructsDisplayed;
  bool                                                   myIsInComputedMode;
  bool                                                   myIsActive;
  bool                                                   myIsRemoved;
  Graphic3d_TypeOfBackfacingModel                        myBackfacing;
  Graphic3d_TypeOfVisualization                          myVisualization;

  Graphic3d_ZLayerId myZLayerTarget;
  bool               myZLayerRedrawMode;

  Quantity_ColorRGBA                myBgColor;
  occ::handle<Graphic3d_TextureMap> myBackgroundImage;
  occ::handle<Graphic3d_CubeMap>    myCubeMapBackground;
  occ::handle<Graphic3d_CubeMap>    myCubeMapIBL;
  occ::handle<Graphic3d_TextureEnv> myTextureEnvData;
  Graphic3d_GraduatedTrihedron      myGTrihedronData;
  Graphic3d_TypeOfBackground        myBackgroundType;
  Aspect_SkydomeBackground          mySkydomeAspect;
  bool                              myToUpdateSkydome;

  occ::handle<Aspect_XRSession> myXRSession;

  occ::handle<Graphic3d_Camera> myBackXRCamera;
  occ::handle<Graphic3d_Camera> myBaseXRCamera;
  occ::handle<Graphic3d_Camera> myPosedXRCamera;
  occ::handle<Graphic3d_Camera> myPosedXRCameraCopy;
  double                        myUnitFactor;
};
